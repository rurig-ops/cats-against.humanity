#include <iostream>
#include "clase.h"
using namespace std;

//                                    :3

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

//                                             :3

Humanity::Humanity(int start, int maxS) : suspicion(start), maxSuspicion(maxS) {}

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

bool Humanity::isGameOver() const { return suspicion >= maxSuspicion; }

ostream& operator<<(ostream& os, const Humanity& h) {
    os << "Human Suspicion: " << h.suspicion << "/" << h.maxSuspicion;
    return os;
}

//                                    :3

Mission::Mission(const string& n, int diff, int money, int chaos, int hunger,
                 int minE, int minL, int minC, MissionType t)
    : name(n), difficulty(diff), rewardMoney(money), rewardChaos(chaos),
      hungerCost(hunger), minEvilness(minE), minLoyalty(minL),
      minCuteness(minC), type(t) {}

bool Mission::attempt(const Cat& c) const {
    if (type == EVIL)
        return c.getEvilness() >= minEvilness && c.getLoyalty() >= minLoyalty;
    else
        return c.getLoyalty() >= minLoyalty && c.getCuteness() >= minCuteness;
}

ostream& operator<<(ostream& os, const Mission& m) {
    os << "Mission: " << m.name
       << " | Type: " << (m.type == Mission::EVIL ? "EVIL" : "PR")
       << " | Difficulty: " << m.difficulty
       << " | Reward: " << m.rewardMoney
       << " | Chaos: " << m.rewardChaos;
    return os;
}

//                                              :3

CatOverlord::CatOverlord(int startMoney, int startChaos, int startAP)
    : money(startMoney), chaosPoints(startChaos), actionPoints(startAP) {}

void CatOverlord::addCat(const Cat& c) { cats.push_back(c); }

void CatOverlord::feedCat(int i, int cant) {
    if (actionPoints <= 0) throw NotEnoughAPException(1, actionPoints);
    if (i < 0 || i >= (int)cats.size()) throw InvalidCatIndexException(i);
    if (cant > money) throw NotEnoughMoneyException(cant, money);
    cats[i].feed(cant);
    money -= cant;
    actionPoints--;
}

void CatOverlord::encourageCat(int i, int cant) {
    if (actionPoints <= 0) throw NotEnoughAPException(1, actionPoints);
    if (i < 0 || i >= (int)cats.size()) throw InvalidCatIndexException(i);
    cats[i].rewardLoyalty(cant);
    actionPoints--;
}

bool CatOverlord::sendOnMission(int i, const Mission& m, Humanity& humans) {
    if (actionPoints < 2) {
        cout << "Not enough action points to send a cat on a mission!" << endl;
        return false;
    }
    if (i < 0 || i >= (int)cats.size()) throw InvalidCatIndexException(i);

    bool success = m.attempt(cats[i]);
    cout << cats[i].getName() << " was sent on mission: " << m.getName() << "..." << endl;

    actionPoints -= 2;
    cats[i].increaseHunger(m.getHungerCost());

    if (m.getType() == Mission::EVIL) {
        if (success) {
            money += m.getRewardMoney();
            chaosPoints += m.getRewardChaos();
            cout << "Mission SUCCESS! " << cats[i].getName() << " completed " << m.getName() << endl;
        } else {
            humans.increaseSuspicion(m.getDifficulty());
            cout << "Mission FAILED! " << cats[i].getName() << " could not complete " << m.getName() << endl;
        }
    } else {
        if (success) {
            humans.decreaseSuspicion(m.getDifficulty());
            cout << "PR Mission SUCCESS! " << cats[i].getName() << " lowered suspicion with " << m.getName() << endl;
        } else {
            humans.increaseSuspicion(m.getDifficulty() * 2);
            cout << "PR Mission FAILED! " << cats[i].getName() << "'s attempt at " << m.getName() << " backfired!" << endl;
        }
    }

    if (humans.isGameOver()) {
        cout << "Game Over! Humans discovered the cat conspiracy!" << endl;
        return true;
    }
    if (chaosPoints >= 100) {
        cout << "You won! Chaos has reached maximum! Congratulations!" << endl;
        return true;
    }

    return false;
}

void CatOverlord::nextDay() {
    actionPoints = 6;
    for (auto& c : cats) c.increaseHunger(15);
}

void CatOverlord::trainCatEvil(int i, int cant) {
    if (actionPoints <= 0) throw NotEnoughAPException(1, actionPoints);
    if (i < 0 || i >= (int)cats.size()) throw InvalidCatIndexException(i);
    if (cant > money) throw NotEnoughMoneyException(cant, money);
    cats[i].trainEvil(cant);
    money -= cant;
    actionPoints--;
}

void CatOverlord::printStatus() const {
    cout << "Money: " << money << " | Chaos: " << chaosPoints << " | AP: " << actionPoints << "\n";
}

void CatOverlord::printCats() const {
    for (size_t i = 0; i < cats.size(); i++) {
        const Cat& c = cats[i];
        cout << "[" << i << "] " << c.getName() << " | Evil: " << c.getEvilness()
             << " | Cute: " << c.getCuteness() << " | Hunger: " << c.getHunger()
             << " | Loyalty: " << c.getLoyalty() << "\n";
    }
}

void CatOverlord::sortCatsByEvilness() {
    int n = cats.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (cats[j].getEvilness() > cats[j + 1].getEvilness()) {
                swap(cats[j], cats[j + 1]);
            }
        }
    }
}

// Interactive methods for CatOverlord
void CatOverlord::feedCatInteractive() {
    try {
        int index, amount;
        cout << "Select cat index to feed: ";
        cin >> index;
        cout << "Amount to feed: ";
        cin >> amount;
        feedCat(index, amount);
    } catch (const GameException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void CatOverlord::encourageCatInteractive() {
    try {
        int index, amount;
        cout << "Select cat index to encourage: ";
        cin >> index;
        cout << "Amount to increase loyalty: ";
        cin >> amount;
        encourageCat(index, amount);
    } catch (const GameException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void CatOverlord::trainCatEvilInteractive() {
    try {
        int index, amount;
        cout << "Select cat index to train evilness: ";
        cin >> index;
        cout << "Amount to train evilness: ";
        cin >> amount;
        trainCatEvil(index, amount);
    } catch (const GameException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void CatOverlord::sendOnMissionInteractive(Humanity& humans) {
    try {
        int index, missionChoice;
        cout << "Select cat index to send on mission: ";
        cin >> index;
        cout << "Select mission:\n1. Steal Socks\n2. Infiltrate the government\n3. Funny Compilation\n> ";
        cin >> missionChoice;

        Mission stealSock("Steal Socks",15,5,30,25,35,10,0,Mission::EVIL);
        Mission government("Infiltrate the government",45,40,5,5,66,50,0,Mission::EVIL);
        Mission funnyCompilation("Funny Cat Compilation",5,0,0,5,0,0,20,Mission::PR);

        bool gameOver = false;
        switch(missionChoice) {
            case 1: gameOver = sendOnMission(index, stealSock, humans); break;
            case 2: gameOver = sendOnMission(index, government, humans); break;
            case 3: gameOver = sendOnMission(index, funnyCompilation, humans); break;
            default: cout << "Invalid mission choice!\n"; return;
        }

        if(gameOver) cout << "Mission ended the game!\n";
    } catch (const GameException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void CatOverlord::calmCatInteractive() {
    try {
        int index, amount;
        cout << "Select cat index to calm: ";
        cin >> index;
        cout << "Amount to reduce evilness: ";
        cin >> amount;
        if(index < 0 || index >= (int)cats.size()) throw InvalidCatIndexException(index);
        if(amount < 0) amount = 0;
        cats[index].decreaseEvilness(amount);
        cout << cats[index].getName() << " has calmed down. Evilness: " << cats[index].getEvilness() << "\n";
        if(actionPoints <= 0) throw NotEnoughAPException(1, actionPoints);
        actionPoints--;
    } catch(const GameException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

bool CatOverlord::checkEvilnessGameOver() {
    for(const auto& c : cats)
        if(c.getEvilness() >= 100) {
            cout << c.getName() << " has become too evil! Game Over!\n";
            return true;
        }
    return false;
}

//                                         :3

// StealFoodAction
void StealFoodAction::execute(Cat& c, Humanity& h) {
    cout << c.getName() << " is stealing food symbolically.\n";
    c.trainEvil(3);
    h.increaseSuspicion(5);
}

string StealFoodAction::name() const { return "Steal Food"; }

unique_ptr<CatAction> StealFoodAction::clone() const {
    return make_unique<StealFoodAction>(*this);
}

// SpreadChaosAction
void SpreadChaosAction::execute(Cat& c, Humanity& h) {
    cout << c.getName() << " is spreading chaos!\n";
    c.trainEvil(5);
    h.increaseSuspicion(10);
}

string SpreadChaosAction::name() const { return "Spread Chaos"; }

unique_ptr<CatAction> SpreadChaosAction::clone() const {
    return make_unique<SpreadChaosAction>(*this);
}

// RecruitCatsAction
RecruitCatsAction::RecruitCatsAction(CatOverlord* o) : overlord(o) {}

void RecruitCatsAction::execute(Cat& c, Humanity& h) {
    if (!overlord) return;
    (void)h;
    static int id = 1;
    Cat newCat("NewCat#" + to_string(id++));
    overlord->addCat(newCat);
    cout << c.getName() << " recruited a new cat: " << newCat.getName() << "\n";
}

string RecruitCatsAction::name() const { return "Recruit Cats"; }

unique_ptr<CatAction> RecruitCatsAction::clone() const {
    return make_unique<RecruitCatsAction>(*this);
}
