#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <cmath>

unsigned long long int decode_game(std::string game)
{
    // Dont care about game number
    game.erase(game.begin(), game.begin() + game.find_first_of(":") + 1);

    size_t split_pos = game.find_first_of("|");

    auto lucky_numbers_str = game.substr(0, split_pos);
    auto current_numbers_str = game.substr(split_pos + 1, game.size() - split_pos + 1);

    auto number_split = [](std::string str) -> std::vector<int>
    {
        std::vector<int> number_;
        std::istringstream iss_(str);
        std::string tmp_;
        while (getline(iss_, tmp_, ' '))
        {
            if (tmp_ != "")
                number_.push_back(std::stoi(tmp_));
        }
        return number_;
    };

    auto lucky_numbers = number_split(lucky_numbers_str);
    auto current_numbers = number_split(current_numbers_str);

    int number_of_lucky_numbers_in_plot = std::count_if(current_numbers.begin(), current_numbers.end(), [lucky_numbers](int number) -> bool
                                                        { return (std::find(lucky_numbers.begin(), lucky_numbers.end(), number) != lucky_numbers.end()); });

    unsigned long long int sum = number_of_lucky_numbers_in_plot > 0 ? std::pow(2, --number_of_lucky_numbers_in_plot) : 0;

    return sum;
}

int main(int argc, char **argv)
{
    std::string filename = "first_input_real.txt";

    if (argc == 2)
    {
        filename = std::string(argv[1]);
    }

    unsigned long long int sum = 0;

    std::ifstream file(filename, std::ios::in);
    std::string tmp;

    while (getline(file, tmp))
    {
        sum += decode_game(tmp);
    }

    std::cout << "Sum: " << sum << std::endl;
}
