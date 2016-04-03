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
 * Use this function for test the regexp reading from a local file
 * @param filename the path of the local file
 */ 
string getFile (string filename) {
  ifstream ist{ filename,  ios::in };
  if ( ist.is_open() ) {
    stringstream stream;
    string line;
    while ( getline (ist, line) ) {
      stream << line <<  endl;
    }
    return stream.str();
  }else{
    return "";
  }
}

/**
* Requests the web page from the Neue Zürcher Zeitung Site and then
* extracts the clickable hypertext links using a regular expression.
*/
int main(void) {
	string webPage = getPage("www.nzz.ch"); 
   //getFile("testcontent2.html");
// 	cout << "THEPAGE" << webPage << "ENDPAGE";

	string outputFilename = "parsedresults.txt";
	ofstream ost{ outputFilename, ios::out  };
	if (!ost) {
		cout << "can't open output file" << outputFilename;
		return 255;
	}

//	regex literPattern { R"(<a\s.*href=(".*").*>(.*)</a>)" };
	regex literPattern { 
	      //tag and multi params,  find href,   then the real link,  then again multi params
	    R"(<a ([\w]+="[\d\w\.-_:=']*" )*href="((https?://)?([\da-z\.-]+)(\.[a-z\.]{2,6})?([\/\w \.-]*)*\/?(\?[^<^>]*)*)\"( [\w]+="[\d\w\.-_:=']*" ?)*>([^<^>]*)</a>)" 
	};
	//regex literPattern { R"((https?:\/\/)?([\da-z\.-]+)\.([a-z\.]{2,6})([\/\w \.-]*)*\/?)" };
	auto literBegin = sregex_iterator(webPage.begin(), webPage.end(), literPattern);
	auto literEnd = sregex_iterator();

	cout << endl << "link list:" << endl;
	int cnt {0};
	for ( sregex_iterator i = literBegin; i != literEnd; ++i ) {
		cout << (*i)[9] << " -> " << (*i)[2] << "\n";
		ost  << (*i)[9] << " -> " << (*i)[2] << "\n";
		cnt++;
	}
	cout << "counts: " << cnt << " links." << endl;

	return 0;
}
