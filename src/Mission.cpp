#include "Mission.h"
#include "GameSettings.h"

Mission::Mission(const std::string& n, int diff, int money, int chaos, int hunger, int minE, int minL, int minC, MissionType t)
    : name(n), difficulty(diff), rewardMoney(money), rewardChaos(chaos), hungerCost(hunger),
      minEvilness(minE), minLoyalty(minL), minCuteness(minC), type(t) {}

bool Mission::attempt(const Cat& c) const {
    int gameDiff = GameSettings::getInstance().getDifficulty();
    int difficultyPenalty = (gameDiff - 1) * 15;

    int baseChance = (type == EVIL) ? c.getEvilness() : c.getCuteness();

    if (c.getLoyalty() < minLoyalty) {
        std::cout << "cat is not loyal enough" << std::endl;
        return false;
    }

    int roll = (std::rand() % 100) + 1;

    // succesul depinde de noroc minus penalizarea de dificultate
    if (baseChance > (roll + difficultyPenalty)) {
        std::cout << "mission success: " << name << " (lvl " << gameDiff << ")" << std::endl;
        return true;
    }

    std::cout << "mission failed" << std::endl;
    return false;
}

std::ostream& operator<<(std::ostream& os, const Mission& m) {
    os << "mission: " << m.name << " [" << m.rewardMoney << "$]";
    return os;
}

