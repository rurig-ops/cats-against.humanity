//
// Created by Yoga 7Pro on 2/2/2026.
//
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

/**
 * @class GameException
 * @brief Base class for all custom exceptions in the Cat Conspiracy game.
 */
class GameException : public std::exception {
protected:
    std::string message;
public:
    explicit GameException(std::string msg) : message(std::move(msg)) {}
    [[nodiscard]] const char* what() const noexcept override { return message.c_str(); }
};

class InvalidCatIndexException : public GameException {
public:
    explicit InvalidCatIndexException(int index)
        : GameException("Invalid cat index: " + std::to_string(index)) {}
};

class NotEnoughMoneyException : public GameException {
public:
    explicit NotEnoughMoneyException(int cost, int money)
        : GameException("Not enough money! Needed: " + std::to_string(cost) + ", Available: " + std::to_string(money)) {}
};

class NotEnoughAPException : public GameException {
public:
    explicit NotEnoughAPException(int needed, int available)
        : GameException("Not enough action points! Needed: " + std::to_string(needed) + ", Available: " + std::to_string(available)) {}
};

#endif