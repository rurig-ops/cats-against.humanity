#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

/** * @brief FUNCTIE SABLON: Afiseaza un mesaj de logare pentru orice tip de data (T).
 * @details Utilizeaza incarcarea statica pentru a functiona cu orice tip ce suporta operatorul <<.
 */
template <typename T>
void logGameEvent(const std::string& label, const T& data) {
    std::cout << "[GAME LOG] " << label << ": " << data << std::endl;
}

#endif