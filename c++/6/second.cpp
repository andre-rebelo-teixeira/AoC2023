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

    std::string time = "";
    std::string record = "";

    // get times line
    getline(input_file, tmp);

    tmp.erase(tmp.begin(), tmp.begin() + tmp.find_first_of(":") + 1);

    std::istringstream iss(tmp);

    while (getline(iss, tmp, ' '))
    {
        if (tmp != "")
            time += tmp;
    }

    // get records line
    getline(input_file, tmp);

    tmp.erase(tmp.begin(), tmp.begin() + tmp.find_first_of(":") + 1);

    iss = std::istringstream(tmp);

    while (getline(iss, tmp, ' '))
    {
        if (tmp != "")
            record += tmp;
    }

    std::cout << "time: " << time << std::endl;
    std::cout << "record: " << record << std::endl;

    uli t = std::stoull(time);
    uli r = std::stoull(record);

    uli num_of_victories = 1;

    std::vector<uli> velocities(t + 1);
    std::iota(std::begin(velocities), std::end(velocities), 0);

    num_of_victories = std::count_if(velocities.begin(), velocities.end(), [r, t](auto vel) -> bool
                                     { return vel * (t - vel) > r; });

    std::cout << num_of_victories << std::endl;
}
