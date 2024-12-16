#ifndef BET_HPP
#define BET_HPP

#include "Player.hpp"

class Bet {
private:
    int amount;
    Player* player;

public:
    Bet(Player* player, int amount)
        : player(player), amount(amount) {}

    int getAmount() const { return amount; }
    Player* getPlayer() const { return player; }
};

#endif