#pragma once

#include <iostream>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;

#include <libxml/HTMLparser.h>

#include <locale>
#include <codecvt>

#include "CurlWrapper.h"

/**
* @brief A class representing a link and a vector of children
*/
class Link
{
public:
    /**
    * @brief Constructs a new link with the url, and the description.
    * It downloads the webpage and stores it in the member variable webPage
    */
    Link(std::wstring href, std::wstring description)
        : href(href), description(description), node(counter++)
    {
        this->fetch();
    };

    /**
    * @brief Constructs a new link with the url, html document
    */
    Link(std::string href, std::wstring description) : Link(stringToWstring(href), description)
    {
    };

    /**
    * @brief an internal node number
    */
    int node;

    /**
    * @brief the child pages
    */
    std::vector<Link> children{};


    /**
    * @brief returns a json representation of the node with href, description and node number
    */
    json toJson() const
    {
        json j = {{"href", wstringToString(href)},
                  {"text", wstringToString(description)},
                  {"node", node}};
        for (auto child : children) {
            j["children"].push_back({{"href", wstringToString(child.href)},
                                     {"text", wstringToString(child.description)},
                                     {"node", child.node}});
        }
        return j;
    }

    /**
    *@brief fetches the webpage in the href and stores the result in the member variable webPage
    */
    void fetch()
    {
        CurlWrapper w;
        webPage = w.getPage(wstringToString(href));
        std::cout << "Downloaded URL: " << wstringToString(href) << " (" << webPage.size()
                  << " chars)" << std::endl;
    }

    /**
    * @brief parses the webPage for links and adds them to the children vector.
    */
    void parseLinks() 
    {
        // std::vector<Link> links{};
        _xmlDoc *htmlDocument =
            htmlReadDoc((const xmlChar *)webPage.c_str(), NULL, NULL,
                        HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);

        if (htmlDocument) {
            xmlNodePtr root_element = (xmlNodePtr)htmlDocument;
            collectLinks(root_element);
        }

        xmlFreeDoc(htmlDocument); // clear memory
        // return links;
    }

    /**
    * @brief Searches the xmlNode for href tags and adds them to the children vector
    * can be called recursively.
    */
    void collectLinks(xmlNode *a_node)
    {
        xmlNode *cur_node = NULL;

        for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
            if (cur_node->type == XML_ELEMENT_NODE) {
                std::string name(reinterpret_cast<const char *>(cur_node->name));
                if (name == "a") {
                    xmlChar *hrefProp = xmlGetProp(cur_node, (const xmlChar *)"href");
                    std::wstring href = xmlCharToWideString(hrefProp);
                    // std::string href = xmlCharToString(hrefProp);
                    xmlFree(hrefProp);
                    std::wstring text = xmlCharToWideString(cur_node->children->content);
                    // std::string text = xmlCharToString(cur_node->children->content);
                    children.emplace_back(Link(href, text));
                }
            }

            collectLinks(cur_node->children);
        }
    }

private:
    /**
    * @brief the URL or the link
    */
    std::wstring href;

    /**
    * @brief A description for the Link
    */
    std::wstring description;

    /**
    * @brief static variable to help create the next id
    */
    static int counter;

    /**
    * @brief the data on the webpage
    */
    std::string webPage{""};

    /**
    * @brief Converts a std::wstring to a std::string
    * @param ws the std::wstring to convert
    * @return the std::string
    * @see
    * https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
    */
    std::string wstringToString(const std::wstring ws) const
    {
        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;

        return converter.to_bytes(ws);
    }

    /**
     * @brief Converts a std::string to a std::wstring
     *
     * @param s the std::string to convert
     * @return the std::wstring
    * @see
        * https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
    */
    std::wstring stringToWstring(const std::string s) const
    {
        using convert_type = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_type, wchar_t> converter;

        return converter.from_bytes(s);
    }

    /**
    * @see
    * https://stackoverflow.com/questions/14107268/libxml2-xmlchar-to-stdwstring
    */
    std::wstring xmlCharToWideString(const xmlChar *xmlString) const
    {
        if (!xmlString) {
            return L"Null pointer passed to xmlCharToWideString";
        }
        try {
            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> conv;
            return conv.from_bytes((const char *)xmlString);
        } catch (const std::range_error &e) {
            return L"wstring_convert failed";
        }
    }
};

// the static variable has to be initialised and this has to happen outside the class definition
int Link::counter = 0;
