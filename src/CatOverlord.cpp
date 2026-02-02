#include "CatOverlord.h"
#include "Actions.h"
#include "Mission.h"
#include "GameSettings.h"
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

// Initializare statica obligatorie pentru Singleton
GameSettings* GameSettings::instance = nullptr;

CatOverlord::CatOverlord(int startMoney, int startChaos, int startAP)
    : money(startMoney), chaosPoints(startChaos), actionPoints(startAP) {
    actions.push_back(make_unique<StealFoodAction>());
    actions.push_back(make_unique<SpreadChaosAction>());
    actions.push_back(make_unique<RecruitCatsAction>(this));
    actions.push_back(make_unique<SendToSpaAction>());
    actions.push_back(make_unique<PerformDanceRitualAction>());
}

/**
 * Constructor de copiere corectat pentru Prototype Pattern.
 * Previne Stack Overflow prin re-ancorarea pointerului catre noul obiect 'this'.
 */
CatOverlord::CatOverlord(const CatOverlord& other)
    : cats(other.cats), money(other.money),
      chaosPoints(other.chaosPoints), actionPoints(other.actionPoints) {
    for (const auto& a : other.actions) {
        auto clona = a->clone();

        auto recruitPtr = dynamic_cast<RecruitCatsAction*>(clona.get());
        if (recruitPtr) {
            recruitPtr->setOverlord(this);
        }
        actions.push_back(std::move(clona));
    }
}

/**
 * Operatorul de atribuire folosind Copy-and-Swap.
 * Parametrul 'other' este primit prin valoare, declansand constructorul de copiere de mai sus.
 */
CatOverlord& CatOverlord::operator=(CatOverlord other) {
    swap(cats, other.cats);
    swap(actions, other.actions);
    swap(money, other.money);
    swap(chaosPoints, other.chaosPoints);
    swap(actionPoints, other.actionPoints);
    return *this;
}

void CatOverlord::addCat(const Cat& c) {
    cats.push_back(c);
}

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

void CatOverlord::trainCatEvil(int i, int cant) {
    if (actionPoints <= 0) throw NotEnoughAPException(1, actionPoints);
    if (i < 0 || i >= (int)cats.size()) throw InvalidCatIndexException(i);
    if (cant > money) throw NotEnoughMoneyException(cant, money);

    cats[i].trainEvil(cant);
    money -= cant;
    actionPoints--;
}

void CatOverlord::sendCatToSpa(int i, int cost) {
    if (actionPoints <= 0) throw NotEnoughAPException(1, actionPoints);
    if (i < 0 || i >= (int)cats.size()) throw InvalidCatIndexException(i);
    if (cost > money) throw NotEnoughMoneyException(cost, money);

    cats[i].decreaseEvilness(5);
    cats[i].increaseCuteness(15);
    money -= cost;
    actionPoints--;
    cout << cats[i].getName() << " is now relaxed. :3" << endl;
}

void CatOverlord::sortCatsByEvilness() {
    sort(cats.begin(), cats.end(), [](const Cat &a, const Cat &b){
        return a.getEvilness() > b.getEvilness();
    });
}

void CatOverlord::printStatus() const {
    cout << "Money: " << money << " | Chaos: " << chaosPoints << " | AP: " << actionPoints << endl;
    cout << "Difficulty: " << GameSettings::getInstance().getDifficulty() << endl;
}

void CatOverlord::printCats() const {
    for (size_t i = 0; i < cats.size(); ++i) cout << i << ": " << cats[i] << endl;
}

void CatOverlord::performAction(int catIndex, int actionIndex, Humanity& h) {
    if (catIndex < 0 || catIndex >= (int)cats.size()) throw InvalidCatIndexException(catIndex);
    if (actionIndex < 0 || actionIndex >= (int)actions.size()) return;

    actions[actionIndex]->perform(cats[catIndex], h);
}

void CatOverlord::nextDay() {
    actionPoints = 6;
    for (auto& c : cats) c.increaseHunger(5);
    cout << "--- A new day has dawned for the feline empire ---" << endl;
}

// METODE INTERACTIVE
void CatOverlord::feedCatInteractive() {
    int idx = -1, amt = 0;
    cout << "Cat index: ";
    if (!(cin >> idx)) return;
    cout << "Food amount ($): ";
    if (!(cin >> amt)) return;
    feedCat(idx, amt);
}

void CatOverlord::encourageCatInteractive() {
    int idx = -1, amt = 0;

    cout << "cat index: ";
    if (!(cin >> idx)) {
        if (cin.eof()) return;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    cout << "loyalty points: ";
    if (!(cin >> amt)) {
        if (cin.eof()) return;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    try {
        encourageCat(idx, amt);
    } catch (const GameException& e) {
        cout << "error: " << e.what() << endl;
    }
}

void CatOverlord::trainCatEvilInteractive() {
    int idx = -1, amt = 0;
    cout << "Cat index: ";
    if (!(cin >> idx)) return;
    cout << "Training cost ($): ";
    if (!(cin >> amt)) return;
    trainCatEvil(idx, amt);
}

void CatOverlord::calmCatInteractive() {
    int idx = -1;
    cout << "Cat to send to spa index: ";
    if (!(cin >> idx)) return;
    sendCatToSpa(idx, 15);
}

void CatOverlord::sendOnMissionInteractive(Humanity& h) {
    if (cats.empty()) {
        cout << "No cats available for missions!" << endl;
        return;
    }

    int index = -1;
    cout << "Select cat for mission (0-" << cats.size() - 1 << "): ";
    if (!(cin >> index)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (index < 0 || index >= (int)cats.size()) {
        cout << "Invalid cat index!" << endl;
        return;
    }

    vector<Mission> missions = {
        {"Steal Left Socks", 1, 10, 20, 10, 10, 5, 0, Mission::EVIL},
        {"Be Cute for TikTok", 1, 50, 0, 5, 0, 10, 30, Mission::PR}
    };

    cout << "\nAvailable Missions:" << endl;
    for(size_t i = 0; i < missions.size(); ++i) {
        cout << i << ". " << missions[i].getName() << endl;
    }

    int mIdx = -1;
    cout << "Mission index: ";
    if (!(cin >> mIdx)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }


    if (mIdx >= 0 && mIdx < (int)missions.size()) {
        if (missions[mIdx].attempt(cats[index])) {
            cout << "Mission successful!" << endl;
            money += missions[mIdx].getRewardMoney();
            chaosPoints += missions[mIdx].getRewardChaos();
            h.decreaseSuspicion(5);
        } else {
            cout << "Mission failed! Suspicion increased." << endl;
            h.increaseSuspicion(15);
        }

        cats[index].increaseHunger(missions[mIdx].getHungerCost());
        actionPoints--;
    } else {
        cout << "Invalid mission index!" << endl;
    }
}

ostream& operator<<(ostream& os, const CatOverlord& o) {
    os << "Overlord presiding over " << o.cats.size() << " operatives.";
    return os;
}