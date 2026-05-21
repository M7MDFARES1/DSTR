#include <iostream>
#include <string>
using namespace std;

// =============================================
// Task 4: Item Search and Management Module
// Data Structure: Binary Search Tree (BST)
// Ordered by Item ID
// =============================================

const int MAX_ITEMS = 100;

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
    ItemNode* insertHelper(ItemNode* node, int id, string name, string zone, string aisle, int shelf) {
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
            // Duplicate ID
            cout << "\nItem ID " << id << " already exists. Use update instead.\n";
        }
        return node;
    }

    // Helper: find the minimum node (used in delete)
    ItemNode* findMin(ItemNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Helper: delete recursively
    ItemNode* deleteHelper(ItemNode* node, int id, bool& found) {
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
            // Case 2: one child
            else if (node->left == nullptr) {
                ItemNode* temp = node->right;
                delete node;
                itemCount--;
                return temp;
            }
            else if (node->right == nullptr) {
                ItemNode* temp = node->left;
                delete node;
                itemCount--;
                return temp;
            }
            // Case 3: two children — replace with in-order successor
            else {
                ItemNode* successor   = findMin(node->right);
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
    void inOrderHelper(ItemNode* node, int& count) {
        if (node == nullptr) return;
        inOrderHelper(node->left, count);
        count++;
        cout << "  " << count << ". Item ID: " << node->itemID
             << "  |  Name: " << node->itemName
             << "  |  Location: Zone " << node->zone
             << ", Aisle " << node->aisle
             << ", Shelf " << node->shelf << "\n";
        inOrderHelper(node->right, count);
    }

    // Helper: search by name (traverses whole tree)
    void searchByNameHelper(ItemNode* node, string name, bool& found) {
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
    ItemNode* updateHelper(ItemNode* node, int id, bool& found) {
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

            cout << "\nEnter new item name    : ";
            cin.ignore();
            getline(cin, newName);
            cout << "Enter new zone         : ";
            getline(cin, newZone);
            cout << "Enter new aisle        : ";
            getline(cin, newAisle);
            cout << "Enter new shelf number : ";
            cin >> newShelf;

            node->itemName = newName;
            node->zone     = newZone;
            node->aisle    = newAisle;
            node->shelf    = newShelf;

            cout << "\nItem ID " << id << " updated successfully.\n";
        }
        return node;
    }

    // Helper: convert string to lowercase
    string toLowerCase(string input) {
        string result = "";
        for (int i = 0; i < (int)input.length(); i++) {
            char c = input[i];
            if (c >= 'A' && c <= 'Z') c = c + 32;
            result += c;
        }
        return result;
    }

    // Helper: delete all nodes (destructor)
    void destroyTree(ItemNode* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

    // Helper: print a single item
    void printItem(ItemNode* node) {
        cout << "  Item ID  : " << node->itemID   << "\n"
             << "  Name     : " << node->itemName << "\n"
             << "  Zone     : " << node->zone     << "\n"
             << "  Aisle    : " << node->aisle    << "\n"
             << "  Shelf    : " << node->shelf    << "\n";
    }

public:
    ItemBST() : root(nullptr), itemCount(0) {}

    ~ItemBST() {
        destroyTree(root);
    }

    bool isEmpty() { return root == nullptr; }
    int  getCount() { return itemCount; }

    // Insert a new item into the BST
    void insertItem(int id, string name, string zone, string aisle, int shelf) {
        root = insertHelper(root, id, name, zone, aisle, shelf);
    }

    // Search by Item ID (BST search — O log n)
    void searchByID(int id) {
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

    // Search by item name (full tree scan)
    void searchByName(string name) {
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
    void updateItem(int id) {
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
    void deleteItem(int id) {
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

    // Display all items sorted by ID (in-order)
    void displayAll() {
        if (isEmpty()) {
            cout << "\nNo items in the system.\n";
            return;
        }
        cout << "\nAll Items (sorted by ID) — Total: " << itemCount << "\n";
        int count = 0;
        inOrderHelper(root, count);
    }
};

// =============================================
// Menu
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
                cout << "\nEnter item ID     : ";
                cin >> itemID;
                cout << "Enter item name   : ";
                cin.ignore();
                getline(cin, itemName);
                cout << "Enter zone        : ";
                getline(cin, zone);
                cout << "Enter aisle       : ";
                getline(cin, aisle);
                cout << "Enter shelf number: ";
                cin >> shelf;

                itemTree.insertItem(itemID, itemName, zone, aisle, shelf);
                cout << "\nItem ID " << itemID << " added successfully.\n";
                cout << "Total items in system: " << itemTree.getCount() << "\n";
                break;

            case 2:
                // Search by ID
                cout << "\nEnter item ID to search: ";
                cin >> itemID;
                itemTree.searchByID(itemID);
                break;

            case 3:
                // Search by name
                cout << "\nEnter item name to search: ";
                cin.ignore();
                getline(cin, itemName);
                itemTree.searchByName(itemName);
                break;

            case 4:
                // Update item
                cout << "\nEnter item ID to update: ";
                cin >> itemID;
                itemTree.updateItem(itemID);
                break;

            case 5:
                // Delete item
                cout << "\nEnter item ID to delete: ";
                cin >> itemID;
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
