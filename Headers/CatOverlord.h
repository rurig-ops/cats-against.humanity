#ifndef CATOVERLORD_H
#define CATOVERLORD_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Cat.h"
#include "Humanity.h"
#include "Actions.h"
#include "Exceptions.h"

/**
 * @class CatOverlord
 * @brief The player's persona, managing resources and cat agents.
 */
class CatOverlord {
private:
    std::vector<Cat> cats;
    int money;
    int chaosPoints;
    int actionPoints;
    std::vector<std::unique_ptr<CatAction>> actions;

public:
    explicit CatOverlord(int startMoney = 50, int startChaos = 10, int startAP = 6);

    // Deep copy support
    CatOverlord(const CatOverlord& other);
    CatOverlord& operator=(CatOverlord other);

    friend std::ostream& operator<<(std::ostream& os, const CatOverlord& o);

    // Management Methods
    void addCat(const Cat& c);
    void feedCat(int index, int amount);
    void encourageCat(int index, int amount);
    void trainCatEvil(int index, int amount);
    void sendCatToSpa(int index, int cost);

    // Interactive UI Methods
    void printStatus() const;
    void printCats() const;
    void feedCatInteractive();
    void encourageCatInteractive();
    void trainCatEvilInteractive();
    void sendOnMissionInteractive(Humanity& humans);
    void calmCatInteractive();

    // Turn Logic
    void nextDay();
    void sortCatsByEvilness();
    void performAction(int catIndex, int actionIndex, Humanity& humans);

    // Accessors
    size_t getNumActions() const { return actions.size(); }
    const std::vector<std::unique_ptr<CatAction>>& getActions() const { return actions; }
};

#endif