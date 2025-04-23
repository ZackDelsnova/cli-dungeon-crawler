#pragma once
#include <string>

namespace utils {
    //more miscellaneous function if added here
    int getValidatedInput(int min = INT_MIN, int max = INT_MAX);
    std::string formatName(const std::string& name);
}