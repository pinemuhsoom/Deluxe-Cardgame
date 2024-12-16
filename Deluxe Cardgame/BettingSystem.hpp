#ifndef BETTING_SYSTEM_HPP
#define BETTING_SYSTEM_HPP

#include "Bet.hpp"
#include <vector>
#include <iostream>

class BettingSystem {
private:
    int totalPot;
    std::vector<Bet> bets;

public:
    BettingSystem() : totalPot(0) {}

    void placeBet(Player* player, int amount) {
        if (amount > 0) {
            bets.emplace_back(player, amount);
            totalPot += amount;
        }
    }

    int calculateTotal() const {
        return totalPot;
    }

    void payoutWinners(std::vector<Player*> winners) {
        if (winners.empty()) return;

        int payout = totalPot / winners.size();
        for (auto* winner : winners) {
            std::cout << winner->getName() << " �� �¸� " << payout << std::endl;
            winner->placeBet(-payout); // �ݾ��� ���޹���
        }
        totalPot = 0;
    }
};

#endif