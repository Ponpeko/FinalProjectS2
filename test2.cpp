#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

struct LaundryOrder {
    string customerName;
    int shirtCount;
    int pantsCount;
    int jacketCount;
    bool isCompleted;
};

struct SalesRecord {
    int orderId;
    string customerName;
    int amount;

    SalesRecord(int id, const string& name, int amt) : orderId(id), customerName(name), amount(amt) {}
};

class LaundryGame {
private:
    queue<LaundryOrder> orderQueue;
    int coins;
    int queueSize;
    int day;
    vector<SalesRecord> salesRecords;
    int orderIdCounter;

public:
    LaundryGame() : coins(0), queueSize(4), day(1), orderIdCounter(1) {
        srand(time(0));
    }

    void acceptOrder() {
        string name, serviceType;
        int shirtCount, pantsCount, jacketCount;

        cout << "Masukkan nama pelanggan: ";
        cin.ignore();
        getline(cin, name);

        cout << endl;
        cout << "Rincian pesanan" << endl;

        cout << "Jumlah baju   : ";
        cin >> shirtCount;

        cout << "Jumlah celana : ";
        cin >> pantsCount;

        cout << "Jumlah jaket  : ";
        cin >> jacketCount;

        LaundryOrder order = { name, shirtCount, pantsCount, jacketCount, false };

        if (orderQueue.size() >= queueSize) {
            cout << "Antrean penuh. Tunggu pelanggan lain menyelesaikan pesanan." << endl;
            return;
        }

        orderQueue.push(order);
        cout << "Pesanan dari " << order.customerName << " sudah diterima." << endl;

        ofstream outFile("orders.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "Nama          : " << order.customerName << endl;
            outFile << "Jumlah baju   : " << order.shirtCount << endl;
            outFile << "Jumlah celana : " << order.pantsCount << endl;
            outFile << "Jumlah jaket  : " << order.jacketCount << endl;
            outFile << endl;
            outFile.close();
        } else {
            cout << "Failed to open file." << endl;
        }

        getch();
        system("cls");
    }

    void viewOrderQueue() {
        system("cls");

        if (orderQueue.empty()) {
            cout << "Antrean kosong." << endl;
            getch();
        }

        cout << "Lihat Antrean (Max: " << queueSize << ")" << endl;
        int index = 1;
        queue<LaundryOrder> tempQueue = orderQueue;
        while (!tempQueue.empty()) {
            LaundryOrder order = tempQueue.front();
            cout << index << ". Pesanan " << order.customerName << endl;
            cout << "   - Jumlah baju   : " << order.shirtCount << endl;
            cout << "   - Jumlah celana : " << order.pantsCount << endl;
            cout << "   - Jumlah jaket  : " << order.jacketCount << endl;
            tempQueue.pop();
            index++;
        }

        getch();
        system("cls");
    }

    void completeOrder() {
        if (orderQueue.empty()) {
            cout << "Tidak ada pesanan." << endl;
            getch();
            system("cls");
        }

        LaundryOrder order = orderQueue.front();
        orderQueue.pop();
        order.isCompleted = true;
        int earnedCoins = (rand() % 9 + 2) * 500;
        coins += earnedCoins;
        cout << "Pesanan dari " << order.customerName << " sudah selesai. Kamu mendapatkan " << earnedCoins << " coins." << endl;

        SalesRecord record(orderIdCounter, order.customerName, earnedCoins);
        salesRecords.push_back(record);
        orderIdCounter++;

        getch();
        system("cls");
    }

    void endDay() {      
        system("cls");

        if (!orderQueue.empty()) {
        cout << "Masih ada pesanan yang belum selesai." << endl;       
        getch();
        system("cls");
        return;
        }

        cout << "\tSales Record Day " << day << endl;
        ifstream inFile("orders.txt");
        if (inFile.is_open()) {
            string line;
            while (getline(inFile, line)) {
                cout << line << endl;
            }
            inFile.close();
        } else {
            cout << "Failed to open file." << endl;
        }
            
        cout << endl;
        char choice;
        cout << "End Day Menu:" << endl;
        cout << "1. Upgrade antrian (20000)" << endl;
        cout << "2. Next Day" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case '1':
            upgrade();
            break;
        case '2':
            nextDay();
            break;
        default:
            cout << "Pilihan salah." << endl;
            break;
        }

        day++;
    }

    void displayDay(){
        cout << "  Day: " << day << "\t\tCoins: " << coins << endl;
    }

private:
    void upgrade() {
        if (coins >= 20000) {
            coins -= 20000;
            queueSize += 4;
            cout << "Antiran telah di upgrade. Jumlah maksimal " << queueSize << "." << endl;
        } else {
            cout << "Coin tidak cukup." << endl;
        }
        
        salesRecords.clear();
        remove("orders.txt");

        getch();
        system("cls");
    }

    void nextDay() {
        while (!orderQueue.empty()) {
            LaundryOrder order = orderQueue.front();
            orderQueue.pop();
            order.isCompleted = true;
        }
        cout << "Day completed " << day << endl;

        salesRecords.clear();
        remove("orders.txt");

        getch();
        system("cls");
    }
};

int main() {
    LaundryGame game;

    int choice;
    do {
        cout << "================================" << endl;
        cout << "\t Kiki's Laundry" << endl;
        game.displayDay();
        cout << "================================" << endl;
        cout << "1. Terima Pesanan" << endl;
        cout << "2. Lihat Antrean " << endl;
        cout << "3. Selesaikan Pesanan" << endl;
        cout << "4. End Day" << endl;
        cout << "5. Exit" << endl;
        cout << "Masukkan pilihan: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1:
                game.acceptOrder();
                break;
            case 2:
                game.viewOrderQueue();
                break;
            case 3:
                game.completeOrder();
                break;
            case 4:
                game.endDay();
                break;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }

        cout << endl;

    } while (choice != 5);

    return 0;
}
