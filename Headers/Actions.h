#ifndef ACTIONS_H
#define ACTIONS_H

#include <memory>
#include <string>
#include <iostream>
#include "Cat.h"
#include "Humanity.h"

class CatOverlord;

class CatAction {
public:
    virtual ~CatAction() = default;
    virtual void execute(Cat& c, Humanity& h) = 0;
    [[nodiscard]] virtual std::string name() const = 0;
    [[nodiscard]] virtual std::unique_ptr<CatAction> clone() const = 0;

    void perform(Cat& c, Humanity& h) {
        std::cout << c.getName() << " is performing action: " << name() << std::endl;
        execute(c, h);
    }
};

class StealFoodAction : public CatAction {
public:
    void execute(Cat& c, Humanity& h) override;
    [[nodiscard]] std::string name() const override { return "Steal Food"; }
    [[nodiscard]] std::unique_ptr<CatAction> clone() const override { return std::make_unique<StealFoodAction>(*this); }
};

class SpreadChaosAction : public CatAction {
public:
    void execute(Cat& c, Humanity& h) override;
    [[nodiscard]] std::string name() const override { return "Spread Chaos"; }
    [[nodiscard]] std::unique_ptr<CatAction> clone() const override { return std::make_unique<SpreadChaosAction>(*this); }
};

class RecruitCatsAction : public CatAction {
private:
    CatOverlord* overlord = nullptr; // Initializare pentru Cppcheck
public:
    RecruitCatsAction() = default;
    explicit RecruitCatsAction(CatOverlord* o) : overlord(o) {}
    void setOverlord(CatOverlord* o) { overlord = o; } // Necesar pentru Prototype Fix
    void execute(Cat& c, Humanity& h) override;
    [[nodiscard]] std::string name() const override { return "Recruit Cats"; }
    [[nodiscard]] std::unique_ptr<CatAction> clone() const override { return std::make_unique<RecruitCatsAction>(*this); }
};

class SendToSpaAction : public CatAction {
public:
    void execute(Cat& c, Humanity&) override;
    [[nodiscard]] std::string name() const override { return "Send to Spa"; }
    [[nodiscard]] std::unique_ptr<CatAction> clone() const override { return std::make_unique<SendToSpaAction>(*this); }
};

class PerformDanceRitualAction : public CatAction {
public:
    void execute(Cat& c, Humanity& h) override;
    [[nodiscard]] std::string name() const override { return "Perform Dance Ritual"; }
    [[nodiscard]] std::unique_ptr<CatAction> clone() const override { return std::make_unique<PerformDanceRitualAction>(*this); }
};

#endif