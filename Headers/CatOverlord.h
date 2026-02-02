#ifndef CATOVERLORD_H
#define CATOVERLORD_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include "Cat.h"
#include "Humanity.h"
#include "Actions.h"
#include "Exceptions.h"

class CatOverlord {
private:
    std::vector<Cat> cats;
    int money;
    int chaosPoints;
    int actionPoints;
    /** @brief Colectie de actiuni polimorfice gestionate prin Smart Pointers */
    std::vector<std::unique_ptr<CatAction>> actions;

public:
    explicit CatOverlord(int startMoney = 50, int startChaos = 10, int startAP = 6);

    /** @brief Copy Constructor - foloseste Prototype Pattern (clone) pentru deep copy la actions */
    CatOverlord(const CatOverlord& other);

    /** @brief Operator= (Copy-and-Swap) - Varianta safe care elimina riscul de stack-overflow */
    CatOverlord& operator=(CatOverlord other);

    ~CatOverlord() = default;

    friend std::ostream& operator<<(std::ostream& os, const CatOverlord& o);

    void addCat(const Cat& c);
    void feedCat(int index, int amount);
    void trainCatEvil(int index, int amount);
    void sendCatToSpa(int index, int cost);

    void printStatus() const;
    void printCats() const;
    void feedCatInteractive();
    void trainCatEvilInteractive();
    void sendOnMissionInteractive(Humanity& humans);
    void calmCatInteractive();

    void nextDay();
    void sortCatsByEvilness();

    /** @brief Executa o actiune speciala utilizand Late Binding/Polimorfism */
    void performAction(int catIndex, int actionIndex, Humanity& humans);

    [[maybe_unused]] size_t getNumActions() const { return actions.size(); }
    [[maybe_unused]] const std::vector<std::unique_ptr<CatAction>>& getActions() const { return actions; }

    void encourageCat(int i, int cant);
    void encourageCatInteractive();
};

#endif