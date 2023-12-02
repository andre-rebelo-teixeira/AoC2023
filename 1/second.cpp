#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <string_view>

unsigned long long int parse_string(std::string str)
{
    constexpr std::array<std::string_view, 9> digitWords = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    std::string tmp;

    for (size_t i = 0; i < str.size(); i++)
    {
        if (isdigit(str[i]))
        {
            tmp += (str[i]);
        }
        else
        {
            for (unsigned int j = 0; j < digitWords.size(); j++)
            {
                if (const auto &w = digitWords[j]; !str.compare(i, w.size(), w))
                {
                    tmp += std::to_string(j + 1);
                    break;
                }
            }
        }
    }

    return stoull(std::string(tmp.substr(0, 1) + tmp.substr(tmp.size() - 1, 1)));
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
            sum += parse_string(tmp);
        }
        std::cout << "Sum: " << sum << "\n";
        return 0;
    }
    else
    {
        std::cout << "Error opening file\n";
        return 1;
    }
}