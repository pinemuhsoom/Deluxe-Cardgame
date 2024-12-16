#ifndef CARD_HPP
#define CARD_HPP

#include <iostream>
#include <string>
#include <vector>

class Card {
private:
    std::string suit;   // 무늬
    std::string rank;   // 숫자 또는 랭크
    int value;          // 블랙잭 점수 계산용 값

public:
    Card(std::string rank, std::string suit, int value)
        : rank(rank), suit(suit), value(value) {}

    int getValue() const { return value; }
    std::string getSuit() const { return suit; }
    std::string getRank() const { return rank; }

    // 유니코드 심볼 반환
    std::string getSuitSymbol() const {
        if (suit == "Heart") return "\u2665";       // ♥
        if (suit == "Diamond") return "\u25C6";    // ♦ 얘가 u2666 인데 2665도 되고 2667도 되는데 진짜 왜? 암튼 ?로 뜨는 오류가 계속 나서 charset 바꾸거나 프로젝트 설정을 건드리려했는데 다른게 작동 안되서 포기하고 ◆로 교체
        if (suit == "Clover") return "\u2663";       // ♣
        if (suit == "Spade") return "\u2660";      // ♠
        return suit; //디버깅용 확인 / 원래는 ?로 처리했음
    }

    // 카드 정보 출력용 메서드
    /*std::string toString() const {
        return rank + " " + getSuitSymbol();
        return R"(

        주어진대로 출력한다는 건데 원하는 모양을 만들기 빡세서 포기

)";
         
    }*/

    //gpt의 도움으로 아스키 코드로 이쁘게 카드 출력하려함 근데 이거 하나 툭 던져줘서 기존에 카드 출력하던거랑 안맞음
    //void printAscii() const {
    //    std::string topRank = rank + (rank.size() == 1 ? " " : ""); // 숫자 정렬
    //    std::string bottomRank = (rank.size() == 1 ? " " : "") + rank;

    //    std::cout << "┌─────────┐\n";
    //    std::cout << "│" << topRank << "       │\n";
    //    std::cout << "│         │\n";
    //    std::cout << "│    " << getSuitSymbol() << "    │\n";
    //    std::cout << "│         │\n";
    //    std::cout << "│       " << bottomRank << "│\n";
    //    std::cout << "└─────────┘\n";
    //}

    //Raw 스트링이랑 gpt의 아스키 아트 합쳐서 완성
    std::string toString() const { // 10의 경우 이쁜 카드 모양이 깨짐
        return R"(
┌─────┐
│)" + getSuitSymbol() + R"(   │
│     │
│    )" + rank + R"(│
└─────┘)";
    }

    std::vector<std::string> toStringLines() const {
        std::vector<std::string> lines;
        lines.push_back("┌─────┐");
        lines.push_back("│" + getSuitSymbol() + "   │");
        lines.push_back("│     │");
        lines.push_back("│   " + (rank.size() == 1 ? " " + rank : rank) + "│");
        lines.push_back("└─────┘");
        return lines;
    }


};

#endif