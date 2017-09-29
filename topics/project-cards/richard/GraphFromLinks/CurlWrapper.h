#pragma once

#include <curl/curl.h>
#include <sstream>


#define HEADER_ACCEPT "Accept:text/html,application/xhtml+xml,application/xml"
#define HEADER_USER_AGENT                                                                          \
    "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.17 (KHTML, "                       \
    "like Gecko) Chrome/24.0.1312.70 Safari/537.17"

class CurlWrapper
{
public:
    /**
     * This function will call CURL with the requested url and
     * returns a string of the data received.
     */
    std::string getPage(std::string pageUrl)
    {
        CURL *curl;
        CURLcode res;

        curl = curl_easy_init();
        std::stringstream out;
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
            curl_easy_setopt(curl, CURLOPT_URL, pageUrl.c_str());
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return out.str();
    }

private:
    /**
     * a helper function for CURL
     */
    static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
    {
        std::string data((const char *)ptr, (size_t)size * nmemb);
        *((std::stringstream *)stream) << data << std::endl;
        return size * nmemb;
    }

};
