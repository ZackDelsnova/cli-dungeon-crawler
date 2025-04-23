#include "utils.h"
#include <iostream>
#include <limits>
#include <cctype>

namespace utils {
    int getValidatedInput(int min, int max) {
        int choice;
        while (true) {
            std::cin >> choice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Please enter a valid number!\n> ";
                continue;
            }

            if (choice < min || choice > max) {
                std::cout << "Please enter a number between " << min << " and " << max << "!\n> ";
                continue;
            }

            return choice;
        }
    }

    std::string formatName(const std::string& name) {
        std::string formatted = name;
        bool newWord = true;
        for (char& ch : formatted) {
            if (std::isspace(ch)) {
                newWord = true;
            } else if (newWord) {
                ch = std::toupper(ch);
                newWord = false;
            } else {
                ch = std::tolower(ch);
            }
        }
        return formatted;
    }
}