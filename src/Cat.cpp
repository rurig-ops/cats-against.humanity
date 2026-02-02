#include "Cat.h"
#include <iostream>
#include <algorithm>

int Cat::totalCats = 0;

Cat::Cat(std::string n, int e, int c, int h, int l)
    : name(std::move(n)), evilness(e), cuteness(c), hunger(h), loyalty(l) { ++totalCats; }

Cat::Cat(std::string n)
    : name(std::move(n)), evilness(25), cuteness(25), hunger(50), loyalty(10) { ++totalCats; }

Cat::Cat(const Cat &other)
    : name(other.name), evilness(other.evilness), cuteness(other.cuteness),
      hunger(other.hunger), loyalty(other.loyalty) { ++totalCats; }

Cat::~Cat() { --totalCats; }

Cat& Cat::operator=(const Cat& other) {
    if (this != &other) {
        name = other.name;
        evilness = other.evilness;
        cuteness = other.cuteness;
        hunger = other.hunger;
        loyalty = other.loyalty;
    }
    return *this;
}

void Cat::feed(int amount) { hunger = std::max(0, hunger - amount); }
void Cat::trainEvil(int amount) { evilness = std::min(100, evilness + amount); }
void Cat::rewardLoyalty(int amount) { loyalty = std::min(100, loyalty + amount); }
void Cat::increaseHunger(int amount) { hunger = std::min(100, hunger + amount); }
void Cat::decreaseEvilness(int amount) { evilness = std::max(0, evilness - amount); }
void Cat::increaseCuteness(int amount) { cuteness = std::min(100, cuteness + amount); }

std::ostream& operator<<(std::ostream& os, const Cat& c) {
    os << c.name << " [Evil: " << c.evilness << " Luck: " << c.loyalty << "]";
    return os;
}