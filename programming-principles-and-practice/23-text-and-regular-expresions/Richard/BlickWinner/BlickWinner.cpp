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
* Requests the web page from the Blick am Abend URL and
* extract the winners writing them to a file.
*/
int main(void) {
	string webPage = getPage("http://services.vpch.ch/winonlineparticipation/WinBlick-baa/");

	string outputFilename = "parsedresults.txt";
	ofstream ost{ outputFilename, ios::out | ios::app };
	if (!ost) {
		cout << "can't open output file" << outputFilename;
		return 255;
	}

	regex literPattern { R"(<div id="winnergalery-smaller-winner.{1,2}-text" style="display:none;">(\w+\s\w+\s\(\d+\).*?)</div>)" };
	auto literBegin = sregex_iterator(webPage.begin(), webPage.end(), literPattern);
	auto literEnd = sregex_iterator();

	for ( sregex_iterator i = literBegin; i != literEnd; ++i )	{
		ost << (*i)[1] << endl;
	}

	cout << "Successfully downloaded values\n";
	return 0;
}
