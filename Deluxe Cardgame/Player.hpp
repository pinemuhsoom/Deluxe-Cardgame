#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Card.hpp"
#include <vector>
#include <string>

class Player {
private:
    std::string name;
    std::vector<Card> hand;
    int balance;
    bool isFolded;

public:
    Player(std::string name, int balance = 100)
        : name(name), balance(balance), isFolded(false) {}

    void receiveCard(const Card& card) {
        hand.push_back(card);
    }

    int getScore() const {
        int score = 0;
        int aces = 0;

        for (const Card& card : hand) {
            score += card.getValue();
            if (card.getRank() == "Ace") ++aces;
        }

        while (score > 21 && aces > 0) {
            score -= 10;
            --aces;
        }

        return score;
    }

    void placeBet(int amount) {
        if (amount <= balance) {
            balance -= amount;
        }
    }

    void fold() {
        isFolded = true;
    }

    bool hasFolded() const {
        return isFolded;
    }

    int getBalance() const {
        return balance;
    }

    std::string getName() const {
        return name;
    }

    // **추가: 현재 핸드 반환**
    const std::vector<Card>& getHand() const {
        return hand;
    }
};

#endif