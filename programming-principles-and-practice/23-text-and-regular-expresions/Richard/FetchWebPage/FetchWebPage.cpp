#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include <fstream>
//#include <regex>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

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
* Requests the web page from the Swiss Customs Site and then
* extracts the wine import contingent for the year.
*/
int main(void) {
	string webPage = getPage("http://www.ezv.admin.ch/zollinfo_firmen/abfertigungshilfen/zollkontingente/index.html?lang=de&id=1289&show=neu");

	string outputFilename = "parsedresults.txt";
	ofstream ost{ outputFilename, ios::out | ios::app };
	if (!ost) {
		cout << "can't open output file" << outputFilename;
		return 255;
	}

	regex datePattern { R"((\d{2}\.\d{2}\.\d{4})\s-\s\d{2}:\d{2})" };
	smatch dateMatches;
	if (regex_search(webPage, dateMatches, datePattern)) {
		ost << dateMatches[1] << "\t";
	}

	regex literPattern { R"(<b>(.{4,16}).Liter)" };
	auto literBegin = sregex_iterator(webPage.begin(), webPage.end(), literPattern);
	auto literEnd = sregex_iterator();

	for ( sregex_iterator i = literBegin; i != literEnd; ++i )	{
		ost << (*i)[1] << "\t";
	}

	ost << endl;
	cout << "Successfully downloaded values\n";
	return 0;
}
