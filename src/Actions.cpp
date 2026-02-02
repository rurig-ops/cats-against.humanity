#include "Actions.h"
#include "CatOverlord.h"
#include <iostream>
#include <string> // Necesar pentru std::to_string

void StealFoodAction::execute(Cat& c, Humanity& h) {
    std::cout << c.getName() << " is stealing food for the cause!\n";
    c.trainEvil(2);
    h.increaseSuspicion(3);
}

void SpreadChaosAction::execute(Cat& c, Humanity& h) {
    std::cout << c.getName() << " is spreading absolute chaos!\n";
    c.trainEvil(5);
    h.increaseSuspicion(8);
}

void RecruitCatsAction::execute(Cat& c, Humanity&) {
    if (!overlord) return;

    std::string newName = "Operative_" + std::to_string(Cat::getTotalCats());
    Cat newCat(newName);

    overlord->addCat(newCat);
    std::cout << c.getName() << " recruited " << newName << " to the conspiracy.\n";
}

void SendToSpaAction::execute(Cat& c, Humanity&) {
    std::cout << c.getName() << " is relaxing at the spa to lower suspicion.\n";
    c.decreaseEvilness(5);
    c.increaseCuteness(10);
}

void PerformDanceRitualAction::execute(Cat& c, Humanity& h) {
    std::cout << c.getName() << " is performing the ancient feline ritual! :3\n";
    c.increaseCuteness(10);
    h.increaseSuspicion(15);
}