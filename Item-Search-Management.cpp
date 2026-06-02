#include "Item-Search-Management.hpp"

#include <limits>

// =============================================
// Task 4: Item Search and Management Module
// Data Structure: Binary Search Tree (BST)
// Ordered by Item ID
// =============================================

bool isCancelChoice(int value) {
    if (value == 0) {
        cout << "\nCancelled. Returning to Item Search menu.\n";
        return true;
    }

    return false;
}

bool isCancelChoice(string value) {
    if (value == "0") {
        cout << "\nCancelled. Returning to Item Search menu.\n";
        return true;
    }

    return false;
}

// =============================================
// ItemBST — Private Helper Implementations
// =============================================

// Helper: insert recursively
ItemNode* ItemBST::insertHelper(ItemNode* node, int id, string name, string zone, string aisle, int shelf) {
    if (node == nullptr) {
        itemCount++;
        return new ItemNode(id, name, zone, aisle, shelf);
    }
    if (id < node->itemID) {
        node->left = insertHelper(node->left, id, name, zone, aisle, shelf);
    }
    else if (id > node->itemID) {
        node->right = insertHelper(node->right, id, name, zone, aisle, shelf);
    }
    else {
        // Duplicate ID — not allowed
        cout << "\nItem ID " << id << " already exists. Use update instead.\n";
    }
    return node;
}

// Helper: find the minimum node (used in delete)
ItemNode* ItemBST::findMin(ItemNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Helper: delete recursively
ItemNode* ItemBST::deleteHelper(ItemNode* node, int id, bool& found) {
    if (node == nullptr) {
        return nullptr;
    }
    if (id < node->itemID) {
        node->left = deleteHelper(node->left, id, found);
    }
    else if (id > node->itemID) {
        node->right = deleteHelper(node->right, id, found);
    }
    else {
        found = true;

        // Case 1: no children
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            itemCount--;
            return nullptr;
        }
        // Case 2: only right child
        else if (node->left == nullptr) {
            ItemNode* temp = node->right;
            delete node;
            itemCount--;
            return temp;
        }
        // Case 2: only left child
        else if (node->right == nullptr) {
            ItemNode* temp = node->left;
            delete node;
            itemCount--;
            return temp;
        }
        // Case 3: two children — replace with in-order successor
        else {
            ItemNode* successor = findMin(node->right);
            node->itemID   = successor->itemID;
            node->itemName = successor->itemName;
            node->zone     = successor->zone;
            node->aisle    = successor->aisle;
            node->shelf    = successor->shelf;
            bool dummy = false;
            node->right = deleteHelper(node->right, successor->itemID, dummy);
        }
    }
    return node;
}

// Helper: in-order traversal (sorted by ID)
void ItemBST::inOrderHelper(ItemNode* node, int& count) {
    if (node == nullptr) return;
    inOrderHelper(node->left, count);
    count++;
    cout << "  " << count << ". Item ID: " << node->itemID
         << "  |  Name: "     << node->itemName
         << "  |  Location: Zone " << node->zone
         << ", Aisle "        << node->aisle
         << ", Shelf "        << node->shelf << "\n";
    inOrderHelper(node->right, count);
}

// Helper: search by name (traverses whole tree)
void ItemBST::searchByNameHelper(ItemNode* node, string name, bool& found) {
    if (node == nullptr) return;
    searchByNameHelper(node->left, name, found);

    // Case-insensitive compare
    string nodeName  = toLowerCase(node->itemName);
    string searchKey = toLowerCase(name);

    if (nodeName == searchKey) {
        found = true;
        cout << "\n  Item found!\n";
        printItem(node);
    }
    searchByNameHelper(node->right, name, found);
}

// Helper: update node by ID
ItemNode* ItemBST::updateHelper(ItemNode* node, int id, bool& found) {
    if (node == nullptr) return nullptr;
    if (id < node->itemID) {
        updateHelper(node->left, id, found);
    }
    else if (id > node->itemID) {
        updateHelper(node->right, id, found);
    }
    else {
        found = true;
        string newName, newZone, newAisle;
        int    newShelf;

        cout << "\nCurrent details:\n";
        printItem(node);

        cout << "\nEnter new item name (0 to cancel)    : ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, newName);
        if (isCancelChoice(newName)) {
            return node;
        }

        cout << "Enter new zone (0 to cancel)         : ";
        getline(cin, newZone);
        if (isCancelChoice(newZone)) {
            return node;
        }

        cout << "Enter new aisle (0 to cancel)        : ";
        getline(cin, newAisle);
        if (isCancelChoice(newAisle)) {
            return node;
        }

        cout << "Enter new shelf number (0 to cancel) : ";
        cin >> newShelf;
        if (isCancelChoice(newShelf)) {
            return node;
        }

        node->itemName = newName;
        node->zone     = newZone;
        node->aisle    = newAisle;
        node->shelf    = newShelf;

        cout << "\nItem ID " << id << " updated successfully.\n";
    }
    return node;
}

// Helper: convert string to lowercase
string ItemBST::toLowerCase(string input) {
    string result = "";
    for (int i = 0; i < (int)input.length(); i++) {
        char c = input[i];
        if (c >= 'A' && c <= 'Z') c = c + 32;
        result += c;
    }
    return result;
}

// Helper: delete all nodes (destructor helper)
void ItemBST::destroyTree(ItemNode* node) {
    if (node == nullptr) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// Helper: print a single item's details
void ItemBST::printItem(ItemNode* node) {
    cout << "  Item ID  : " << node->itemID   << "\n"
         << "  Name     : " << node->itemName << "\n"
         << "  Zone     : " << node->zone     << "\n"
         << "  Aisle    : " << node->aisle    << "\n"
         << "  Shelf    : " << node->shelf    << "\n";
}

// =============================================
// ItemBST — Public Method Implementations
// =============================================

// Constructor
ItemBST::ItemBST() : root(nullptr), itemCount(0) {}

// Destructor
ItemBST::~ItemBST() {
    destroyTree(root);
}

// Check if the BST is empty
bool ItemBST::isEmpty() {
    return root == nullptr;
}

// Get current item count
int ItemBST::getCount() {
    return itemCount;
}

// Insert a new item into the BST
void ItemBST::insertItem(int id, string name, string zone, string aisle, int shelf) {
    root = insertHelper(root, id, name, zone, aisle, shelf);
}

// Search by Item ID — O(log n) BST traversal
void ItemBST::searchByID(int id) {
    if (isEmpty()) {
        cout << "\nNo items in the system.\n";
        return;
    }
    ItemNode* current = root;
    while (current != nullptr) {
        if (id == current->itemID) {
            cout << "\n  Item found!\n";
            printItem(current);
            return;
        }
        else if (id < current->itemID) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    cout << "\nItem ID " << id << " not found.\n";
}

// Search by item name — full tree scan
void ItemBST::searchByName(string name) {
    if (isEmpty()) {
        cout << "\nNo items in the system.\n";
        return;
    }
    bool found = false;
    searchByNameHelper(root, name, found);
    if (!found) {
        cout << "\nNo item with name \"" << name << "\" found.\n";
    }
}

// Update item details by ID
void ItemBST::updateItem(int id) {
    if (isEmpty()) {
        cout << "\nNo items in the system.\n";
        return;
    }
    bool found = false;
    updateHelper(root, id, found);
    if (!found) {
        cout << "\nItem ID " << id << " not found.\n";
    }
}

// Delete item by ID
void ItemBST::deleteItem(int id) {
    if (isEmpty()) {
        cout << "\nNo items in the system.\n";
        return;
    }
    bool found = false;
    root = deleteHelper(root, id, found);
    if (found) {
        cout << "\nItem ID " << id << " deleted successfully.\n";
    }
    else {
        cout << "\nItem ID " << id << " not found.\n";
    }
}

// Display all items sorted by ID using in-order traversal
void ItemBST::displayAll() {
    if (isEmpty()) {
        cout << "\nNo items in the system.\n";
        return;
    }
    cout << "\nAll Items (sorted by ID) — Total: " << itemCount << "\n";
    int count = 0;
    inOrderHelper(root, count);
}

// =============================================
// Menu display function
// =============================================
void showMenu() {
    cout << "\n=====================================\n";
    cout << "Task 4: Item Search and Management\n";
    cout << "=====================================\n";
    cout << "1. Add new item\n";
    cout << "2. Search item by ID\n";
    cout << "3. Search item by name\n";
    cout << "4. Update item details\n";
    cout << "5. Delete item\n";
    cout << "6. Display all items\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

// =============================================
// Main
// =============================================
int main() {
    ItemBST itemTree;
    int     choice;
    int     itemID, shelf;
    string  itemName, zone, aisle;

    cout << "Warehouse Robot Navigation System\n";
    cout << "Task 4: Item Search and Management Module\n";
    cout << "\nData Structure: Binary Search Tree (BST)\n";
    cout << "Items are ordered by Item ID for fast lookup.\n";

    do {
        showMenu();
        cin >> choice;

        switch (choice) {

            case 1:
                // Add new item
                cout << "\nEnter item ID (0 to cancel)     : ";
                cin >> itemID;
                if (isCancelChoice(itemID)) {
                    break;
                }

                cout << "Enter item name (0 to cancel)   : ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, itemName);
                if (isCancelChoice(itemName)) {
                    break;
                }

                cout << "Enter zone (0 to cancel)        : ";
                getline(cin, zone);
                if (isCancelChoice(zone)) {
                    break;
                }

                cout << "Enter aisle (0 to cancel)       : ";
                getline(cin, aisle);
                if (isCancelChoice(aisle)) {
                    break;
                }

                cout << "Enter shelf number (0 to cancel): ";
                cin >> shelf;
                if (isCancelChoice(shelf)) {
                    break;
                }

                itemTree.insertItem(itemID, itemName, zone, aisle, shelf);
                cout << "\nItem ID " << itemID << " added successfully.\n";
                cout << "Total items in system: " << itemTree.getCount() << "\n";
                break;

            case 2:
                // Search by ID
                cout << "\nEnter item ID to search (0 to cancel): ";
                cin >> itemID;
                if (isCancelChoice(itemID)) {
                    break;
                }
                itemTree.searchByID(itemID);
                break;

            case 3:
                // Search by name
                cout << "\nEnter item name to search (0 to cancel): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, itemName);
                if (isCancelChoice(itemName)) {
                    break;
                }
                itemTree.searchByName(itemName);
                break;

            case 4:
                // Update item
                cout << "\nEnter item ID to update (0 to cancel): ";
                cin >> itemID;
                if (isCancelChoice(itemID)) {
                    break;
                }
                itemTree.updateItem(itemID);
                break;

            case 5:
                // Delete item
                cout << "\nEnter item ID to delete (0 to cancel): ";
                cin >> itemID;
                if (isCancelChoice(itemID)) {
                    break;
                }
                itemTree.deleteItem(itemID);
                cout << "Total items in system: " << itemTree.getCount() << "\n";
                break;

            case 6:
                // Display all items sorted
                itemTree.displayAll();
                break;

            case 0:
                cout << "\nExiting Item Search and Management Module.\n";
                cout << "Total items remaining: " << itemTree.getCount() << "\n";
                break;

            default:
                cout << "\nInvalid choice. Please enter a number from the menu.\n";
        }

    } while (choice != 0);

    return 0;
}
