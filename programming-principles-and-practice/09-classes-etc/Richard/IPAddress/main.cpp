#include <boost/regex.hpp>
// remember to include the file /usr/lib64/libboost_regex.so in the additional linker files

using namespace boost;
using namespace std;

int main() {
    regex IPv4Pattern{R"(^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$)"};
    string ip1 = "192.168.0.1";
    string ip2 = "7000.168.0.1";
    string ip3 = "192.168.0";
    string ip4 = "192.168.0.1:22";
    cout << ip1 << " regex_match "
            << regex_match(ip1, IPv4Pattern) << '\n';
    cout << ip2 << " regex_match "
            << regex_match(ip2, IPv4Pattern) << '\n';
    cout << ip3 << " regex_match "
            << regex_match(ip3, IPv4Pattern) << '\n';
    cout << ip4 << " regex_match "
            << regex_match(ip4, IPv4Pattern) << '\n';

    regex IPv4ExtractPattern{R"(^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})$)"};
    smatch matches;
    if (regex_search(ip1, matches, IPv4ExtractPattern)) {
        cout << matches.size() << " matches\n";
        for (int i = 0; i < matches.size(); ++i) {
            cout << "matches[" << i << "] = " << matches[i] << '\n';
        }
    }

    smatch matches2;
    if (regex_search(ip2, matches2, IPv4ExtractPattern)) {
        cout << matches2.size() << " matches\n";
        for (int i = 0; i < matches2.size(); ++i) {
            cout << "matches[" << i << "] = " << matches[i] << '\n';
        }
    }
    return 0;
}