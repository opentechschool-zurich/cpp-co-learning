#include <vector>
#include <utility>
// #include <unordered_map>
#include <set>
#include <iostream>
#include <cassert>

using Vertices = std::vector<std::pair<int, int>>;

bool is_it_a_tree(const Vertices& vertices) {
    // we are assuming the first vertice starts at the root
    std::set<int> targets{vertices.front().first};
    for (auto pair: vertices) {
        if (!targets.contains(pair.first)) {
            return false;
        }

        if (targets.contains(pair.second)) {
            return false;
        }
        targets.insert(pair.second);
    }
    return true;
}

int main() {
    Vertices vertices = {
        {1,2},
        {2,3},
        {2,4},
        {1,5},
    };

    bool its_a_tree = is_it_a_tree(vertices);

    std::cout << "it's" << (its_a_tree ? "" : " not") << " a tree" << std::endl;

    assert(is_it_a_tree(vertices) == true);
    vertices.push_back({6, 7});
    assert(is_it_a_tree(vertices) == false);
    vertices.pop_back();
    vertices.push_back({2, 1});
    assert(is_it_a_tree(vertices) == false);
    vertices.pop_back();
    vertices.push_back({1, 4});
    assert(is_it_a_tree(vertices) == false);
}

    // std::unordered_map<int, std::vector<int>> tree{};
    // for (auto pair: vertices) {
    //     tree[pair.first].push_back(pair.second);
    // }
