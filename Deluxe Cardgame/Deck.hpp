#ifndef DECK_HPP
#define DECK_HPP

#include "Card.hpp"
#include <vector>
#include <algorithm>
#include <random>

class Deck {
private:
    std::vector<Card> cards;

public:
    Deck() { defaultDeck(); }

    void defaultDeck() {
        const std::vector<std::string> suits = { "Heart", "Diamond", "Clover", "Spade" };
        const std::vector<std::pair<std::string, int>> ranks = {
            {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7},
            {"8", 8}, {"9", 9}, {"10", 10}, {"J", 10}, {"Q", 10},
            {"K", 10}, {"A", 11}
        };

        for (const auto& suit : suits) {
            for (const auto& rank : ranks) {
                cards.emplace_back(rank.first, suit, rank.second);  
            }
        }
    }

    void shuffle() {
        std::random_device rd;
        //난수 생성 : 시스템 물리적 장치나 특성에서 난수를 생성함
        std::mt19937 g(rd());
        std::shuffle(cards.begin(), cards.end(), g);
    }

    Card drawCard() {
        if (cards.empty()) defaultDeck();
        Card card = cards.back();
        cards.pop_back();
        return card;
    }

    void printCardsHorizontally(const std::vector<Card>& cards) {
        // 각 카드의 ASCII 아트를 줄 단위로 저장
        std::vector<std::vector<std::string>> asciiCards;
        for (const auto& card : cards) {
            asciiCards.push_back(card.toStringLines());
        }

        // 카드가 없으면 출력 중단
        if (asciiCards.empty()) {
            std::cout << "No cards to display.\n";
            return;
        }

    }

};

#endif