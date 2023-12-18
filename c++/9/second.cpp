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
#include <numeric>
#include <array>
#include <unordered_set>

using uli = long long int;
using sequence = std::vector<uli>;

uli extrapolate_data(sequence original_sequence)
{
    std::vector<sequence> sequences;
    sequences.push_back(original_sequence);
    // lambda function to differences in the sequence
    auto get_difference_in_sequence = [](sequence n) -> sequence
    {
        sequence d_;

        for (size_t i = 0; i < n.size() - 1; i++)
        {
            d_.push_back(n[i + 1] - n[i]);
        }

        return d_;
    };

    // lambda function to check if all elements in a sequence are equal to zero
    auto all_equal = [](sequence n) -> bool
    {
        for (size_t i = 0; i < n.size(); i++)
        {
            if (n[i] != 0)
            {
                return false;
            }
        }
        return true;
    };

    while (!all_equal(sequences.back()))
    {
        auto n = get_difference_in_sequence(sequences.back());
        sequences.push_back(n);
    }

    uli last_value_2 = 0;
    for (auto &seq : std::ranges::views::reverse(sequences))
    {
        last_value_2 = seq.front() - last_value_2;
    }

    return last_value_2;
}

int main(int argc, char **argv)
{
    std::string filename = "../input";

    if (argc == 2)
    {
        filename = argv[1];
    }

    std::ifstream input_file(filename, std::ios::in);
    std::string tmp;

    uli sum = 0;

    while (getline(input_file, tmp))
    {
        sequence numbers_;

        std::istringstream iss(tmp);
        std::string token;

        while (getline(iss, token, ' '))
        {
            if (token == "")
            {
                continue;
            }
            numbers_.push_back(std::stoll(token));
        }
        sum += extrapolate_data(numbers_);
    }

    std::cout << "Sum " << sum << std::endl;
}