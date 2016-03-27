#include <boost/regex.hpp>
// remember to include the file /usr/lib64/libboost_regex.so in the additional linker files
using namespace boost;
using namespace std;

int main() {
    regex ISBNPattern{ R"(^\d+-\d+-\d+-\d+-\d$)" };
    string isbn1 = "978-0-321-99278-9";
    string isbn2 = "978-0-321-99278";
    cout << isbn1 << " regex_match "
            << regex_match(isbn1, ISBNPattern) << '\n';
    cout << isbn2 << " regex_match "
            << regex_match(isbn2, ISBNPattern) << '\n';
    return 0;
}
