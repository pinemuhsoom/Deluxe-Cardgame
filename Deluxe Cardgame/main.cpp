#include <iostream>
#include "blackjack.hpp" // ���� ���� ��� ����
#include <windows.h>

int main() {
    int choice;
    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "���� ī����ӿ� ���Ű��� ȯ���մϴ�!" << std::endl;
    std::cout << "������ ����ּ��� :" << std::endl;
    std::cout << "1. ����" << std::endl;
    std::cout << "2. ������" << std::endl;
    std::cout << "------------------------------------------------" << std::endl;

    std::cin >> choice;

    if (choice == 1) {
        system("cls");
        std::cout << "------------------------------------------------" << std::endl;
        std::cout << "������ �����մϴ�!" << std::endl;
        playBlackjack(); // ���� ���� ����
    }
    else if (choice == 2) {
        std::cout << "�����մϴ�" << std::endl;
        return 0;
    }
    else {
        std::cout << "�߸��� �����Դϴ�. �����մϴ�." << std::endl;
        return 0;
    }

    return 0;
}