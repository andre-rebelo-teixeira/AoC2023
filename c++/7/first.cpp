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

using uli = unsigned long long int;

enum Rank
{
    None,
    FiveOfAKind,
    FourOfAKind,
    FullHouse,
    ThreeOfAKind,
    TwoPair,
    OnePair,
    HighCard
};

struct hand
{
    std::array<std::string, 5> cards;
    std::string play;
    unsigned int bid;
};

unsigned int
get_card_value(const char c)
{
    switch (c)
    {
    case 'A':
        return 14;
    case 'K':
        return 13;
    case 'Q':
        return 12;
    case 'J':
        return 11;
    case 'T':
        return 10;
    default:
        return c - '0';
    }
}

Rank decode_card_type(std::string play)
{
    std::map<char, int> card_to_count;

    for (auto c : play)
    {
        if (card_to_count.find(c) == card_to_count.end())
        {
            card_to_count[c] = 1;
        }
        else
        {
            card_to_count[c]++;
        }
    }

    // only on card
    if (card_to_count.size() == 1) // 1 card in deck
    {
        return Rank::FiveOfAKind;
    }
    else if (card_to_count.size() == 2) // two cards in deck
    {
        for (auto const &[c, count] : card_to_count)
        {
            if (count == 4 || count == 1)
                return Rank::FourOfAKind;
            else if (count == 2 || count == 3)
                return Rank::FullHouse;
        }
    }
    else if (card_to_count.size() == 3)
    {
        for (auto const &[c, count] : card_to_count)
        {
            if (count == 3)
                return Rank::ThreeOfAKind;
            else if (count == 2)
                return Rank::TwoPair;
        }
    }
    else if (card_to_count.size() == 4)
    {
        return Rank::OnePair;
    }
    else if (card_to_count.size() == 5)
    {
        return Rank::HighCard;
    }

    return Rank::None;
}

int main(int argc, char **argv)
{
    std::string input_file_name = "input";

    if (argc == 2)
    {
        input_file_name = argv[1];
    }

    std::ifstream input_file(input_file_name, std::ios::in);
    std::string tmp;

    std::map<std::string, uli> hands;
    std::map<Rank, std::vector<std::pair<std::string, uli>>> hands_rank_unordered;

    while (getline(input_file, tmp))
    {
        std::string name = tmp.substr(0, tmp.find_first_of(" "));
        uli bid = std::stoull(tmp.substr(tmp.find_first_of(" ") + 1));

        Rank current_card_rank = decode_card_type(name);

        if (current_card_rank == Rank::None)
        {
            std::cout << "Error: " << name << std::endl;
            return 1;
        }

        if (hands_rank_unordered.find(current_card_rank) == hands_rank_unordered.end())
        {
            hands_rank_unordered[current_card_rank].push_back(std::make_pair(name, bid));
        }
        else
        {
            hands_rank_unordered[current_card_rank].push_back(std::make_pair(name, bid));
        }
    }

    auto compare_string = [](auto &left, auto &right) -> bool
    {
        for (auto [l, r] : std::ranges::views::zip(left.first, right.first))
        {
            if (get_card_value(l) < get_card_value(r))
                return true;
            else if (get_card_value(l) > get_card_value(r))
                return false;
        }
        return true;
    };

    for (auto &[rank, hands] : hands_rank_unordered)
    {
        std::sort(hands.begin(), hands.end(), compare_string);
    }

    // get final result
    uli final_count = 0;
    uli current_multiplier = 1;

    auto reverse_map(hands_rank_unordered | std::ranges::views::reverse);

    for (auto &[rank, hands] : reverse_map)
    {
        for (auto &[name, bid] : hands)
        {
            final_count += bid * current_multiplier++;
        }
    }

    std::cout << "final count " << final_count << std::endl;
    return 0;
}