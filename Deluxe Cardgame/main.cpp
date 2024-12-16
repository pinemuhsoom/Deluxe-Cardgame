#include <iostream>
#include "blackjack.hpp" // 블랙잭 관련 헤더 파일
#include <windows.h>

int main() {
    int choice;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "종합 카드게임에 오신것을 환영합니다!" << std::endl;
    std::cout << "게임을 골라주세요 :" << std::endl;
    std::cout << "1. 블랙잭" << std::endl;
    std::cout << "2. 나가기" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    std::cin >> choice;

    if (choice == 1) {
        system("cls");
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "블랙잭을 시작합니다!" << std::endl;
        playBlackjack(); // 블랙잭 게임 시작
    }
    else if (choice == 2) {
        std::cout << "종료합니다" << std::endl;
        return 0;
    }
    else {
        std::cout << "잘못된 선택입니다. 종료합니다." << std::endl;
        return 0;
    }

    return 0;
}