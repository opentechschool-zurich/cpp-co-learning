#pragma once

#include <iostream>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;

#include <locale>
#include <codecvt>
/**
* @see
* https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
*/
std::string wstringToString(const std::wstring ws)
{
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    return converter.to_bytes(ws);
}

class Link
{
public:
    Link(std::wstring href, std::wstring text) : href(href), text(text), node(counter++){};
    std::wstring href;
    std::wstring text;
    int node;
    std::vector<Link> children;
    json toJson() const {
        json j = { { "href", wstringToString( href ) },
         { "text", wstringToString( text ) },
         { "node", node }
       };
        for ( auto child : children ) {
            j["children"].push_back(  {
              { "href", wstringToString( child.href ) },
              { "text", wstringToString( child.text ) },
            {"node",child.node} } );
        }
        return j;
    }

private:
  static int counter;
};
int Link::counter = 0;
