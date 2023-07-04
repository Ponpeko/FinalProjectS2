#include "LaundryGame.h"
#include <iostream>
#include <fstream>

LaundryGame::LaundryGame() {
    
}

void LaundryGame::acceptOrder() {
    Order newOrder;
    std::cout << "Masukkan nama pelanggan: ";
    std::cin.ignore(); // Menghapus karakter newline di input sebelumnya
    std::getline(std::cin, newOrder.name);
    newOrder.daysLeft = 3;
    orderStack.push(newOrder);

    std::ofstream file("pesanan.txt", std::ios::app); // Membuka file pesanan.txt untuk menambahkan pesanan baru
    file << newOrder.name << std::endl;
    file.close();

    std::cout << "Pesanan " << newOrder.name << " telah ditambahkan." << std::endl;
}

void LaundryGame::viewStack() {
    if (!orderStack.empty()) {
        std::cout << "Stack Pesanan:" << std::endl;
        int index = 1;
        std::stack<Order> tempStack = orderStack;
        while (!tempStack.empty()) {
            const Order& order = tempStack.top();
            std::cout << index << ". " << order.name << " (Tersisa " << order.daysLeft << " hari)" << std::endl;
            tempStack.pop();
            index++;
        }
    } else {
        std::cout << "Tidak ada pesanan dalam stack." << std::endl;
    }
}

void LaundryGame::completeOrder() {
    if (!orderStack.empty()) {
        Order completedOrder = orderStack.top();
        orderStack.pop();
        std::cout << "Pesanan " << completedOrder.name << " telah selesai." << std::endl;
    } else {
        std::cout << "Tidak ada pesanan dalam stack." << std::endl;
    }
}

void LaundryGame::endDay() {
    // ...
}

void LaundryGame::display(const Order& order) {
    std::cout << "Nama Pelanggan: " << order.name << std::endl;
    std::cout << "Hari yang Tersisa: " << order.daysLeft << std::endl;
}

