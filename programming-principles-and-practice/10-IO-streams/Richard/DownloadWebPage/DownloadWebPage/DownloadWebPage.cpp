#include "stdafx.h"
#include <curl/curl.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
	string data((const char*)ptr, (size_t)size * nmemb);
	*((stringstream*)stream) << data << endl;
	return size * nmemb;
}

int main(void)
{
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	std::stringstream out;
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
		curl_easy_setopt(curl, CURLOPT_URL, "http://www.ezv.admin.ch/zollinfo_firmen/abfertigungshilfen/zollkontingente/index.html?lang=de&id=1289&show=neu");
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	string webPage = out.str();

	string outputFilename = "wein.csv";
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


	regex pattern { R"(<b>(.*) Liter)" };
	std::regex_iterator<std::string::iterator> it(webPage.begin(), webPage.end(), pattern);
	std::regex_iterator<std::string::iterator> end;

	while (it != end)
	{
		ost << (*it)[1] << "\t";
		++it;
	}

	ost << endl;
	cout << "Successfully downloaded values\n";
	return 0;
}
