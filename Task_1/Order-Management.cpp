#include <iostream>
#include <string>
using namespace std;
 
// Order status values
enum OrderStatus {
    PENDING,
    PROCESSING,
    COMPLETED
};
string statusLabel(OrderStatus s) {
    if (s == PENDING)    return "PENDING";
    if (s == PROCESSING) return "PROCESSING";
    return "COMPLETED";
}
 
// Order struct
// Used as a node in both the pending queue and processing list
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
 
// OrderQueue — pending orders (FIFO linked list)
const int MAX_QUEUE = 10;
class OrderQueue {
private:
    Order* front;
    Order* rear;
    int    size;
    int    nextID;
public:
    OrderQueue() : front(nullptr), rear(nullptr), size(0), nextID(1) {}
    ~OrderQueue() {
        while (front != nullptr) {
            Order* temp = front;
            front = front->next;
            delete temp;
        }
    }
    bool isEmpty() { return front == nullptr; }
    int  getSize() { return size; }

    // Add a new order to the back of the queue (status: PENDING)
    void enqueue(string customerName, string itemName) {
        if (size >= MAX_QUEUE) {
            cout << "\nSystem overload. Queue is full (" << MAX_QUEUE << "/" << MAX_QUEUE << " orders)."
                 << "\n  Order for " << customerName << " could not be accepted."
                 << "\n  Please wait until current orders are processed.\n";
            return;
        }
        Order* newOrder = new Order(nextID++, customerName, itemName);
        if (isEmpty()) {
            front = newOrder;
            rear  = newOrder;
        } else {
            rear->next = newOrder;
            rear       = newOrder;
        }
        size++;
        cout << "\nOrder #" << newOrder->orderID << " received."
             << "\n  Customer : " << customerName
             << "\n  Item     : " << itemName
             << "\n  Status   : " << statusLabel(newOrder->status) << "\n";
    }
 
    // Remove front order and return it — caller owns the pointer
    // Status becomes PROCESSING as it leaves the queue
    Order* dequeue() {
        if (isEmpty()) return nullptr;
        Order* order  = front;
        front         = front->next;
        if (front == nullptr) rear = nullptr;
        order->next   = nullptr;
        order->status = PROCESSING;
        size--;
        return order;
    }
 
    void displayPending() {
        if (isEmpty()) {
            cout << "\nNo pending orders in the queue.\n";
            return;
        }
        cout << "\nPending orders (" << size << "):\n";
        Order* current  = front;
        int    position = 1;
        while (current != nullptr) {
            cout << "  " << position++ << ". Order #" << current->orderID
                 << "  |  " << current->customerName
                 << "  |  " << current->itemName
                 << "  |  Status: " << statusLabel(current->status) << "\n";
            current = current->next;
        }
    }
};
 
// ProcessingList — orders assigned to robots, waiting for delivery
class ProcessingList {
private:
    Order* head;
    int    size;
 
public:
    ProcessingList() : head(nullptr), size(0) {}
    ~ProcessingList() {
        Order* current = head;
        while (current != nullptr) {
            Order* temp = current;
            current = current->next;
            delete temp;
        }
    }
    bool isEmpty() { return head == nullptr; }
    int  getSize() { return size; }

    // Add an order that just left the pending queue
    void add(Order* order) {
        order->next = head;
        head        = order;
        size++;
    }
    // Task 3 calls this when the robot finishes delivery
    // Finds the order by ID, marks it COMPLETED, removes it from list
    Order* markCompleted(int orderID) {
        Order* current  = head;
        Order* previous = nullptr;
        while (current != nullptr) {
            if (current->orderID == orderID) {
                if (previous == nullptr)
                    head = current->next;
                else
                    previous->next = current->next;
                current->next   = nullptr;
                current->status = COMPLETED;
                size--;
                return current;   // Task 3 owns this pointer
            }
            previous = current;
            current  = current->next;
        }
        return nullptr;   // order ID not found
    }
 
    void displayProcessing() {
        if (isEmpty()) {
            cout << "\nNo orders are currently being processed.\n";
            return;
        }
        cout << "\nProcessing orders (" << size << "):\n";
        Order* current  = head;
        int    position = 1;
        while (current != nullptr) {
            cout << "  " << position++ << ". Order #" << current->orderID
                 << "  |  " << current->customerName
                 << "  |  " << current->itemName
                 << "  |  Status: " << statusLabel(current->status) << "\n";
            current = current->next;
        }
    }
};
 
// CompletedList — orders fully delivered by robots
class CompletedList {
private:
    Order* head;
    int    size;
public:
    CompletedList() : head(nullptr), size(0) {}
    ~CompletedList() {
        Order* current = head;
        while (current != nullptr) {
            Order* temp = current;
            current = current->next;
            delete temp;
        }
    }
    bool isEmpty() { return head == nullptr; }
    int  getSize() { return size; }
    void add(Order* order) {
        order->next = head;
        head        = order;
        size++;
    }
    void displayCompleted() {
        if (isEmpty()) {
            cout << "\nNo completed orders yet.\n";
            return;
        }
        cout << "\nCompleted orders (" << size << "):\n";
        Order* current  = head;
        int    position = 1;
        while (current != nullptr) {
            cout << "  " << position++ << ". Order #" << current->orderID
                 << "  |  " << current->customerName
                 << "  |  " << current->itemName
                 << "  |  Status: " << statusLabel(current->status) << "\n";
            current = current->next;
        }
    }
};
 
// Menu
void printMenu() {
    cout << "\nOrder Management Module"
         << "\n  1. Add new order"
         << "\n  2. Assign next order to robot (PENDING -> PROCESSING)"
         << "\n  3. Display pending orders"
         << "\n  4. Display processing orders"
         << "\n  5. Display completed orders"
         << "\n  0. Exit"
         << "\nEnter choice: ";
}

 // Main
int main() {
    OrderQueue     pendingQueue;
    ProcessingList processingList;
    CompletedList  completedList;
    int    choice;
    string cName, iName;
    cout << "Warehouse Robot Navigation System\n";
    cout << "Task 1: Order Management Module\n";
    cout << "\nSystem ready. Pending orders: " << pendingQueue.getSize() << "\n";
 
    do {
        printMenu();
        cin >> choice;
        cin.ignore();
 
        switch (choice) {
 
            case 1:
                // Accept a new order from user input
                cout << "Enter customer name: ";
                getline(cin, cName);
                cout << "Enter item name   : ";
                getline(cin, iName);
                pendingQueue.enqueue(cName, iName);
                break;
 
            case 2: {
                // Move front order from PENDING queue -> PROCESSING list
                // Robot is now assigned — Task 2 will pick it up from here
                if (pendingQueue.isEmpty()) {
                    cout << "\nNo orders to process. Queue is empty.\n";
                    break;
                }
                Order* order = pendingQueue.dequeue();   // status -> PROCESSING
 
                cout << "\nOrder #" << order->orderID << " assigned to robot."
                     << "\n  Customer : " << order->customerName
                     << "\n  Item     : " << order->itemName
                     << "\n  Status   : " << statusLabel(order->status)
                     << "\n  Waiting for robot delivery.\n";
 
                processingList.add(order);
                break;
            }
 
            case 3:
                pendingQueue.displayPending();
                break;
 
            case 4:
                processingList.displayProcessing();
                break;
 
            case 5:
                // Completed orders are added here by Task 3
                // when the robot finishes delivery
                completedList.displayCompleted();
                break;
 
            case 0:
                cout << "\nShutting down Order Management Module.\n";
                cout << "  Pending    : " << pendingQueue.getSize()   << "\n";
                cout << "  Processing : " << processingList.getSize() << "\n";
                cout << "  Completed  : " << completedList.getSize()  << "\n";
                break;
 
            default:
                cout << "\nInvalid choice. Please enter a number from the menu.\n";
        }
 
    } while (choice != 0);
 
    return 0;
}