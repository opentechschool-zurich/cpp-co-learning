#pragma once

#include <iostream>

class Link
{
public:
    Link(std::wstring href, std::wstring text) : href(href), text(text){};
    std::wstring href;
    std::wstring text;
};
