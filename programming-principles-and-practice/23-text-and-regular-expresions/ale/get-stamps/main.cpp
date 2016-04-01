/**
 * Fetch the html page published by the Swiss Post with the prices for sending letters.
 * https://www.post.ch/de/privat/versenden/briefe-inland-privat/a-post-privat
 * The values are stored in a structure and, for now, is stored in a local file.
 * Based on this one could build a tool to calculating the price for sending a letter
 * by querying its size.
 */
#include <sstream>
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <regex>

using namespace std;

/**
* a helper function for CURL
*/
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
	string data((const char*)ptr, (size_t)size * nmemb);
	*((stringstream*)stream) << data << endl;
	return size * nmemb;
}

/**
* This function will call CURL with the requested url and
* returns a string of the data received.
*/
string getPage( string pageUrl ) {
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	stringstream out;
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
		curl_easy_setopt(curl, CURLOPT_URL, pageUrl.c_str());
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	return out.str();
}

/**
 * size and price of a letter
 */
struct PriceCategory 
{
	string name;
	string aSize;
	double width;
	double height;
	int thickness;
	int weightFrom;
	int weightTo;
	double price;
	PriceCategory(string name, string aSize, string height, string width, string thickness, string weightFrom, string weightTo, string price)
	: name(name), aSize(aSize), height(stod(height)), width(stod(width)), thickness(stoi(thickness)), weightFrom(stoi(weightFrom)), weightTo(stoi(weightTo)), price(stod(price)) {}
	friend ostream& operator<< (ostream&, const PriceCategory&);
};

/**
 * overload << for "cout << PriceCategory;"
 */
ostream& operator<< (ostream& os, const PriceCategory& obj) {
    os << obj.name << " (" << obj.aSize << ") ";
    os << obj.width << " x " << obj.height << " x " << obj.thickness << " cm";
    os << "; from " << obj.weightFrom << " to " << obj.weightTo << " g";
    os << "; CHF " << obj.price;
    return os;
}

int main() {
	string webPage = getPage("https://www.post.ch/de/privat/versenden/briefe-inland-privat/a-post-privat");
	// ifstream t("a-post-privat.html");
	// string webPage((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

	string outputFilename = "parsedresults.txt";
	ofstream ost{ outputFilename, ios::out /*| ios::app*/ };
	if (!ost) {
		cout << "can't open output file" << outputFilename;
		return 255;
	}

    // eventually remove all end of lines
    // webPage.erase(std::remove(webPage.begin(), webPage.end(), '\n'), webPage.end());
    // webPage.erase(std::remove(webPage.begin(), webPage.end(), '\r'), webPage.end());

    regex e;

    // remove spaces around the html tag delimiters (only the cases that matter for us are retianed)
    e = R"(>\s+)";
    webPage = regex_replace(webPage, e, ">");
    e = R"(\s+<)";
    webPage = regex_replace(webPage, e, "<");

    // match the rows with the prices, extract the relevant data and store it in the PriceCategory structure
	smatch m;
	e = R"(<tr><td>(.+?)</td><td>bis (B\d) \(([\d\.]+) x ([\d\.]+) cm; bis (\d+) cm Dicke\)</td><td>(\d+) bis (\d+) g</td><td>([\d\.]+)</td></tr>)";
	auto formatBegin = sregex_iterator(webPage.begin(), webPage.end(), e);
	auto formatEnd = sregex_iterator();

	for ( sregex_iterator i = formatBegin; i != formatEnd; ++i )	{
		PriceCategory pc {(*i)[1], (*i)[2], (*i)[3], (*i)[4], (*i)[5], (*i)[6], (*i)[7], (*i)[8]};
		ost << pc << endl;
	}

    // ost << webPage << endl; // output the full page for debugging

	cout << "Values Successfully downloaded\n";

    return  0;
}
