#include <iostream>
#include <string>
#include <fstream>

#include <iostream>
#include <string>

std::string get_number_string(std::string string_to_parse_)
{
    std::string number_string;
    for (char ch : string_to_parse_)
    {
        if (isdigit(ch))
        {
            number_string += ch;
        }
    }
    std::string tmp = number_string.substr(0, 1) + number_string.substr(number_string.size() - 1, 1);
    return tmp;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    unsigned long long int sum = 0;
    std::string file_name = argv[1];

    std::ifstream file(file_name, std::ios::in);

    if (!file.is_open())
    {
        std::cout << "Error opening file\n";
        return 1;
    }
    else
    {
        std::string tmp;
        while (getline(file, tmp))
        {
            std::string number_string = get_number_string(tmp);
            sum += std::stoull(number_string);
        }
    }

    std::cout << "Sum: " << sum << "\n";
    return 0;
}