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
#include <cstdlib>

using uli = unsigned long int;
using ui = unsigned int;
using si = short int;
using galaxy = std::tuple<int, int, int>;

/* Get line universe and gives vector with galaxy position*/
std::vector<galaxy> find_galaxy(std::string line_universe, size_t row, std::vector<size_t> &column_to_expand, uli num_galaxies_found)
{
    std::vector<galaxy> g;

    for (size_t i = 0; i < line_universe.size(); i++)
    {
        if (line_universe[i] == '#')
        {
            g.push_back(std::make_tuple(num_galaxies_found++, row, i));
            auto it = std::remove_if(column_to_expand.begin(), column_to_expand.end(), [i](auto const &c) -> bool
                                     { return c == i; });       // get value to remove
            column_to_expand.erase(it, column_to_expand.end()); // remove value
        }
    }

    return g;
}

int main(int argc, char **argv)
{
    std::string filename = "input";
    uli conversion_factor = 1000000;

    switch (argc)
    {
    case 2:
        conversion_factor = std::atoi(argv[1]);
        break;
    case 3:
        conversion_factor = std::atoi(argv[2]);
        filename = argv[1];
        break;
    default:
        break;
    }

    std::ifstream input_file(filename);
    std::string tmp;
    getline(input_file, tmp);

    size_t universe_line_size = tmp.size();

    // reset file location
    input_file.seekg(0, std::ios::beg);

    std::vector<size_t> column_to_expand(universe_line_size, 0);
    std::iota(column_to_expand.begin(), column_to_expand.end(), 0);

    std::vector<galaxy> galaxies_location;

    size_t row = 0;
    while (std::getline(input_file, tmp))
    {
        auto g = find_galaxy(tmp, row, column_to_expand, galaxies_location.size() + 1);

        if (g.size() == 0)
        {
            row += conversion_factor - 1;
        }
        else
        {
            galaxies_location.insert(galaxies_location.end(), g.begin(), g.end());
        }

        row++;
    }

    std::cout << std::endl;

    for (auto &galaxy : galaxies_location)
    {
        auto count = std::count_if(column_to_expand.begin(), column_to_expand.end(), [galaxy](auto const &c) -> bool
                                   { return c < static_cast<long unsigned int>(std::get<2>(galaxy)); });

        std::get<2>(galaxy) += count * (conversion_factor - 1);
    }

    uli sum = 0;

    for (auto it = galaxies_location.begin(); it != galaxies_location.end(); it++)
    {
        for (auto it2 = it + 1; it2 != galaxies_location.end(); it2++)
        {
            //  std::cout << std::get<0>(*it) << " " << std::get<0>(*it2) << " " << std::abs(std::get<1>(*it) - std::get<1>(*it2)) + std::abs(std::get<2>(*it) - std::get<2>(*it2)) << std::endl;
            auto it1_x = std::get<1>(*it);
            auto it1_y = std::get<2>(*it);
            auto it2_x = std::get<1>(*it2);
            auto it2_y = std::get<2>(*it2);

            sum += std::abs(it1_x - it2_x) + std::abs(it1_y - it2_y);
        }
    }
    std::cout << sum << std::endl;

    return 0;
}
