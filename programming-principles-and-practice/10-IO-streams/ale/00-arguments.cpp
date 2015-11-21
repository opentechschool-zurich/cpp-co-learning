#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    cout << "argc " << argc << endl;
    cout << "exec " << argv[0] << endl;
    if (argc == 2) {
        cout << "filename " << argv[1] << endl;
    }
}
