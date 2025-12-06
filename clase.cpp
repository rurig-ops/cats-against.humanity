#include "clase.h"
#include <iostream>
#include <algorithm>

using namespace std;

// :3 Cat
Cat::Cat(string n, int e, int c, int h, int l) : name(n), evilness(e), cuteness(c), hunger(h), loyalty(l) {}
Cat::Cat(string n) : name(n), evilness(25), cuteness(25), hunger(50), loyalty(10) {}
Cat::Cat(const Cat &other) : name(other.name), evilness(other.evilness), cuteness(other.cuteness), hunger(other.hunger), loyalty(other.loyalty) {}
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

void Cat::increaseCuteness(int amount) {
    cuteness += amount;
    if (cuteness > 100) cuteness = 100;
}

// :3 Humanity
Humanity::Humanity(int start, int maxS) : suspicion(start), maxSuspicion(maxS) {}

void Humanity::increaseSuspicion(int val) {
    suspicion += val;
    if (suspicion > maxSuspicion) suspicion = maxSuspicion;
    cout << "Human suspicion increased: " << suspicion << "/" << maxSuspicion << endl;
    if (isGameOver()) cout << "Humans discovered the cat conspiracy! Game Over!" << endl;
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
    : money(startMoney), chaosPoints(startChaos), actionPoints(startAP) {
    actions.push_back(make_unique<StealFoodAction>());
    actions.push_back(make_unique<SpreadChaosAction>());
    actions.push_back(make_unique<RecruitCatsAction>(this));
    actions.push_back(make_unique<SendToSpaAction>());
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
    cout << cats[i].getName() << " enjoyed the spa! Evilness down, cuteness up." << endl;

    money -= cost;
    actionPoints--;
}

// interactive
void CatOverlord::feedCatInteractive() {
    int index, cant;
    cout << "Which cat to feed? "; cin >> index;
    cout << "How much? "; cin >> cant;
    feedCat(index, cant);
}

void CatOverlord::encourageCatInteractive() {
    int index, cant;
    cout << "Which cat to encourage? "; cin >> index;
    cout << "How much? "; cin >> cant;
    encourageCat(index, cant);
}

void CatOverlord::trainCatEvilInteractive() {
    int index, cant;
    cout << "Which cat to train evilly? "; cin >> index;
    cout << "How much? "; cin >> cant;
    trainCatEvil(index, cant);
}

void CatOverlord::sendOnMissionInteractive(Humanity& h) {
    if (cats.empty()) return;
    int index;
    cout << "Select cat for mission: ";
    cin >> index;
    if (index < 0 || index >= (int)cats.size()) throw InvalidCatIndexException(index);

    // Exemple misiuni
    vector<Mission> prMissions = {
        {"Make a brainrot TikTok", 1, 25, 0, 10, 0, 0, 15, Mission::PR},
        {"Make AI Facebook post", 2, 50, 0, 10, 0, 0, 25, Mission::PR}
    };
    vector<Mission> evilMissions = {
        {"Steal everyone's left sock", 1, 0, 25, 10, 0, 0, 0, Mission::EVIL},
        {"Steal the laser from Magurele", 2, 0, 50, 10, 80, 0, 0, Mission::EVIL}
    };

    int missionType;
    cout << "Select mission type (0=PR, 1=EVIL): ";
    cin >> missionType;
    int missionIndex;

    const Mission* selectedMission = nullptr;

    if (missionType == 0) {
        for (size_t i = 0; i < prMissions.size(); ++i)
            cout << i << ": " << prMissions[i].getName() << endl;
        cout << "Select mission index: ";
        cin >> missionIndex;
        if (missionIndex < 0 || missionIndex >= (int)prMissions.size()) return;
        selectedMission = &prMissions[missionIndex];
    } else {
        for (size_t i = 0; i < evilMissions.size(); ++i)
            cout << i << ": " << evilMissions[i].getName() << endl;
        cout << "Select mission index: ";
        cin >> missionIndex;
        if (missionIndex < 0 || missionIndex >= (int)evilMissions.size()) return;
        selectedMission = &evilMissions[missionIndex];
    }

    if (!selectedMission) return;

    Cat& c = cats[index];

    if (selectedMission->attempt(c)) {
        cout << "Success! ";
        if (selectedMission->getType() == Mission::PR) {
            if (missionIndex == 0) cout << "The kids loved this one. It's becoming the new Italian brainrot.\n";
            else cout << "The post reached old people's feeds!\n";
            h.decreaseSuspicion( missionIndex == 0 ? 25 : 35 );
            money += selectedMission->getRewardMoney();
        } else {
            if (missionIndex == 0) cout << "The sock collection is growing.\n";
            else cout << "The cats will enjoy this laser.\n";
            chaosPoints += selectedMission->getRewardChaos();
        }
    } else {
        cout << "Fail! ";
        if (selectedMission->getType() == Mission::PR) {
            if (missionIndex == 0) cout << "Phew, that video sucked. Never attempt editing again.\n";
            else cout << "Even the grandparents figured out it's AI and they are suing you now.\n";
            h.increaseSuspicion( missionIndex == 0 ? 22 : 44 );
        } else {
            if (missionIndex == 0) cout << "You have disappointed the sock lovers in the cat society.\n";
            else cout << "Cojocariu will remember this.\n";
            h.increaseSuspicion( missionIndex == 0 ? 33 : 67 );
        }
    }

    c.increaseHunger(selectedMission->getHungerCost());
    actionPoints--;
}

void CatOverlord::calmCatInteractive() {
    int index;
    cout << "Which cat to calm at spa? "; cin >> index;
    sendCatToSpa(index, 15);
}

void CatOverlord::nextDay() {
    actionPoints = 3;
    for (auto& c : cats) c.increaseHunger(5);
}

void CatOverlord::printStatus() const {
    cout << "Money: " << money << " | Chaos: " << chaosPoints << " | AP: " << actionPoints << endl;
}

void CatOverlord::printCats() const {
    for (size_t i = 0; i < cats.size(); ++i) cout << i << ": " << cats[i] << endl;
}

void CatOverlord::sortCatsByEvilness() {
    sort(cats.begin(), cats.end(), [](const Cat &a, const Cat &b){ return a.getEvilness() > b.getEvilness(); });
}

void CatOverlord::performAction(int catIndex, int actionIndex, Humanity& h) {
    if (catIndex < 0 || catIndex >= (int)cats.size()) throw InvalidCatIndexException(catIndex);
    if (actionIndex < 0 || actionIndex >= (int)actions.size()) return;

    CatAction* a = actions[actionIndex].get();

    // DOWNCAST demonstrativ
    if (auto recruit = dynamic_cast<RecruitCatsAction*>(a)) {
        (void)recruit;
        cout << "Detected RecruitCatsAction! This action can recruit new cats.\n";
    }

    a->perform(cats[catIndex], h);
}

// :3 StealFoodAction
StealFoodAction::StealFoodAction() = default;
void StealFoodAction::execute(Cat& c, Humanity& h) {
    cout << c.getName() << " is stealing food.\n";
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

// :3 SendToSpaAction
SendToSpaAction::SendToSpaAction() = default;
void SendToSpaAction::execute(Cat& c, Humanity&) {
    c.decreaseEvilness(5);
    c.increaseCuteness(10);
    cout << c.getName() << " went to spa! Evilness down, cuteness up.\n";
}
string SendToSpaAction::name() const { return "Send to Spa"; }
unique_ptr<CatAction> SendToSpaAction::clone() const { return make_unique<SendToSpaAction>(*this); }
