#ifndef ORDER_MANAGEMENT_HPP
#define ORDER_MANAGEMENT_HPP

#include <iostream>
#include <string>
using namespace std;

// Task 1: Order Management Module

const int MAX_QUEUE = 10;

enum OrderStatus {
    PENDING,
    PROCESSING,
    COMPLETED
};

struct Order {
    int         orderID;
    string      customerName;
    string      itemName;
    OrderStatus status;
    Order*      next;

    Order(int id, string cName, string iName)
        : orderID(id), customerName(cName),
          itemName(iName), status(PENDING), next(nullptr) {}
};

class OrderQueue {
private:
    Order* front;
    Order* rear;
    int    size;
    int    nextID;

public:
    OrderQueue();
    ~OrderQueue();
    bool   isEmpty();
    int    getSize();
    void   enqueue(string customerName, string itemName);
    Order* dequeue();
    void   displayPending();
};

class ProcessingList {
private:
    Order* head;
    int    size;

public:
    ProcessingList();
    ~ProcessingList();
    bool   isEmpty();
    int    getSize();
    void   add(Order* order);
    Order* markCompleted(int orderID);
    void   displayProcessing();
};

class CompletedList {
private:
    Order* head;
    int    size;

public:
    CompletedList();
    ~CompletedList();
    bool isEmpty();
    int  getSize();
    void add(Order* order);
    void displayCompleted();
};

extern OrderQueue     pendingQueue;
extern ProcessingList processingList;
extern CompletedList  completedList;

string statusLabel(OrderStatus s);
void   printMenu();
void   markOrderCompleted(int orderID);

#endif
