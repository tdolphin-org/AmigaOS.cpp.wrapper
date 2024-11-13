//
//  AmigaOS C++ wrapper
//
//  (c) 2024 TDolphin
//

#include "Random.hpp"

#include <ctime>

RandomCore::RandomCore()
{
    srand((unsigned)std::time(0));
}

std::string RandomCore::Randomize()
{
    return std::to_string(rand());
}