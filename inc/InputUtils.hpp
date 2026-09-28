#ifndef INPUT_UTILS_HPP
#define INPUT_UTILS_HPP

#include <iostream>
#include <limits>
#include <string>

//Used for reading an int input from user
//This avoids bad input such as any character other than integer
//Which causes failbit to enable, leading to infinite loop of program
//This class handles integer input safely
class InputUtils {
public:
    static int readInt(const std::string& prompt) {
        int value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input, please enter a number.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
};


#endif
