#ifndef ORDER_MANAGEMENT_HPP
#define ORDER_MANAGEMENT_HPP

#include <iostream>
#include <string>
using namespace std;

// Maximum number of pending orders allowed in the queue
const int MAX_QUEUE = 10;

// Order status enum
enum OrderStatus {
    PENDING,
    PROCESSING,
    COMPLETED
};

// Order struct — used as a node in all three containers
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

// OrderQueue — pending orders (FIFO linked-list queue)
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

// ProcessingList — orders assigned to robots (linked list)
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

// CompletedList — orders fully delivered by robots (linked list)
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

// Global containers — shared across tasks
extern OrderQueue     pendingQueue;
extern ProcessingList processingList;
extern CompletedList  completedList;

// Function declarations
string statusLabel(OrderStatus s);
void   printMenu();

// Called by Task 2 completeRobotTask() when robot finishes delivery.
// Automatically moves order from processing -> completed.
void markOrderCompleted(int orderID);

#endif // ORDER_MANAGEMENT_HPP
