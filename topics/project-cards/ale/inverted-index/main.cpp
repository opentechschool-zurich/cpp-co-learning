#include <string>
#include <vector>
#include <utility> // for pair
#include <iostream>
#include <regex>
#include <iterator>
#include <map>

std::vector<std::string> split(const std::string& input)
{
    std::vector<std::string> result;

    std::regex word_regex("(\\w+)");
    auto words_begin = 
        std::sregex_iterator(input.begin(), input.end(), word_regex);
    auto words_end = std::sregex_iterator();

    const int N = 1;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        if (match_str.size() > N) {
            result.push_back(match_str);
        }
    }
	return result;
}


int main()
{
    std::vector<std::pair <std::string, std::string> > files;
    files.push_back(std::make_pair("a.txt", "There are two main variants of inverted indexes: A record-level inverted index (or inverted file index or just inverted file) contains a list of references to documents for each word."));
    files.push_back(std::make_pair("b.txt", "A word-level inverted index (or full inverted index or inverted list) additionally contains the positions of each word within a document."));
    files.push_back(std::make_pair("c.txt", "The latter form offers more functionality (like phrase searches), but needs more processing power and space to be created."));

	std::map< std::string, std::vector<std::string> > index;

    for (auto file: files) {
        std::cout << file.first << std::endl;
        std::cout << file.second << std::endl;
		auto words = split(file.second);
		for (auto word: words) {
			// std::cout << word << std::endl;
            try {
                index.at(word).push_back(file.first);
            } catch (const std::out_of_range& e) {
                index[word] = {file.first};
            }
		}
    }

    for (auto file: index["index"]) {
        std::cout << file << std::endl;
    }

}
