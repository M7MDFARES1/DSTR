#ifndef ITEM_SEARCH_MANAGEMENT_HPP
#define ITEM_SEARCH_MANAGEMENT_HPP

#include <iostream>
#include <string>
using namespace std;

// =============================================
// Task 4: Item Search and Management Module
// Data Structure: Binary Search Tree (BST)
// Ordered by Item ID
// =============================================

// Node struct for BST
// Each node stores one item and its warehouse location
struct ItemNode {
    int       itemID;
    string    itemName;
    string    zone;
    string    aisle;
    int       shelf;
    ItemNode* left;
    ItemNode* right;

    ItemNode(int id, string name, string z, string a, int s)
        : itemID(id), itemName(name), zone(z), aisle(a), shelf(s),
          left(nullptr), right(nullptr) {}
};

// =============================================
// Binary Search Tree class
// =============================================
class ItemBST {
private:
    ItemNode* root;
    int       itemCount;

    // Helper: insert recursively
    ItemNode* insertHelper(ItemNode* node, int id, string name, string zone, string aisle, int shelf);

    // Helper: find the minimum node (used in delete)
    ItemNode* findMin(ItemNode* node);

    // Helper: delete recursively
    ItemNode* deleteHelper(ItemNode* node, int id, bool& found);

    // Helper: in-order traversal (sorted by ID)
    void inOrderHelper(ItemNode* node, int& count);

    // Helper: search by name (traverses whole tree)
    void searchByNameHelper(ItemNode* node, string name, bool& found);

    // Helper: update node by ID
    ItemNode* updateHelper(ItemNode* node, int id, bool& found);

    // Helper: convert string to lowercase
    string toLowerCase(string input);

    // Helper: delete all nodes (destructor)
    void destroyTree(ItemNode* node);

    // Helper: print a single item
    void printItem(ItemNode* node);

public:
    // Constructor
    ItemBST();

    // Destructor
    ~ItemBST();

    // Check if tree is empty
    bool isEmpty();

    // Get total item count
    int getCount();

    // Insert a new item into the BST
    void insertItem(int id, string name, string zone, string aisle, int shelf);

    // Search by Item ID (BST search — O log n)
    void searchByID(int id);

    // Search by item name (full tree scan)
    void searchByName(string name);

    // Update item details by ID
    void updateItem(int id);

    // Delete item by ID
    void deleteItem(int id);

    // Display all items sorted by ID (in-order)
    void displayAll();
};

// Display the task menu
void showMenu();

#endif // ITEM_SEARCH_MANAGEMENT_HPP
