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

using uli = unsigned long long int;

int main(int argc, char **argv)
{
    std::string input_file_name = "input";

    if (argc == 2)
    {
        input_file_name = argv[1];
    }

    std::ifstream input_file(input_file_name, std::ios::in);
    std::string tmp;

    std::vector<uli> time;
    // get times line
    getline(input_file, tmp);

    tmp.erase(tmp.begin(), tmp.begin() + tmp.find_first_of(":") + 1);

    std::istringstream iss(tmp);

    while (getline(iss, tmp, ' '))
    {
        if (tmp != "")
            time.push_back(std::stoull(tmp));
    }

    std::vector<uli> record;
    // get records line
    getline(input_file, tmp);

    tmp.erase(tmp.begin(), tmp.begin() + tmp.find_first_of(":") + 1);

    iss = std::istringstream(tmp);

    while (getline(iss, tmp, ' '))
    {
        if (tmp != "")
            record.push_back(std::stoull(tmp));
    }

    if (time.size() != record.size())
    {
        std::cerr << "Invalid input file: " << input_file_name << std::endl;
        exit(1);
    }

    uli num_of_victories = 1;
    for (auto const [t, r] : std::views::zip(time, record))
    {
        uli current_victories = 0;

        std::vector<uli> velocities(t + 1);
        std::iota(std::begin(velocities), std::end(velocities), 0);

        current_victories = std::count_if(velocities.begin(), velocities.end(), [r, t](auto vel) -> bool
                                          { return vel * (t - vel) > r; });

        std::cout << "t: " << t << " r: " << r << " victories: " << current_victories << std::endl;
        num_of_victories *= current_victories;
    }

    std::cout << num_of_victories << std::endl;
}
