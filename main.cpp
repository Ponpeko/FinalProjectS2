#include "LaundryGame.h"
#include <iostream>

using namespace std;

int main() {
    LaundryGame game;

    int choice;
    do {
        cout << "=== Main Menu ===" << endl;
        cout << "1. Terima Pesanan" << endl;
        cout << "2. Lihat Antrean Pesanan" << endl;
        cout << "3. Selesaikan Pesanan" << endl;
        cout << "4. End Day" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> choice;

        switch (choice) {
            case 1:
                game.acceptOrder();
                break;
            case 2:
                game.viewStack();
                break;
            case 3:
                game.completeOrder();
                break;
            case 4:
                game.endDay();
                break;
            case 0:
                std::cout << "Terima kasih telah bermain!" << std::endl;
                break;
            default:
                std::cout << "Pilihan tidak valid. Silakan coba lagi." << std::endl;
                break;
        }

        cout << endl;

    } while (choice != 0);

    return 0;
}

