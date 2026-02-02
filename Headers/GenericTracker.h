#ifndef GENERICTRACKER_H
#define GENERICTRACKER_H

#include <vector>

/** * @class GenericTracker
 * @brief CLASA SABLON: Permite monitorizarea istoricului pentru orice tip de date (T).
 */
template <typename T>
class GenericTracker {
private:
    std::vector<T> history; ///< Container generic pentru stocarea datelor de tip T.

public:
    /** @brief Adauga un element nou in tracker. */
    void log(T value) { 
        history.push_back(value); 
    }

    /** @brief Returneaza numarul total de intrari inregistrate. */
    size_t getTotalEntries() const { 
        return history.size(); 
    }
};

#endif