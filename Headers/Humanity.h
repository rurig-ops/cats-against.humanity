#ifndef HUMANITY_H
#define HUMANITY_H

#include <iostream>

/**
 * @class Humanity
 * @brief Tracks how close humans are to discovering the conspiracy.
 */
class Humanity {
private:
    int suspicion;
    int maxSuspicion;
public:
    explicit Humanity(int start = 0, int maxS = 100);

    /** @brief Increases suspicion level. Triggers game over if max reached. */
    void increaseSuspicion(int val);
    
    /** @brief Lowers suspicion level. */
    void decreaseSuspicion(int val);

    [[nodiscard]] bool isGameOver() const;

    friend std::ostream& operator<<(std::ostream& os, const Humanity& h);
};

#endif