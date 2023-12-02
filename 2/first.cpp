#include <list>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

unsigned long long int parse_game(std::string game, std::map<std::string, unsigned int> max_color_map)
{
    std::string string_to_remove = "Game ";

    game.erase(game.begin(), game.begin() + string_to_remove.size());

    size_t split_pos = game.find(":");

    std::string gn = game.substr(0, split_pos);
    unsigned long long int game_number = std::stoull(gn);

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

            if (color_number > max_color_map[color_string])
            {
                return 0;
            }
        }
    }

    return game_number;
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

    std::map<std::string, unsigned int> max_color_map = {{"red", 12}, {"green", 13}, {"blue", 14}};

    if (file.is_open())
    {
        std::string tmp;
        while (getline(file, tmp))
        {
            sum += parse_game(tmp, max_color_map);
        }

        std::cout << "Sum: " << sum << std::endl;
        return 0;
    }

    std::cout << "Error opening file" << std::endl;
    return 1;
}