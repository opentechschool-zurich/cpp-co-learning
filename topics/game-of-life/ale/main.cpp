#include <cassert>
#include <cmath>
#include <set>
#include <numeric>
#include <algorithm>
#include <iostream>

#include <string>

#include <chrono>
#include <thread>

using namespace std::literals;

struct Cell
{
    int x;
    int y;

    std::string to_string() const {
        return "{" + std::to_string(x) + ", "  + std::to_string(y) + "}";
    }
};

bool operator==(const Cell& lhs, const Cell& rhs)
{
        return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator<(const Cell &lhs, const Cell &rhs)
{
        return lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x);;
}

std::ostream& operator<<(std::ostream& os, const Cell& c)
{
        return os << c.to_string();
}

using World = std::set<Cell>;

std::ostream& operator<<(std::ostream& os, const World& world)
{
    return os << "{" << *world.begin() << std::accumulate(std::next(world.begin()), world.end(), ""s,
        [](const auto& a, const auto& i) {return a + ", " + i.to_string();}) << "}";
}

bool is_neighbour(const Cell& c, const Cell& n)
{
    if (c.x == n.x && c.y == n.y) {
        return false;
    }
    return abs(c.x - n.x) <= 1 && abs(c.y - n.y) <= 1;
}

int count_neighbours(const Cell& c, const World& cells)
{
    if (cells.empty()) {
        return 0;
    }
    return std::accumulate(cells.begin(), cells.end(), 0,
        [&c](int a, Cell i) {return a + (is_neighbour(c, i) ? 1 : 0);});
}

World get_neighbours(const Cell& c)
{
    return {{c.x - 1, c.y - 1}, {c.x - 1, c.y} , {c.x - 1, c.y + 1},
        {c.x, c.y - 1}, {c.x - 1, c.y + 1},
        {c.x + 1, c.y - 1}, {c.x + 1, c.y} , {c.x + 1, c.y + 1}};
}

World next_generation(const World& world)
{
    World next_world{};
    for (const auto cell: world) {
        const int n = count_neighbours(cell, world);
        if (n == 2 || n == 3) {
            next_world.insert(cell);
        }
        for (const auto neighbour: get_neighbours(cell)) {
            if (world.find(neighbour) == world.end() && count_neighbours(neighbour, world) == 3) {
                next_world.insert(neighbour);
            }
        }
    }
    return next_world;
}

void display(const World& world) {
    auto min = *world.begin();
    auto max = *std::prev(world.end());
    for (const auto& cell: world) {
        if (min.x > cell.x) {
            min.x = cell.x;
        }
        if (max.x < cell.x) {
            max.x = cell.x;
        }
    }
    std::string out{};
    auto cell_it = world.begin();
    for (int i = 0; i <= max.y; i++) {
        for (int j = 0; j <= max.x; j++) {
            if ((*cell_it).y == i && (*cell_it).x == j) {
                // out += "+";
                out += "■";
                cell_it = std::next(cell_it);
            } else {
                out += " ";
            }
        }
        out += "\n";
    }
    std::cout << out;
}

int main()
{
    assert(is_neighbour({1, 1}, {1, 2}) == true); // neighbour is neighbour
    assert(is_neighbour({1, 1}, {4, 4}) == false); // not neighbour is not neighbour
    assert(is_neighbour({1, 1}, {1, 1}) == false); // self is not neighbour
    assert(count_neighbours({1, 1}, {{1, 2}}) == 1); // count one neighbour
    assert(count_neighbours({1, 1}, {{1, 2}, {2, 1}, {4, 4}}) == 2); // count two neighbours and one non neighbour
    assert(next_generation({{1, 1}}).size() == 0); // lonely cell dies
    {
        auto next = next_generation({{1, 1}, {1, 2}, {2, 1}});
        assert(next.find(Cell{1, 1}) != next.end()); // cell with two neighbours survives
    }
    {
        auto next = next_generation({{1, 1}, {1, 2}, {2, 1}, {2, 2}, {4, 4}});
        assert(next.find(Cell{1, 1}) != next.end()); // cell with three neighbours survives
    }
    {
        auto next = next_generation({{1, 1}, {1, 2}, {2, 1}, {4, 4}});
        assert(next.find(Cell{2, 2}) != next.end()); // dead cell with three neighbours becomes alive
    }
    {
        int count{0};
        for (const Cell& cell: next_generation({{1, 1}, {1, 2}, {2, 1}, {4, 4}})) {
            if (cell.x == 2 && cell.y == 2) {
                count++;
            }
        }
        assert(count == 1); // dead cell coming to life is only added once
    }
    // blinker
    {
        World start = {{2, 1}, {2, 2}, {2, 3}};
        auto next = next_generation(start);
        auto second = World{{1, 2}, {2, 2}, {3, 2}};
        assert(next == second); // blinker turns
        next = next_generation(next);
        assert(next == start); // blinker turns
    }
    // display an animation
    {
        World world = {{2, 1}, {2, 2}, {2, 3}}; // blinker
        // World world = {{2, 0}, {2, 1}, {2, 2}, {1, 2}, {0, 1}}; // glider
        // int x = 3, y = 3;
        // World world = {{x + 1, y + 0}, {x + 1, y + 1}, {x + 0, y + 2}, {x + 2, y + 2}, {x + 1, y + 3}, {x + 1, y + 4}, {x + 1, y + 5}, {x + 1, y + 6}, {x + 0, y + 7}, {x + 2, y + 7}, {x + 1, y + 8}, {x + 1, y + 9}}; //  penta-decathlon
        for (int i = 0; i < 20; i++) {
            std::cout << "\033[2J\033[1;1H" << std::flush;
            display(world);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            world = next_generation(world);
        }
    }
}
