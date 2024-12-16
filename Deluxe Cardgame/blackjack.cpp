#include "blackjack.hpp"
#include "Deck.hpp"
#include "Player.hpp"
#include "BettingSystem.hpp"
#include <iostream>
#include <vector>
#include <Windows.h>

// 여러 카드의 ASCII를 가로로 출력
void printCardsHorizontally(const std::vector<Card>& cards) {
    if (cards.empty()) {
        std::cout << "No cards to display.\n";
        return;
    }

    std::vector<std::vector<std::string>> asciiCards;
    for (const auto& card : cards) {
        asciiCards.push_back(card.toStringLines());
    }

    for (size_t line = 0; line < asciiCards[0].size(); ++line) {
        for (const auto& ascii : asciiCards) {
            std::cout << ascii[line] << " ";
        }
        std::cout << "\n";
    }
}

// 블랙잭 게임의 실행 흐름
void playBlackjack() {
    Deck deck;
    deck.shuffle();

    Player player1("Player", 100); // 플레이어
    Player dealer("Dealer", 100); // 딜러
    BettingSystem bettingSystem;

    // 플레이어와 딜러 초기 카드 배분 (2장씩임)
    player1.receiveCard(deck.drawCard());
    player1.receiveCard(deck.drawCard());
    dealer.receiveCard(deck.drawCard());
    dealer.receiveCard(deck.drawCard());

    // 베팅
    int betAmount;
    do {
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "현재 자금 : " << player1.getBalance() << std::endl;
        std::cout << "베팅할 금액을 입력하세요 : ";
        std::cin >> betAmount;
        if (betAmount > player1.getBalance()) {
            std::cout << "자금을 초과된 베팅금액입니다!" << std::endl;
        }   
    } while (betAmount > player1.getBalance());

    if (betAmount > player1.getBalance()) {
        std::cout << "자금을 초과된 베팅금액입니다!" << std::endl;
        return;
    }

    player1.placeBet(betAmount);
    bettingSystem.placeBet(&player1, betAmount);

    // 플레이어의 행동
    std::string action;
    while (true) {
        system("cls");
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "베팅된 금액 : " << betAmount << std::endl;
        std::cout << "현재 카드 : " << std::endl;;
        printCardsHorizontally(player1.getHand());
        std::cout << std:: endl << "카드 총합 : " << player1.getScore() << std::endl;

        if (player1.getScore() > 21) {
            std::cout << "버스트! 딜러의 승리입니다!" << std::endl;
            return;
        }

        std::cout << "행동을 골라주세요 (hit : 카드 뽑기 / stand : 안 뽑기): ";
        std::cin >> action;

        if (action == "hit") {
            Card newCard = deck.drawCard();
            player1.receiveCard(newCard);
            std::cout << "당신이 받은 카드 : " << std::endl;;
            printCardsHorizontally(dealer.getHand());
        }
        else if (action == "stand") {
            break;
        }
        else {
            std::cout << "잘못된 입력입니다. 다시 시도해주세요" << std::endl;
        }
    }
    Sleep(1000);
    //딜러 행동전 딜러의 카드
    std::cout << "현재 딜러의 카드 : " << std::endl;;
    printCardsHorizontally(dealer.getHand());
    std::cout << std::endl << "현재 딜러의 카드 총합: " << dealer.getScore() << std::endl;
    Sleep(1000);
    // 딜러의 행동
    while (dealer.getScore() < 17) {
        std::cout << "딜러는 카드를 뽑았습니다." << std::endl;
        Sleep(500);
        Card newCard = deck.drawCard();
        dealer.receiveCard(newCard);
    }

    std::cout << "딜러의 최종 카드 : " << std::endl;;
    printCardsHorizontally(dealer.getHand());
    std::cout << std::endl << "딜러의 카드 총합: " << dealer.getScore() << std::endl;

    // 승자 결정
    if (dealer.getScore() > 21 || player1.getScore() > dealer.getScore()) {
        std::cout << "플레이어의 승리!" << std::endl;
        bettingSystem.payoutWinners({ &player1 });
    }
    else if (player1.getScore() < dealer.getScore()) {
        std::cout << "딜러의 승리!" << std::endl;
    }
    else {
        std::cout << "무승부!" << std::endl;
    }
}