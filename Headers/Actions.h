#ifndef ACTIONS_H
#define ACTIONS_H

#include <memory>
#include <string>
#include <iostream>
#include "Cat.h"
#include "Humanity.h"

class CatOverlord; // Forward declaration

/**
 * @class CatAction
 * @brief Abstract base class for all actions a cat can perform.
 */
class CatAction {
public:
    virtual ~CatAction() = default;

    /**
     * @brief Executes the specific logic of the action.
     * @param c The cat performing the action.
     * @param h The humanity state affected by the action.
     */
    virtual void execute(Cat& c, Humanity& h) = 0;

    /**
     * @brief Returns the display name of the action.
     */
    [[nodiscard]] virtual std::string name() const = 0;

    /**
     * @brief Creates a deep copy of the action.
     */
    [[nodiscard]] virtual std::unique_ptr<CatAction> clone() const = 0;

    /**
     * @brief Wrapper method to print action start and then execute.
     */
    void perform(Cat& c, Humanity& h) {
        std::cout << c.getName() << " is performing action: " << name() << std::endl;
        execute(c, h);
    }
};

/** @brief Action: Steal food to train evil and increase suspicion. */
class StealFoodAction : public CatAction {
public:
    void execute(Cat& c, Humanity& h) override;
    [[nodiscard]] std::string name() const override { return "Steal Food"; }
    [[nodiscard]] std::unique_ptr<CatAction> clone() const override { return std::make_unique<StealFoodAction>(*this); }
};

/** @brief Action: High risk, high reward for evilness and chaos. */
class SpreadChaosAction : public CatAction {
public:
    void execute(Cat& c, Humanity& h) override;
    [[nodiscard]] std::string name() const override { return "Spread Chaos"; }
    [[nodiscard]] std::unique_ptr<CatAction> clone() const override { return std::make_unique<SpreadChaosAction>(*this); }
};

/** @brief Action: Adds a new cat to the Overlord's roster. */
class RecruitCatsAction : public CatAction {
private:
    CatOverlord* overlord;
public:
    explicit RecruitCatsAction(CatOverlord* o) : overlord(o) {}
    void execute(Cat& c, Humanity& h) override;
    [[nodiscard]] std::string name() const override { return "Recruit Cats"; }
    [[nodiscard]] std::unique_ptr<CatAction> clone() const override { return std::make_unique<RecruitCatsAction>(*this); }
};

/** @brief Action: Increases cuteness and decreases evilness. */
class SendToSpaAction : public CatAction {
public:
    void execute(Cat& c, Humanity& h) override;
    [[nodiscard]] std::string name() const override { return "Send to Spa"; }
    [[nodiscard]] std::unique_ptr<CatAction> clone() const override { return std::make_unique<SendToSpaAction>(*this); }
};

/** @brief Action: Complex ritual affecting multiple stats. */
class PerformDanceRitualAction : public CatAction {
public:
    void execute(Cat& c, Humanity& h) override;
    [[nodiscard]] std::string name() const override { return "Perform Dance Ritual"; }
    [[nodiscard]] std::unique_ptr<CatAction> clone() const override { return std::make_unique<PerformDanceRitualAction>(*this); }
};

#endif