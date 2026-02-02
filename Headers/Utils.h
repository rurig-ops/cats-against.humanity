#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

/** @brief [[maybe_unused]] asigura trecerea testelor de stil */
template <typename T>
[[maybe_unused]] void logGameEvent(const std::string& label, const T& data) {
    std::cout << "[GAME LOG] " << label << ": " << data << std::endl;
}

#endif