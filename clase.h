#ifndef CLASE_H
#define CLASE_H

#include <iostream>
#include <vector>
using namespace std;

//                                        :3

class Cat {
private:
    string name;
    int evilness;
    int cuteness;
    int hunger;
    int loyalty;

public:
    Cat(string n, int e, int c, int h, int l);
    explicit Cat(string n);
    Cat(const Cat &other);
    ~Cat();
    Cat& operator=(const Cat& other);
    friend ostream& operator<<(ostream& os, const Cat& c);

    [[nodiscard]]const string& getName() const;
    [[nodiscard]]int getEvilness() const;
    [[nodiscard]]int getCuteness() const;
    [[nodiscard]]int getHunger() const;
    [[nodiscard]]int getLoyalty() const;

    void feed(int cant);
    void trainEvil(int cant);
    void rewardLoyalty(int cant);
    void increaseHunger(int cant);

    void decreaseEvilness(int amount);
};

//                                           :3

class Humanity {
private:
    int suspicion;
    int maxSuspicion;

public:
    explicit Humanity(int start = 0, int maxS = 100);

    void increaseSuspicion(int val);
    void decreaseSuspicion(int val);

    [[nodiscard]]bool isGameOver() const;

    friend ostream& operator<<(ostream& os, const Humanity& h);
};

//                                         :3

class Mission {
public:
    enum MissionType { EVIL, PR };

private:
    string name;
    int difficulty;
    int rewardMoney;
    int rewardChaos;
    int hungerCost;
    int minEvilness;
    int minLoyalty;
    int minCuteness;
    MissionType type;

public:
    Mission(const string& n, int diff, int money, int chaos, int hunger, int minE, int minL, int minC, MissionType t);
    [[nodiscard]]const string& getName() const { return name; }
    [[nodiscard]]int getRewardMoney() const { return rewardMoney; }
    [[nodiscard]]int getRewardChaos() const { return rewardChaos; }
    [[nodiscard]]int getHungerCost() const { return hungerCost; }
    [[nodiscard]]int getDifficulty() const { return difficulty; }
    [[nodiscard]]MissionType getType() const { return type; }

    [[nodiscard]]bool attempt(const Cat& c) const;

    friend ostream& operator<<(ostream& os, const Mission& m);
};

//                                          :3

class CatOverlord {
private:
    vector<Cat> cats;
    int money;
    int chaosPoints;
    int actionPoints;

public:
    explicit CatOverlord(int startMoney = 50, int startChaos = 10, int startAP = 6);
    friend ostream& operator<<(ostream& os, const CatOverlord& o);

    void addCat(const Cat& c);
    void feedCat(int index, int cant);
    void encourageCat(int index, int cant);
    void nextDay();
    bool sendOnMission(int index, const Mission& m, Humanity& humans);
    void trainCatEvil(int index, int cant);

    void printStatus() const;
    void printCats() const;

    void feedCatInteractive();
    void encourageCatInteractive();
    void trainCatEvilInteractive();
    void sendOnMissionInteractive(Humanity& humans);

    void sortCatsByEvilness();

    bool checkEvilnessGameOver();

    void calmCatInteractive();
};

#endif