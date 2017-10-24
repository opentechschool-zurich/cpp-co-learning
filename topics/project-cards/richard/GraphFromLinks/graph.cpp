#include <iostream>
#include "Link.h"
#include "webServer.h"

/**
 * Pulls the supplied web page and outputs the links it finds on the page
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "Usage: graph URL\n";
        return 1;
    }
    std::string url = argv[1];

    Link rootLink = Link{url, L"Root Node"};
    rootLink.parseLinks();
    WebServer w{rootLink};
    w.start();

    return 0;
}
