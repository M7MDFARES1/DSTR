#ifndef WAREHOUSE_LAYOUT_HPP
#define WAREHOUSE_LAYOUT_HPP

#include <string>

using namespace std;

struct LocationNode
{
    string name; // Example: "Zone A", "Aisle A1", "Shelf 1"
    string type; // Example: "Root", "Zone", "Aisle", "Shelf"

    LocationNode *firstChild;  // First child inside this location
    LocationNode *nextSibling; // Next location beside this location
};

class WarehouseLayout
{
private:
    LocationNode *root;

public:
    WarehouseLayout();

    LocationNode *createNode(string name, string type);
    void addChild(LocationNode *parent, LocationNode *child);
    void buildDefaultLayout();
    void buildZone(LocationNode *zoneNode, string zoneLetter);
    void displayLayout(LocationNode *current, int level);
    void showWarehouseLayout();
    LocationNode *findChild(LocationNode *parent, string childName);
    bool searchLocation(string zoneLetter, string aisleCode, int shelfNumber);
    void generateRoute(string zoneLetter, string aisleCode, int shelfNumber);
    void traverseLayout(LocationNode *current);
    void showTraversal();
    void task5Menu();
};

#endif
