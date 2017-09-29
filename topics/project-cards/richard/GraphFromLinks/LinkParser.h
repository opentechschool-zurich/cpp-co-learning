#pragma once

#include <vector>

#include <locale>
#include <codecvt>

#include <libxml/HTMLparser.h>

#include "Link.h"

/**
* A class which uses the libmlx2 html parser to parse the supplied html
* document and extract the anchor tags and their links.

* I implemented this as a class because that allows me to define a
* destructor which is necessary to clean up memory that libxml2 allocates
* in a RIAA C++ kind of way.
*/
class LinkParser
{
public:
    ~LinkParser() { xmlCleanupParser(); }

    std::vector<Link> parseLinks(std::string webPage)
    {
        std::vector<Link> links{};
        _xmlDoc *htmlDocument =
            htmlReadDoc((const xmlChar *)webPage.c_str(), NULL, NULL,
                        HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);

        if (htmlDocument) {
            xmlNodePtr root_element = (xmlNodePtr)htmlDocument;
            collectLinks(links, root_element);
        }

        xmlFreeDoc(htmlDocument); // clear memory
        return links;
    }

private:
    void collectLinks(std::vector<Link> &links, xmlNode *a_node)
    {
        xmlNode *cur_node = NULL;

        for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
            if (cur_node->type == XML_ELEMENT_NODE) {
                std::string name(reinterpret_cast<const char *>(cur_node->name));
                if (name == "a") {
                    xmlChar *hrefProp = xmlGetProp(cur_node, (const xmlChar *)"href");
                    std::wstring href = xmlCharToWideString(hrefProp);
                    xmlFree(hrefProp);
                    std::wstring text = xmlCharToWideString(cur_node->children->content);
                    links.emplace_back(Link(href, text));
                }
            }

            collectLinks(links, cur_node->children);
        }
    }

    /**
    * @see
    * https://stackoverflow.com/questions/14107268/libxml2-xmlchar-to-stdwstring
    */
    std::wstring xmlCharToWideString(const xmlChar *xmlString)
    {
        if (!xmlString) {
            abort();
        } // provided string was null
        try {
            std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> conv;
            return conv.from_bytes((const char *)xmlString);
        } catch (const std::range_error &e) {
            abort(); // wstring_convert failed
        }
    }
};
