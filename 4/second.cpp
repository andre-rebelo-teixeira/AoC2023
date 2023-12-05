#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <cmath>

int decode_game(std::string game)
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

    return number_of_lucky_numbers_in_plot;
}

// 7 185 540

int main(int argc, char **argv)
{
    std::string filename = "second_input_real.txt";

    if (argc == 2)
    {
        filename = std::string(argv[1]);
    }

    unsigned long long int sum = 0;

    std::ifstream file(filename, std::ios::in);
    std::string tmp;

    std::map<int, int> num_of_copies;
    std::map<int, int> points_in_card;

    int current_game = 1;

    while (getline(file, tmp))
    {
        points_in_card.insert(std::make_pair(current_game, decode_game(tmp)));
        num_of_copies.insert(std::make_pair(current_game++, 1));
    }

    if (points_in_card.size() != num_of_copies.size())
    {
        std::cout << "Error: points_in_card.size() != num_of_copies.size()" << std::endl;
        return 1;
    }

    for (auto &pair : points_in_card)
    {
        std::cout << pair.first - 1 << " " << num_of_copies[pair.first] << std::endl;
        if (pair.second == 0)
            continue;

        for (int i = pair.first + 1; i <= pair.first + pair.second && i <= num_of_copies.size(); i++)
        {
            num_of_copies[i] += num_of_copies[pair.first];
        }
    }

    // for (auto &pair : points_in_card)
    //{
    //     for (int i = 1; i < pair.second; i++)
    //     {
    //         num_of_copies[pair.first + i] += pair.second * num_of_copies[pair.first];
    //     }
    // }

    for (auto &pair : num_of_copies)
    {
        sum += pair.second;
        //        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << sum << std::endl;
}
