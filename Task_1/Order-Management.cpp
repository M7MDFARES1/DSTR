#include "Order-Management.hpp"
#include "Robot-Assignment.hpp"


// Global containers — accessed by Task 2 integration
OrderQueue     pendingQueue;
ProcessingList processingList;
CompletedList  completedList;

// Helper 
string statusLabel(OrderStatus s) {
    if (s == PENDING)    return "PENDING";
    if (s == PROCESSING) return "PROCESSING";
    return "COMPLETED";
}

// OrderQueue 
OrderQueue::OrderQueue() : front(nullptr), rear(nullptr), size(0), nextID(1) {}

OrderQueue::~OrderQueue() {
    while (front != nullptr) {
        Order* temp = front;
        front = front->next;
        delete temp;
    }
}

bool OrderQueue::isEmpty() { return front == nullptr; }
int  OrderQueue::getSize() { return size; }

void OrderQueue::enqueue(string customerName, string itemName) {
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

Order* OrderQueue::dequeue() {
    if (isEmpty()) return nullptr;
    Order* order  = front;
    front         = front->next;
    if (front == nullptr) rear = nullptr;
    order->next   = nullptr;
    order->status = PROCESSING;
    size--;
    return order;
}

void OrderQueue::displayPending() {
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

// ProcessingList 
ProcessingList::ProcessingList() : head(nullptr), size(0) {}

ProcessingList::~ProcessingList() {
    Order* current = head;
    while (current != nullptr) {
        Order* temp = current;
        current = current->next;
        delete temp;
    }
}

bool ProcessingList::isEmpty() { return head == nullptr; }
int  ProcessingList::getSize() { return size; }

void ProcessingList::add(Order* order) {
    order->next = head;
    head        = order;
    size++;
}

Order* ProcessingList::markCompleted(int orderID) {
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
            return current;
        }
        previous = current;
        current  = current->next;
    }
    return nullptr;
}

void ProcessingList::displayProcessing() {
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

//  CompletedList 
CompletedList::CompletedList() : head(nullptr), size(0) {}

CompletedList::~CompletedList() {
    Order* current = head;
    while (current != nullptr) {
        Order* temp = current;
        current = current->next;
        delete temp;
    }
}

bool CompletedList::isEmpty() { return head == nullptr; }
int  CompletedList::getSize() { return size; }

void CompletedList::add(Order* order) {
    order->next = head;
    head        = order;
    size++;
}

void CompletedList::displayCompleted() {
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

//  Called by Task 2 completeRobotTask() 
void markOrderCompleted(int orderID) {
    Order* delivered = processingList.markCompleted(orderID);
    if (delivered == nullptr) {
        cout << "\n[Task 1] Order #" << orderID << " not found in processing list.\n";
    } else {
        completedList.add(delivered);
        cout << "\n[Task 1] Order #" << delivered->orderID << " automatically marked as COMPLETED."
             << "\n  Customer : " << delivered->customerName
             << "\n  Item     : " << delivered->itemName
             << "\n  Status   : " << statusLabel(delivered->status) << "\n";
    }
}

//  Menu 
void printMenu() {
    cout << "\nOrder Management Module"
         << "\n  1. Add new order"
         << "\n  2. Assign next order to robot  (PENDING -> PROCESSING)"
         << "\n  3. Display pending orders"
         << "\n  4. Display processing orders"
         << "\n  5. Display completed orders"
         << "\n  0. Exit"
         << "\nEnter choice: ";
}

//  Main 
int main() {
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
                cout << "Enter customer name: ";
                getline(cin, cName);
                cout << "Enter item name   : ";
                getline(cin, iName);
                pendingQueue.enqueue(cName, iName);
                break;

            case 2: {
                if (pendingQueue.isEmpty()) {
                    cout << "\nNo orders to process. Queue is empty.\n";
                    break;
                }
                Order* order = pendingQueue.dequeue();
                cout << "\nOrder #" << order->orderID << " assigned to robot."
                     << "\n  Customer : " << order->customerName
                     << "\n  Item     : " << order->itemName
                     << "\n  Status   : " << statusLabel(order->status)
                     << "\n  Use Order #" << order->orderID << " as Task ID in Task 2.\n";
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
