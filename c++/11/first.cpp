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

std::vector<std::string> expand_universe(std::vector<std::string> universe, std::vector<size_t> rows_to_expand, std::vector<size_t> columns_to_expand)
{
    // expand rows of the universe
    std::string empty_row(universe[0].size(), '.');

    int row_already_expanded = 0;
    for (auto const rows_to_expand_index : rows_to_expand)
    {
        universe.insert(universe.begin() + rows_to_expand_index + row_already_expanded++, empty_row);
    }

    std::vector<std::string> tmp_universe;

    std::sort(columns_to_expand.begin(), columns_to_expand.end());

    si columns_already_added = 0;
    for (auto &cl : columns_to_expand)
    {
        cl += columns_already_added++;
    }

    for (auto const &row : universe)
    {
        std::string tmp_row;
        tmp_row.resize(row.size() + columns_to_expand.size());

        auto it = row.begin();

        size_t pos = 0;
        for (auto &ch : tmp_row)
        {
            if (std::find(columns_to_expand.begin(), columns_to_expand.end(), pos) != columns_to_expand.end())
            {
                ch = '.';
                columns_already_added++;
            }
            else
            {
                ch = *it;
                it++;
            }
            pos++;
        }

        tmp_universe.push_back(tmp_row);
    }

    return tmp_universe;
}

std::vector<std::tuple<int, int, int>> get_galaxies_location(std::vector<std::string> universe)
{
    std::vector<std::tuple<int, int, int>> galaxies_location;
    uli number_galaxies_ = 1;
    for (size_t i = 0; i < universe.size(); i++)
    {
        for (size_t j = 0; j < universe[i].size(); j++)
        {
            if (universe[i][j] == '#')
            {
                std::cout << "galaxy " << number_galaxies_ << " at " << i << " " << j << std::endl;
                galaxies_location.push_back({number_galaxies_++, i, j});
            }
        }
    }

    return galaxies_location;
}

int main(int argc, char **argv)
{
    std::string filename = "input";

    if (argc == 2)
    {
        filename = argv[1];
    }

    std::ifstream input_file(filename);
    std::string tmp;

    std::vector<std::string> map;
    std::vector<size_t> column_not_to_expand;
    std::vector<size_t> row_to_expand;

    size_t row = 0;
    while (std::getline(input_file, tmp))
    {
        // create map
        map.push_back(tmp);

        // check if row contains a galaxy
        if (tmp.find_first_of('#') == std::string::npos)
        {
            row_to_expand.push_back(row);
        }

        // check if column contains a galaxy
        size_t pos_ = 0;
        while ((pos_ = tmp.find('#', pos_)) != std::string::npos)
        {
            auto it = std::find(column_not_to_expand.begin(), column_not_to_expand.end(), pos_);

            if (it == column_not_to_expand.end())
                column_not_to_expand.push_back(pos_);
            pos_++;
        }

        row++;
    }

    std::sort(column_not_to_expand.begin(), column_not_to_expand.end());

    std::vector<size_t> column_to_expand;

    for (uli i = 0; i < map[0].size(); i++)
    {
        if (std::find(column_not_to_expand.begin(), column_not_to_expand.end(), i) == column_not_to_expand.end())
        {
            column_to_expand.push_back(i);
        }
    }

    map = expand_universe(map, row_to_expand, column_to_expand);

    std::vector<std::tuple<int, int, int>> galaxies_location = get_galaxies_location(map);

    uli sum = 0;

    for (auto it = galaxies_location.begin(); it != galaxies_location.end(); it++)
    {
        for (auto it2 = it + 1; it2 != galaxies_location.end(); it2++)
        {
            std::cout << std::get<0>(*it) << " " << std::get<0>(*it2) << " " << std::abs(std::get<1>(*it) - std::get<1>(*it2)) + std::abs(std::get<2>(*it) - std::get<2>(*it2)) << std::endl;
            sum += std::abs(std::get<1>(*it) - std::get<1>(*it2)) + std::abs(std::get<2>(*it) - std::get<2>(*it2));
        }
    }

    std::cout << sum << std::endl;
    return 0;
}