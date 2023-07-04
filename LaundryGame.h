#ifndef LAUNDRYGAME_H
#define LAUNDRYGAME_H

#include <string>
#include <stack>

class LaundryGame {
private:
    struct Order {
        std::string name;
        int daysLeft;
    };

    std::stack<Order> orderStack;

public:
    LaundryGame();
    void acceptOrder();
    void viewStack();
    void completeOrder();
    void endDay();
    void display(const Order& order);
};

#endif 
