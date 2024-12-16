#include "blackjack.hpp"
#include "Deck.hpp"
#include "Player.hpp"
#include "BettingSystem.hpp"
#include <iostream>
#include <vector>
#include <Windows.h>

// ���� ī���� ASCII�� ���η� ���
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

// ���� ������ ���� �帧
void playBlackjack() {
    Deck deck;
    deck.shuffle();

    Player player1("Player", 100); // �÷��̾�
    Player dealer("Dealer", 100); // ����
    BettingSystem bettingSystem;

    // �÷��̾�� ���� �ʱ� ī�� ��� (2�徿��)
    player1.receiveCard(deck.drawCard());
    player1.receiveCard(deck.drawCard());
    dealer.receiveCard(deck.drawCard());
    dealer.receiveCard(deck.drawCard());

    // ����
    int betAmount;
    do {
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "���� �ڱ� : " << player1.getBalance() << std::endl;
        std::cout << "������ �ݾ��� �Է��ϼ��� : ";
        std::cin >> betAmount;
        if (betAmount > player1.getBalance()) {
            std::cout << "�ڱ��� �ʰ��� ���ñݾ��Դϴ�!" << std::endl;
        }   
    } while (betAmount > player1.getBalance());

    if (betAmount > player1.getBalance()) {
        std::cout << "�ڱ��� �ʰ��� ���ñݾ��Դϴ�!" << std::endl;
        return;
    }

    player1.placeBet(betAmount);
    bettingSystem.placeBet(&player1, betAmount);

    // �÷��̾��� �ൿ
    std::string action;
    while (true) {
        system("cls");
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "���õ� �ݾ� : " << betAmount << std::endl;
        std::cout << "���� ī�� : " << std::endl;;
        printCardsHorizontally(player1.getHand());
        std::cout << std:: endl << "ī�� ���� : " << player1.getScore() << std::endl;

        if (player1.getScore() > 21) {
            std::cout << "����Ʈ! ������ �¸��Դϴ�!" << std::endl;
            return;
        }

        std::cout << "�ൿ�� ����ּ��� (hit : ī�� �̱� / stand : �� �̱�): ";
        std::cin >> action;

        if (action == "hit") {
            Card newCard = deck.drawCard();
            player1.receiveCard(newCard);
            std::cout << "����� ���� ī�� : " << std::endl;;
            printCardsHorizontally(dealer.getHand());
        }
        else if (action == "stand") {
            break;
        }
        else {
            std::cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���" << std::endl;
        }
    }
    Sleep(1000);
    //���� �ൿ�� ������ ī��
    std::cout << "���� ������ ī�� : " << std::endl;;
    printCardsHorizontally(dealer.getHand());
    std::cout << std::endl << "���� ������ ī�� ����: " << dealer.getScore() << std::endl;
    Sleep(1000);
    // ������ �ൿ
    while (dealer.getScore() < 17) {
        std::cout << "������ ī�带 �̾ҽ��ϴ�." << std::endl;
        Sleep(500);
        Card newCard = deck.drawCard();
        dealer.receiveCard(newCard);
    }

    std::cout << "������ ���� ī�� : " << std::endl;;
    printCardsHorizontally(dealer.getHand());
    std::cout << std::endl << "������ ī�� ����: " << dealer.getScore() << std::endl;

    // ���� ����
    if (dealer.getScore() > 21 || player1.getScore() > dealer.getScore()) {
        std::cout << "�÷��̾��� �¸�!" << std::endl;
        bettingSystem.payoutWinners({ &player1 });
    }
    else if (player1.getScore() < dealer.getScore()) {
        std::cout << "������ �¸�!" << std::endl;
    }
    else {
        std::cout << "���º�!" << std::endl;
    }
}