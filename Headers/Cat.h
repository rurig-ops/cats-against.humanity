#ifndef CAT_H
#define CAT_H

#include <string>
#include <iostream>

/**
 * @class Cat
 * @brief Represents a feline agent.
 */
class Cat {
private:
    std::string name;
    int evilness, cuteness, hunger, loyalty;
    static int totalCats;

public:
    Cat(std::string n, int e, int c, int h, int l);
    explicit Cat(std::string n);
    
    // Rule of Three
    Cat(const Cat &other);
    Cat& operator=(const Cat& other);
    ~Cat();

    friend std::ostream& operator<<(std::ostream& os, const Cat& c);

    // Getters
    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] int getEvilness() const { return evilness; }
    [[nodiscard]] int getCuteness() const { return cuteness; }
    [[nodiscard]] int getHunger() const { return hunger; }
    [[nodiscard]] int getLoyalty() const { return loyalty; }
    static int getTotalCats() { return totalCats; }

    // Logic
    void feed(int amount);
    void trainEvil(int amount);
    void rewardLoyalty(int amount);
    void increaseHunger(int amount);
    void decreaseEvilness(int amount);
    void increaseCuteness(int amount);
};

#endif