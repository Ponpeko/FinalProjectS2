#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <ctime>

using namespace std;

struct LaundryOrder {
    string customerName;
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

    void acceptOrder(const LaundryOrder& order) {
        if (orderQueue.size() >= queueSize) {
            cout << "Order queue is full. Please wait for some orders to be completed." << endl;
            return;
        }

        orderQueue.push(order);
        cout << "Accepted new order for " << order.customerName << endl;
        getch();
        system("cls");
    }

    void viewOrderQueue() {
        if (orderQueue.empty()) {
            cout << "Order queue is empty." << endl;
            return;
        }

        cout << "Order Queue:" << endl;
        int index = 1;
        queue<LaundryOrder> tempQueue = orderQueue;
        while (!tempQueue.empty()) {
            LaundryOrder order = tempQueue.front();
            cout << index << ". Order for " << order.customerName << endl;
            tempQueue.pop();
            index++;
        }
        getch();
        system("cls");
    }

    void completeOrder() {
        if (orderQueue.empty()) {
            cout << "No orders in the queue." << endl;
            return;
        }

        LaundryOrder order = orderQueue.front();
        orderQueue.pop();
        order.isCompleted = true;
        int earnedCoins = (rand() % 9 + 2) * 500; // Jumlah koin acak antara 1000 dan 5000 dengan kelipatan 500
        coins += earnedCoins;
        cout << "Completed order for " << order.customerName << ". You earned " << earnedCoins << " coins." << endl;

        SalesRecord record(orderIdCounter, order.customerName, earnedCoins);
        salesRecords.push_back(record);
        orderIdCounter++;

        getch();
        system("cls");
    }

    void endDay() {
        printSalesRecords();

        char choice;
        cout << "=====================" << endl;
        cout << "1. Upgrade Queue" << endl;
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
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    void printSalesRecords() {
        cout << "Sales Records:" << endl;
        for (const auto& record : salesRecords) {
            cout << record.orderId << ". " << record.customerName << " " << record.amount << endl;
        }
    }

    void displayDay(){
        cout << "  Day: " << day << "\t\t\tCoins: " << coins << endl;
    }

private:
    void upgrade() {
        if (coins >= 20000) {
            coins -= 20000;
            queueSize += 1;
            cout << "Queue size upgraded. New queue size is " << queueSize << "." << endl;
        } else {
            cout << "Insufficient coins to upgrade queue size." << endl;
        }
    }

    void nextDay() {
        while (!orderQueue.empty()) {
            LaundryOrder order = orderQueue.front();
            orderQueue.pop();
            order.isCompleted = true;
        }
        cout << "Finished day " << day << ". All orders completed." << endl;
        day++;
        system("cls");
    }   
};

int main() {
    int choice;

    LaundryGame game;
    do {
        cout << "================================" << endl;
        cout << "\t Kiki's Laundry" << endl;
        game.displayDay();
        cout << "================================" << endl;
        cout << "1. Accept Order" << endl;
        cout << "2. View Order Queue" << endl;
        cout << "3. Complete Order" << endl;
        cout << "4. End Day" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
            case 1: {
                system("cls");
                string name;
                cout << "Enter customer name: ";
                cin.ignore();
                getline(cin, name);
                LaundryOrder order = { name, false };
                game.acceptOrder(order);
                break;
            }
            case 2:
                game.viewOrderQueue();
                break;
            case 3:
                game.completeOrder();
                break;
            case 4:
                game.endDay();
                break;;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;

    } while (choice != 6);

    return 0;
}
