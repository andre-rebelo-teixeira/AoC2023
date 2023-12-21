#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <cmath>
#include <tuple>
#include <list>
#include <ranges>
#include <queue>
#include <numeric>
#include <array>
#include <unordered_set>
#include <iomanip>

using uli = unsigned long int;
using ui = unsigned int;
using si = short int;

std::vector<std::string> map;
si x_max;
si y_max;
int **d;

std::vector<std::pair<si, si>> get_neighbors(si x, si y)
{
    switch (map[x][y])
    {
    case '|':
        return {{x - 1, y}, {x + 1, y}};
    case '-':
        return {{x, y - 1}, {x, y + 1}};
    case 'L':
        return {{x - 1, y}, {x, y + 1}};
    case 'J':
        return {{x - 1, y}, {x, y - 1}};
    case '7':
        return {{x + 1, y}, {x, y - 1}};
    case 'F':
        return {{x + 1, y}, {x, y + 1}};
    default:
        throw std::exception();
    }
}

bool is_a_pipe(int x, int y)
{
    return (x >= 0 && y >= 0 && x < x_max && y < y_max && map[x][y] != '.');
}

int flood_fill(si x, si y)
{
    std::queue<std::pair<int, int>> prev_numbers;
    prev_numbers.emplace(x, y);

    int current_max = 0;

    d = new int *[x_max];
    for (int i = 0; i < x_max; i++)
    {
        d[i] = new int[y_max];
        for (int j = 0; j < y_max; j++)
        {
            d[i][j] = std::numeric_limits<int>::max();
        }
    }

    d[x][y] = current_max;

    while (!prev_numbers.empty())
    {
        int i = prev_numbers.front().first;
        int j = prev_numbers.front().second;

        prev_numbers.pop();

        current_max = std::max(current_max, d[i][j]);
        for (auto &p : get_neighbors(i, j))
        {
            if (is_a_pipe(p.first, p.second) && d[p.first][p.second] > d[i][j])
            {
                d[p.first][p.second] = d[i][j] + 1;
                prev_numbers.emplace(p);
            }
        }
    }

    return current_max;
}

int main(int argc, char **argv)
{
    std::string filename = "input";

    if (argc == 2)
    {
        filename = argv[1];
    }

    std::ifstream input_file(filename, std::ios::in);
    std::string tmp;

    std::tuple<uli, uli> s_position;

    si current_line = 0;
    while (getline(input_file, tmp))
    {
        if (tmp.find_first_of('S') != std::string::npos)
        {
            s_position = std::make_tuple(current_line, tmp.find_first_of('S'));
        }
        current_line++;
        map.push_back(tmp);
    }

    x_max = map[0].size();
    y_max = map.size();

    std::string s_letter = "F";

    // correct letter to be correct for the first iteration
    map[std::get<0>(s_position)][std::get<1>(s_position)] = s_letter[0];

    flood_fill(std::get<0>(s_position), std::get<1>(s_position));

    std::cout << "Max value " << flood_fill(std::get<0>(s_position), std::get<1>(s_position)) << std::endl;

    for (int i = 0; i < x_max; i++)
    {
        for (int j = 0; j < y_max; j++)
        {
            std::cout << std::setw(10) << d[i][j] << " ";
        }
    }

#ifdef DEBUG
    for (auto const &[k, v] : map)
    {
        if (v.size() != size)
        {
            std::cout << "Error: " << v << std::endl;
            return 1;
        }
    }
#endif
}
