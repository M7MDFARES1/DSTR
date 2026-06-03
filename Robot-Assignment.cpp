#ifndef ORDER_MANAGEMENT_HPP
#define ORDER_MANAGEMENT_HPP

#include <iostream>
#include <string>
using namespace std;

// Task 1: Order Management Module

const int MAX_QUEUE = 10;

// Order Status
enum OrderStatus {
    PENDING,
    PROCESSING,
    COMPLETED
};

// Order Node
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

// Pending Orders Queue (FIFO)
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

// Processing Orders List
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

// Completed Orders List
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

// Shared Order Containers
extern OrderQueue     pendingQueue;
extern ProcessingList processingList;
extern CompletedList  completedList;

// Function Declarations
string statusLabel(OrderStatus s);
void   printMenu();
void   markOrderCompleted(int orderID);

#endif
