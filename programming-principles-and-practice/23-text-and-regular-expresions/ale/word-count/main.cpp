#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

template <typename Map>
bool map_compare (Map const &lhs, Map const &rhs) {
    // No predicate needed because there is operator== for pairs already.
    return lhs.size() == rhs.size()
        && std::equal(lhs.begin(), lhs.end(),
                      rhs.begin());
}

namespace word_count {

    vector<string> split(string sentence) {
        string buffer;
        stringstream ss(sentence);
        vector<string> tokens;

        while (ss >> buffer)
            tokens.push_back(buffer);
        return tokens;
    }

    map<string, int> words(string sentence) {
        map<string, int> result {};
        for (auto word: split(sentence)) {
            auto it = result.insert({word, 1});
            if (it.second == false) {
                (*it.first).second++;
            }
        }
        return result;
    }
}

int main() {
    {
        const map<string, int> expected{{"word", 1}};
        const auto actual = word_count::words("word");
        if (!map_compare(expected, actual)) {
            cout << "counts_one_word" << endl;
        }
    }

    {
        const map<string, int> expected{{"one", 1}, {"of", 1}, {"each", 1}};
        const auto actual = word_count::words("one of each");
        if (!map_compare(expected, actual)) {
            cout << "counts_one_of_each" << endl;
        }
    }

    {
        const map<string, int> expected{{"one", 1}, {"fish", 4}, {"two", 1}, {"red", 1}, {"blue", 1}};
        const auto actual = word_count::words("one fish two fish red fish blue fish");
        if (!map_compare(expected, actual)) {
            cout << "counts_multiple_occurences" << endl;
        }
    }

    return  0;
}
