#ifndef WAREHOUSE_LAYOUT_HPP
#define WAREHOUSE_LAYOUT_HPP

#include <string>

using namespace std;

struct LocationNode
{
    string name; 
    string type; 

    LocationNode *firstChild;  
    LocationNode *nextSibling; 
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
