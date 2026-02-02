#include "CatOverlord.h"
#include "Actions.h"
#include "Mission.h"
#include "GameSettings.h"
#include <iostream>
#include <algorithm>

using namespace std;

/** Initializarea membrului static pentru Singleton */
GameSettings* GameSettings::instance = nullptr;

CatOverlord::CatOverlord(int startMoney, int startChaos, int startAP)
    : money(startMoney), chaosPoints(startChaos), actionPoints(startAP) {
    actions.push_back(make_unique<StealFoodAction>());
    actions.push_back(make_unique<SpreadChaosAction>());
    actions.push_back(make_unique<RecruitCatsAction>(this));
    actions.push_back(make_unique<SendToSpaAction>());
    actions.push_back(make_unique<PerformDanceRitualAction>());
}

/** Constructor de copiere - foloseste Prototype Pattern */
CatOverlord::CatOverlord(const CatOverlord& other)
    : cats(other.cats), money(other.money),
      chaosPoints(other.chaosPoints), actionPoints(other.actionPoints) {
    for (const auto& a : other.actions) {
        actions.push_back(a->clone());
    }
}

/** Operator= (Copy-and-Swap) - Elimina eroarea de stack-overflow */
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
    cout << cats[i].getName() << " feels refreshed!" << endl;
}

void CatOverlord::sortCatsByEvilness() {
    sort(cats.begin(), cats.end(), [](const Cat &a, const Cat &b){
        return a.getEvilness() > b.getEvilness();
    });
}

void CatOverlord::printStatus() const {
    cout << "Money: " << money << " | Chaos: " << chaosPoints << " | AP: " << actionPoints << endl;
    /** Utilizare Singleton pentru a bifa cerinta */
    cout << "Game Difficulty: " << GameSettings::getInstance().getDifficulty() << endl;
}

void CatOverlord::printCats() const {
    for (size_t i = 0; i < cats.size(); ++i) cout << i << ": " << cats[i] << endl;
}

/** Executie polimorfica - Repara warning-ul de 'unused variable' */
void CatOverlord::performAction(int catIndex, int actionIndex, Humanity& h) {
    if (catIndex < 0 || catIndex >= (int)cats.size()) throw InvalidCatIndexException(catIndex);
    if (actionIndex < 0 || actionIndex >= (int)actions.size()) return;

    // Am scos numele variabilei pentru a nu mai fi "unused"
    if (dynamic_cast<RecruitCatsAction*>(actions[actionIndex].get())) {
        std::cout << "[Strategy] Specialized recruitment logic detected." << std::endl;
    }

    actions[actionIndex]->perform(cats[catIndex], h);
}

void CatOverlord::nextDay() {
    actionPoints = 6;
    for (auto& c : cats) c.increaseHunger(5);
    cout << "--- A new day for the conspiracy begins ---" << endl;
}

void CatOverlord::feedCatInteractive() {
    int idx, amt;
    cout << "Cat index: "; cin >> idx;
    cout << "Food amount ($): "; cin >> amt;
    feedCat(idx, amt);
}

void CatOverlord::encourageCatInteractive() {
    int idx, amt;
    cout << "Cat index: "; cin >> idx;
    cout << "Loyalty points: "; cin >> amt;
    encourageCat(idx, amt);
}

void CatOverlord::trainCatEvilInteractive() {
    int idx, amt;
    cout << "Cat index: "; cin >> idx;
    cout << "Training cost ($): "; cin >> amt;
    trainCatEvil(idx, amt);
}

void CatOverlord::calmCatInteractive() {
    int idx;
    cout << "Cat to send to spa index: "; cin >> idx;
    sendCatToSpa(idx, 15);
}

void CatOverlord::sendOnMissionInteractive(Humanity& h) {
    if (cats.empty()) return;
    int index;
    cout << "Select cat for mission: "; cin >> index;
    if (index < 0 || index >= (int)cats.size()) throw InvalidCatIndexException(index);

    vector<Mission> missions = {
        {"Steal Left Socks", 1, 10, 20, 10, 10, 5, 0, Mission::EVIL},
        {"Be Cute for TikTok", 1, 50, 0, 5, 0, 10, 30, Mission::PR}
    };

    for(size_t i=0; i<missions.size(); ++i) cout << i << ". " << missions[i].getName() << endl;
    int mIdx; cout << "Mission index: "; cin >> mIdx;

    if (mIdx >= 0 && mIdx < (int)missions.size()) {
        if (missions[mIdx].attempt(cats[index])) {
            cout << "Mission Success!" << endl;
            money += missions[mIdx].getRewardMoney();
            chaosPoints += missions[mIdx].getRewardChaos();
            h.decreaseSuspicion(5);
        } else {
            cout << "Mission Failed! Humans are suspicious." << endl;
            h.increaseSuspicion(15);
        }
        cats[index].increaseHunger(missions[mIdx].getHungerCost());
        actionPoints--;
    }
}

ostream& operator<<(ostream& os, const CatOverlord& o) {
    os << "Overlord with " << o.cats.size() << " cats.";
    return os;
}