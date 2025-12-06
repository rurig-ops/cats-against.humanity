#ifndef CLASE_H
#define CLASE_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <exception>
#include <algorithm>

using namespace std;

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
    [[nodiscard]] const string& getName() const;
    [[nodiscard]] int getEvilness() const;
    [[nodiscard]] int getCuteness() const;
    [[nodiscard]] int getHunger() const;
    [[nodiscard]] int getLoyalty() const;
    void feed(int cant);
    void trainEvil(int cant);
    void rewardLoyalty(int cant);
    void increaseHunger(int cant);
    void decreaseEvilness(int amount);
    void pamper(int amount);
};

class Humanity {
private:
    int suspicion;
    int maxSuspicion;
public:
    explicit Humanity(int start = 0, int maxS = 100);
    void increaseSuspicion(int val);
    void decreaseSuspicion(int val);
    [[nodiscard]] bool isGameOver() const;
    friend ostream& operator<<(ostream& os, const Humanity& h);
};

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
    [[nodiscard]] const string& getName() const { return name; }
    [[nodiscard]] int getRewardMoney() const { return rewardMoney; }
    [[nodiscard]] int getRewardChaos() const { return rewardChaos; }
    [[nodiscard]] int getHungerCost() const { return hungerCost; }
    [[nodiscard]] int getDifficulty() const { return difficulty; }
    [[nodiscard]] MissionType getType() const { return type; }
    [[nodiscard]] bool attempt(const Cat& c) const;
    friend ostream& operator<<(ostream& os, const Mission& m);
};

class CatAction;
class CatOverlord {
private:
    vector<Cat> cats;
    int money;
    int chaosPoints;
    int actionPoints;
    vector<unique_ptr<CatAction>> actions;
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
    void calmCatInteractive();
    void sortCatsByEvilness();
    bool checkEvilnessGameOver();
    vector<Cat>& getCats() { return cats; }
    void performAction(int catIndex, int actionIndex, Humanity& humans);
    size_t getNumActions() { return actions.size(); }
    vector<unique_ptr<CatAction>>& getActions() { return actions; }
    void sendCatToSpaInteractive();
};

class CatAction {
public:
    virtual ~CatAction() = default;
    virtual void execute(Cat& c, Humanity& h) = 0;
    virtual string name() const = 0;
    virtual unique_ptr<CatAction> clone() const = 0;
    void perform(Cat& c, Humanity& h) { cout << c.getName() << " is performing action: " << name() << endl; execute(c, h); }
};

class StealFoodAction : public CatAction {
public:
    StealFoodAction();
    void execute(Cat& c, Humanity& h) override;
    string name() const override;
    unique_ptr<CatAction> clone() const override;
};

class SpreadChaosAction : public CatAction {
public:
    SpreadChaosAction();
    void execute(Cat& c, Humanity& h) override;
    string name() const override;
    unique_ptr<CatAction> clone() const override;
};

class RecruitCatsAction : public CatAction {
private:
    CatOverlord* overlord;
public:
    explicit RecruitCatsAction(CatOverlord* o);
    void execute(Cat& c, Humanity& h) override;
    string name() const override;
    unique_ptr<CatAction> clone() const override;
};

class GameException : public exception {
protected:
    string message;
public:
    explicit GameException(string msg) : message(std::move(msg)) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InvalidCatIndexException : public GameException {
public:
    explicit InvalidCatIndexException(int index) : GameException("Invalid cat index: " + to_string(index)) {}
};

class NotEnoughMoneyException : public GameException {
public:
    explicit NotEnoughMoneyException(int cost, int money) : GameException("Not enough money! Needed: " + to_string(cost) + ", Available: " + to_string(money)) {}
};

class NotEnoughAPException : public GameException {
public:
    explicit NotEnoughAPException(int needed, int available) : GameException("Not enough action points! Needed: " + to_string(needed) + ", Available: " + to_string(available)) {}
};

#endif
