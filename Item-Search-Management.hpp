#ifndef ITEM_SEARCH_MANAGEMENT_HPP
#define ITEM_SEARCH_MANAGEMENT_HPP

#include <iostream>
#include <string>
using namespace std;

// Task 4: Item Search and Management Module

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

class ItemBST {
private:
    ItemNode* root;
    int       itemCount;

    ItemNode* insertHelper(ItemNode* node, int id, string name, string zone, string aisle, int shelf);
    ItemNode* findMin(ItemNode* node);
    ItemNode* deleteHelper(ItemNode* node, int id, bool& found);
    void inOrderHelper(ItemNode* node, int& count);
    void searchByNameHelper(ItemNode* node, string name, bool& found);
    ItemNode* updateHelper(ItemNode* node, int id, bool& found);
    string toLowerCase(string input);
    void destroyTree(ItemNode* node);
    void printItem(ItemNode* node);

public:
    ItemBST();
    ~ItemBST();

    bool isEmpty();
    int getCount();

    void insertItem(int id, string name, string zone, string aisle, int shelf);
    void searchByID(int id);
    void searchByName(string name);
    void updateItem(int id);
    void deleteItem(int id);
    void displayAll();
};

void showMenu();

#endif
