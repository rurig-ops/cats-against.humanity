#include "Mission.h"

Mission::Mission(const std::string& n, int diff, int money, int chaos, int hunger, int minE, int minL, int minC, MissionType t)
    : name(n), difficulty(diff), rewardMoney(money), rewardChaos(chaos), hungerCost(hunger),
      minEvilness(minE), minLoyalty(minL), minCuteness(minC), type(t) {}

bool Mission::attempt(const Cat& c) const {
    if (type == EVIL) return c.getEvilness() >= minEvilness && c.getLoyalty() >= minLoyalty;
    return c.getLoyalty() >= minLoyalty && c.getCuteness() >= minCuteness;
}

std::ostream& operator<<(std::ostream& os, const Mission& m) {
    os << "Mission: " << m.name;
    return os;
}