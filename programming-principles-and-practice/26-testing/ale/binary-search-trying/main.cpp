#include <vector>
#include <iterator>
#include <iostream>

using namespace std;

/**
 * search inside of a sorted a vector an element that we know exists
 */
vector<int>::const_iterator  binary_search(const vector<int>::const_iterator start, const vector<int>::const_iterator end, int value)
{
    auto n = end - start;
    auto middle = start + ((end - start) / 2);
    if (*middle > value) {
        return binary_search(start, middle - 1, value);
    } else if (*middle < value) {
        return binary_search(middle + 1, end, value);
    } else {
        return middle;
    }
}

int main(){

    vector<int> list{1,2,3,4};

    int search = 1;
    auto element = binary_search(list.begin(), list.end(), search);
    cout << "element is " << search << ": " << *element << endl;

    return 0;
}
