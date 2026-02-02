#ifndef MISSION_H
#define MISSION_H

#include <string>
#include "Cat.h"

/**
 * @class Mission
 * @brief Defines a task for a cat with specific requirements and rewards.
 */
class Mission {
public:
    enum MissionType { EVIL, PR };
private:
    std::string name;
    [[maybe_unused]] int difficulty;
    int  rewardMoney, rewardChaos, hungerCost;
    int minEvilness, minLoyalty, minCuteness;
    MissionType type;

public:
    Mission(const std::string& n, int diff, int money, int chaos, int hunger, int minE, int minL, int minC, MissionType t);

    [[nodiscard]] const std::string& getName() const { return name; }
    [[nodiscard]] int getRewardMoney() const { return rewardMoney; }
    [[nodiscard]] int getRewardChaos() const { return rewardChaos; }
    [[nodiscard]] int getHungerCost() const { return hungerCost; }
    [[maybe_unused]] [[nodiscard]] MissionType getType() const { return type; }

    /** @brief Checks if a cat's stats meet the mission requirements. */
    [[nodiscard]] bool attempt(const Cat& c) const;

    friend std::ostream& operator<<(std::ostream& os, const Mission& m);
};

#endif