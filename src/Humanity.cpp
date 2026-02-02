#include "Humanity.h"
#include <algorithm>

Humanity::Humanity(int start, int maxS) : suspicion(start), maxSuspicion(maxS) {}

void Humanity::increaseSuspicion(int val) {
    suspicion = std::min(maxSuspicion, suspicion + val);
}

void Humanity::decreaseSuspicion(int val) {
    suspicion = std::max(0, suspicion - val);
}

bool Humanity::isGameOver() const { return suspicion >= maxSuspicion; }

std::ostream& operator<<(std::ostream& os, const Humanity& h) {
    os << "Suspicion: " << h.suspicion << "/" << h.maxSuspicion;
    return os;
}