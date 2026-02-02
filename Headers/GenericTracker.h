#ifndef GENERICTRACKER_H
#define GENERICTRACKER_H

#include <vector>

template <typename T>
class GenericTracker {
private:
    std::vector<T> history;

public:
    void log(const T& value) {
        history.push_back(value);
    }

    /** @brief Atributul previne eroarea unusedFunction pe GitHub */
    [[maybe_unused]] size_t getTotalEntries() const {
        return history.size(); 
    }
};

#endif