#include <list>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

unsigned long long int parse_game(std::string game)
{
    std::string string_to_remove = "Game ";

    std::map<std::string, unsigned int> min_possible_number_of_dices = {{"red", 0}, {"green", 0}, {"blue", 0}};

    game.erase(game.begin(), game.begin() + string_to_remove.size());

    size_t split_pos = game.find(":");

    std::istringstream game_data_stream(game.substr(split_pos + 1, game.size() - split_pos));

    std::string tmp;
    char delimiter_1 = ';';

    while (getline(game_data_stream, tmp, delimiter_1))
    {
        char delimiter_2 = ',';
        std::string tmp_color;
        std::istringstream tmp_stream(tmp);

        while (getline(tmp_stream, tmp_color, delimiter_2))
        {
            size_t pos = (tmp_color.find_last_of(" "));

            unsigned long int color_number = std::stoul(tmp_color.substr(0, pos));

            std::string color_string = tmp_color.substr(pos + 1, tmp_color.size() - pos);

            min_possible_number_of_dices[color_string] = (color_number > min_possible_number_of_dices[color_string] ? color_number : min_possible_number_of_dices[color_string]);
        }
    }

    unsigned long long int game_dices_value = 1;
    for (auto const &[key, val] : min_possible_number_of_dices)
    {
        game_dices_value *= val;
    }
    return game_dices_value;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    std::ifstream file(std::string(argv[1]), std::ios::in);

    unsigned long long int sum = 0;

    if (file.is_open())
    {
        std::string tmp;
        while (getline(file, tmp))
        {
            sum += parse_game(tmp);
        }

        std::cout << "Sum: " << sum << std::endl;
        return 0;
    }

    std::cout << "Error opening file" << std::endl;
    return 1;
}