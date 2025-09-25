//
//  AmigaOS C++ wrapper
//
//  (c) 2024-2025 TDolphin
//

#pragma once

#include <string>

#include "Singleton.hpp"

class RandomCore
{
    friend class td::Singleton<RandomCore>;

    RandomCore();

  public:
    std::string Randomize();
};

typedef class td::Singleton<RandomCore> Random;
