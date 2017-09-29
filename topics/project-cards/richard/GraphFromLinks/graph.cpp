#include <iostream>
#include <vector>

#include "CurlWrapper.h"
#include "LinkParser.h"
#include "Link.h"

/**
 * Pulls the supplied web page and outputs the links it finds on the page
 */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout << "Usage: graph depth URL\n";
        return 1;
    }
    int depth = atoi(argv[1]);
    std::string url = argv[2];

    CurlWrapper w;
    std::string webPage = w.getPage(url);
    std::cout << "Downloaded URL: " << url << " (" << webPage.size() << " chars)" << std::endl;

    LinkParser p;
    std::vector<Link> links = p.parseLinks(webPage);

    for (auto l : links) {
        std::wcout << l.href << " - " << l.text << std::endl;
    }

    std::cout << links.size() << " links found on url: " << url << "\n";
    return 0;
}
