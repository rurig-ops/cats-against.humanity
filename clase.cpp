#include "clase.h"
#include <iostream>
#include <algorithm>

using namespace std;

// :3 Cat

Cat::Cat(string n, int e, int c, int h, int l)
    : name(n), evilness(e), cuteness(c), hunger(h), loyalty(l) {}

Cat::Cat(string n)
    : name(n), evilness(25), cuteness(25), hunger(50), loyalty(10) {}

Cat::Cat(const Cat &other)
    : name(other.name), evilness(other.evilness), cuteness(other.cuteness),
      hunger(other.hunger), loyalty(other.loyalty) {}

Cat::~Cat() {}

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

ostream& operator<<(ostream& os, const Cat& c) {
    os << c.getName() << " | Evil: " << c.getEvilness()
       << " | Cute: " << c.getCuteness()
       << " | Hunger: " << c.getHunger()
       << " | Loyalty: " << c.getLoyalty();
    return os;
}

const string& Cat::getName() const { return name; }
int Cat::getEvilness() const { return evilness; }
int Cat::getCuteness() const { return cuteness; }
int Cat::getHunger() const { return hunger; }
int Cat::getLoyalty() const { return loyalty; }

void Cat::feed(int cant) {
    hunger -= cant;
    if (hunger < 0) hunger = 0;
    cout << name << " was fed. Hunger: " << hunger << endl;
}

void Cat::trainEvil(int cant) {
    evilness += cant;
    if (evilness > 100) evilness = 100;
    cout << name << " trained fiendishly. Evilness: " << evilness << endl;
}

void Cat::rewardLoyalty(int cant) {
    loyalty += cant;
    if (loyalty > 100) loyalty = 100;
    cout << name << " is more loyal now! Loyalty: " << loyalty << endl;
}

void Cat::increaseHunger(int cant) {
    hunger += cant;
    if (hunger > 100) hunger = 100;
}

void Cat::decreaseEvilness(int amount) {
    evilness -= amount;
    if (evilness < 0) evilness = 0;
}

void Cat::pamper(int amount) {
    cuteness += amount;
    if (cuteness > 100) cuteness = 100;
    cout << name << " went to the spa! Cuteness: " << cuteness << endl;
}

// :3 Humanity

Humanity::Humanity(int start, int maxS)
    : suspicion(start), maxSuspicion(maxS) {}

void Humanity::increaseSuspicion(int val) {
    suspicion += val;
    if (suspicion > maxSuspicion) suspicion = maxSuspicion;
    cout << "Human suspicion increased: " << suspicion << "/" << maxSuspicion << endl;
    if (isGameOver())
        cout << "Humans discovered the cat conspiracy! Game Over!" << endl;
}

void Humanity::decreaseSuspicion(int val) {
    suspicion -= val;
    if (suspicion < 0) suspicion = 0;
    cout << "Suspicion lowered: " << suspicion << "/" << maxSuspicion << endl;
}

bool Humanity::isGameOver() const {
    return suspicion >= maxSuspicion;
}

ostream& operator<<(ostream& os, const Humanity& h) {
    os << "Human Suspicion: " << h.suspicion << "/" << h.maxSuspicion;
    return os;
}

// :3 Mission

Mission::Mission(const string& n, int diff, int money, int chaos, int hunger, int minE, int minL, int minC, MissionType t)
    : name(n), difficulty(diff), rewardMoney(money), rewardChaos(chaos), hungerCost(hunger),
      minEvilness(minE), minLoyalty(minL), minCuteness(minC), type(t) {}

bool Mission::attempt(const Cat& c) const {
    if (type == EVIL)
        return c.getEvilness() >= minEvilness && c.getLoyalty() >= minLoyalty;
    else
        return c.getLoyalty() >= minLoyalty && c.getCuteness() >= minCuteness;
}

ostream& operator<<(ostream& os, const Mission& m) {
    os << "Mission: " << m.name << " | Type: " << (m.type == Mission::EVIL ? "EVIL" : "PR")
       << " | Difficulty: " << m.difficulty
       << " | Reward: " << m.rewardMoney
       << " | Chaos: " << m.rewardChaos;
    return os;
}

// :3 CatOverlord

CatOverlord::CatOverlord(int startMoney, int startChaos, int startAP)
    : money(startMoney), chaosPoints(startChaos), actionPoints(startAP)
{
    actions.push_back(make_unique<StealFoodAction>());
    actions.push_back(make_unique<SpreadChaosAction>());
    actions.push_back(make_unique<RecruitCatsAction>(this));
}

void CatOverlord::addCat(const Cat& c) {
    cats.push_back(c);
}

void CatOverlord::feedCat(int i, int cant) {
    if (actionPoints <= 0)
        throw NotEnoughAPException(1, actionPoints);
    if (i < 0 || i >= (int)cats.size())
        throw InvalidCatIndexException(i);
    if (cant > money)
        throw NotEnoughMoneyException(cant, money);

    cats[i].feed(cant);
    money -= cant;
    actionPoints--;
}

void CatOverlord::encourageCat(int i, int cant) {
    if (actionPoints <= 0)
        throw NotEnoughAPException(1, actionPoints);
    if (i < 0 || i >= (int)cats.size())
        throw InvalidCatIndexException(i);

    cats[i].rewardLoyalty(cant);
    actionPoints--;
}

void CatOverlord::trainCatEvil(int i, int cant) {
    if (actionPoints <= 0)
        throw NotEnoughAPException(1, actionPoints);
    if (i < 0 || i >= (int)cats.size())
        throw InvalidCatIndexException(i);
    if (cant > money)
        throw NotEnoughMoneyException(cant, money);

    cats[i].trainEvil(cant);
    money -= cant;
    actionPoints--;
}

// interactive methods
void CatOverlord::feedCatInteractive() {
    int index, cant;
    cout << "Which cat to feed? ";
    cin >> index;
    cout << "How much? ";
    cin >> cant;
    feedCat(index, cant);
}

void CatOverlord::encourageCatInteractive() {
    int index, cant;
    cout << "Which cat to encourage? ";
    cin >> index;
    cout << "How much? ";
    cin >> cant;
    encourageCat(index, cant);
}

void CatOverlord::trainCatEvilInteractive() {
    int index, cant;
    cout << "Which cat to train evilly? ";
    cin >> index;
    cout << "How much? ";
    cin >> cant;
    trainCatEvil(index, cant);
}

// :3 CatOverlord::sendOnMissionInteractive
void CatOverlord::sendOnMissionInteractive(Humanity& humans) {
    if (actionPoints <= 0)
        throw NotEnoughAPException(1, actionPoints);

    if (cats.empty()) {
        cout << "No cats available for missions!" << endl;
        return;
    }

    // afișăm pisicile
    cout << "Select a cat for the mission:" << endl;
    for (size_t i = 0; i < cats.size(); ++i)
        cout << i << ": " << cats[i] << endl;

    int catIndex;
    cin >> catIndex;
    if (catIndex < 0 || catIndex >= (int)cats.size())
        throw InvalidCatIndexException(catIndex);

    Cat& c = cats[catIndex];

    // definim misiunile PR
    struct PRMission {
        string name;
        int requiredCuteness;
        int suspicionDecrease;
        int failSuspicionIncrease;
        int rewardMoney;
        string successMsg;
        string failMsg;
    };
    vector<PRMission> prMissions = {
        {"Make a brainrot TikTok", 15, 25, 22, 30,
         "Success! The kids loved this one. It's becoming the new Italian brainrot",
         "Phew that video sucked. Never attempt editing again"},
        {"Make AI Facebook post", 0, 35, 44, 50,
         "Success! The post reached old people's feeds",
         "Even the grandparents figured out it's AI and they're suing you now"}
    };

    // definim misiunile EVIL
    struct EvilMission {
        string name;
        int requiredEvilness;
        int chaosIncrease;
        int failSuspicionIncrease;
        string successMsg;
        string failMsg;
    };
    vector<EvilMission> evilMissions = {
        {"Steal everyone's left sock", 0, 25, 33,
         "The sock collection is growing",
         "You have disappointed the sock lovers in the cat society"},
        {"Steal the laser from Magurele", 80, 50, 67,
         "The cats will enjoy this laser",
         "Cojocariu will remember this"}
    };

    cout << "Choose mission type:\n1. PR Mission\n2. Evil Mission\n";
    int typeChoice;
    cin >> typeChoice;

    actionPoints-=2;
    c.increaseHunger(10);

    if (typeChoice == 1) {
        cout << "Select PR mission:\n";
        for (size_t i = 0; i < prMissions.size(); ++i)
            cout << i << ". " << prMissions[i].name << endl;
        int mIndex;
        cin >> mIndex;
        if (mIndex < 0 || mIndex >= (int)prMissions.size()) {
            cout << "Invalid mission index" << endl;
            actionPoints++; // restituim AP
            return;
        }
        PRMission& m = prMissions[mIndex];
        if (c.getCuteness() >= m.requiredCuteness) {
            humans.decreaseSuspicion(m.suspicionDecrease);
            money += m.rewardMoney;       // primim bani
            cout << m.successMsg << " You earned $" << m.rewardMoney << "!" << endl;
        } else {
            humans.increaseSuspicion(m.failSuspicionIncrease);
            cout << m.failMsg << endl;
        }
    } else if (typeChoice == 2) {
        cout << "Select Evil mission:\n";
        for (size_t i = 0; i < evilMissions.size(); ++i)
            cout << i << ". " << evilMissions[i].name << endl;
        int mIndex;
        cin >> mIndex;
        if (mIndex < 0 || mIndex >= (int)evilMissions.size()) {
            cout << "Invalid mission index" << endl;
            actionPoints++; // restituim AP
            return;
        }
        EvilMission& m = evilMissions[mIndex];
        if (c.getEvilness() >= m.requiredEvilness) {
            chaosPoints += m.chaosIncrease;
            cout << m.successMsg << endl;
        } else {
            humans.increaseSuspicion(m.failSuspicionIncrease);
            cout << m.failMsg << endl;
        }
    } else {
        cout << "Invalid mission type" << endl;
        actionPoints++; // dacă alegerea invalidă, restituim AP
    }
}

void CatOverlord::sendCatToSpaInteractive() {
    int index, amount;
    cout << "Which cat to send to the spa? ";
    cin >> index;
    cout << "How much pampering? ";
    cin >> amount;

    if (actionPoints <= 0)
        throw NotEnoughAPException(1, actionPoints);
    if (index < 0 || index >= (int)cats.size())
        throw InvalidCatIndexException(index);

    cats[index].pamper(amount);
    actionPoints--;
}


void CatOverlord::performAction(int catIndex, int actionIndex, Humanity& h) {
    if (catIndex < 0 || catIndex >= (int)cats.size())
        throw InvalidCatIndexException(catIndex);
    if (actionIndex < 0 || actionIndex >= (int)actions.size()) {
        cout << "Invalid action index\n";
        return;
    }

    cout << "Cat " << cats[catIndex].getName()
         << " is performing action: " << actions[actionIndex]->name() << "\n";

    actions[actionIndex]->perform(cats[catIndex], h);
}

void CatOverlord::nextDay() {
    actionPoints = 3;
    for (auto &c : cats)
        c.increaseHunger(5);
}

void CatOverlord::printStatus() const {
    cout << "Money: " << money
         << " | Chaos: " << chaosPoints
         << " | AP: " << actionPoints << endl;
}

void CatOverlord::printCats() const {
    for (size_t i = 0; i < cats.size(); ++i)
        cout << i << ": " << cats[i] << endl;
}

void CatOverlord::sortCatsByEvilness() {
    sort(cats.begin(), cats.end(), [](const Cat &a, const Cat &b) {
        return a.getEvilness() > b.getEvilness();
    });
}

// :3 StealFoodAction

StealFoodAction::StealFoodAction() = default;

void StealFoodAction::execute(Cat& c, Humanity& h) {
    cout << c.getName() << " is stealing food symbolically.\n";
    c.trainEvil(3);
    h.increaseSuspicion(5);
}

string StealFoodAction::name() const { return "Steal Food"; }
unique_ptr<CatAction> StealFoodAction::clone() const { return make_unique<StealFoodAction>(*this); }

// :3 SpreadChaosAction

SpreadChaosAction::SpreadChaosAction() = default;

void SpreadChaosAction::execute(Cat& c, Humanity& h) {
    cout << c.getName() << " is spreading chaos!\n";
    c.trainEvil(5);
    h.increaseSuspicion(10);
}

string SpreadChaosAction::name() const { return "Spread Chaos"; }
unique_ptr<CatAction> SpreadChaosAction::clone() const { return make_unique<SpreadChaosAction>(*this); }

// :3 RecruitCatsAction

RecruitCatsAction::RecruitCatsAction(CatOverlord* o) : overlord(o) {}

void RecruitCatsAction::execute(Cat& c, Humanity& h) {
    (void)h;
    if (!overlord) return;
    static int id = 1;
    Cat newCat("NewCat#" + to_string(id++));
    overlord->addCat(newCat);
    cout << c.getName() << " recruited a new cat: " << newCat.getName() << "\n";
}

string RecruitCatsAction::name() const { return "Recruit Cats"; }
unique_ptr<CatAction> RecruitCatsAction::clone() const { return make_unique<RecruitCatsAction>(*this); }
