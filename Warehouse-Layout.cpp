#include <iostream>
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
    WarehouseLayout()
    {
        root = createNode("Warehouse", "Root");
        buildDefaultLayout();
    }

    // Creates one new location node
    LocationNode *createNode(string name, string type)
    {
        LocationNode *newNode = new LocationNode;

        newNode->name = name;
        newNode->type = type;
        newNode->firstChild = NULL;
        newNode->nextSibling = NULL;

        return newNode;
    }

    // Adds a child node under a parent node
    void addChild(LocationNode *parent, LocationNode *child)
    {
        if (parent == NULL || child == NULL)
        {
            return;
        }

        // If parent has no child, this child becomes the first child
        if (parent->firstChild == NULL)
        {
            parent->firstChild = child;
        }
        else
        {
            // Otherwise, go to the last sibling and attach the child there
            LocationNode *current = parent->firstChild;

            while (current->nextSibling != NULL)
            {
                current = current->nextSibling;
            }

            current->nextSibling = child;
        }
    }

    // Builds the warehouse structure used by the system
    void buildDefaultLayout()
    {
        // Main locations under Warehouse
        LocationNode *packingStation = createNode("Packing Station", "Station");

        LocationNode *zoneA = createNode("Zone A", "Zone");
        LocationNode *zoneB = createNode("Zone B", "Zone");
        LocationNode *zoneC = createNode("Zone C", "Zone");

        addChild(root, packingStation);
        addChild(root, zoneA);
        addChild(root, zoneB);
        addChild(root, zoneC);

        // Build Zone A
        buildZone(zoneA, "A");

        // Build Zone B
        buildZone(zoneB, "B");

        // Build Zone C
        buildZone(zoneC, "C");
    }

    // Builds 3 aisles and 3 shelves for one zone
    void buildZone(LocationNode *zoneNode, string zoneLetter)
    {
        for (int aisleNumber = 1; aisleNumber <= 3; aisleNumber++)
        {
            string aisleName = "Aisle " + zoneLetter + to_string(aisleNumber);
            LocationNode *aisleNode = createNode(aisleName, "Aisle");

            addChild(zoneNode, aisleNode);

            for (int shelfNumber = 1; shelfNumber <= 3; shelfNumber++)
            {
                string shelfName = "Shelf " + to_string(shelfNumber);
                LocationNode *shelfNode = createNode(shelfName, "Shelf");

                addChild(aisleNode, shelfNode);
            }
        }
    }

    // Displays the full warehouse layout in tree format
    void displayLayout(LocationNode *current, int level)
    {
        if (current == NULL)
        {
            return;
        }

        // Print spaces based on tree level
        for (int i = 0; i < level; i++)
        {
            cout << "  ";
        }

        cout << current->name << " (" << current->type << ")" << endl;

        // Go down to child
        displayLayout(current->firstChild, level + 1);

        // Go to sibling at same level
        displayLayout(current->nextSibling, level);
    }

    void showWarehouseLayout()
    {
        cout << "\n========== Warehouse Layout ==========\n";
        displayLayout(root, 0);
    }

    // Finds a direct child by name under a parent
    LocationNode *findChild(LocationNode *parent, string childName)
    {
        if (parent == NULL)
        {
            return NULL;
        }

        LocationNode *current = parent->firstChild;

        while (current != NULL)
        {
            if (current->name == childName)
            {
                return current;
            }

            current = current->nextSibling;
        }

        return NULL;
    }

    // Checks whether Zone -> Aisle -> Shelf exists
    bool searchLocation(string zoneLetter, string aisleCode, int shelfNumber)
    {
        string zoneName = "Zone " + zoneLetter;
        string aisleName = "Aisle " + aisleCode;
        string shelfName = "Shelf " + to_string(shelfNumber);

        LocationNode *zoneNode = findChild(root, zoneName);

        if (zoneNode == NULL)
        {
            cout << "\nInvalid location: " << zoneName << " does not exist.\n";
            return false;
        }

        LocationNode *aisleNode = findChild(zoneNode, aisleName);

        if (aisleNode == NULL)
        {
            cout << "\nInvalid location: " << aisleName << " does not belong to " << zoneName << ".\n";
            return false;
        }

        LocationNode *shelfNode = findChild(aisleNode, shelfName);

        if (shelfNode == NULL)
        {
            cout << "\nInvalid location: " << shelfName << " does not exist in " << aisleName << ".\n";
            return false;
        }

        cout << "\nLocation found: "
             << zoneName << " -> "
             << aisleName << " -> "
             << shelfName << endl;

        return true;
    }

    // Generates route from Packing Station to selected shelf
    void generateRoute(string zoneLetter, string aisleCode, int shelfNumber)
    {
        bool found = searchLocation(zoneLetter, aisleCode, shelfNumber);

        if (found)
        {
            cout << "\nGenerated Robot Route:\n";
            cout << "Packing Station -> Zone " << zoneLetter
                 << " -> Aisle " << aisleCode
                 << " -> Shelf " << shelfNumber << endl;
        }
        else
        {
            cout << "\nRoute cannot be generated because the location is invalid.\n";
        }
    }

    // Traverses the whole tree using preorder traversal
    void traverseLayout(LocationNode *current)
    {
        if (current == NULL)
        {
            return;
        }

        cout << current->name << " (" << current->type << ")" << endl;

        traverseLayout(current->firstChild);
        traverseLayout(current->nextSibling);
    }

    void showTraversal()
    {
        cout << "\n========== Warehouse Traversal ==========\n";
        traverseLayout(root);
    }

    // Menu for Task 5
    void task5Menu()
    {
        int choice;
        string zone;
        string aisle;
        int shelf;

        do
        {
            cout << "\n========================================\n";
            cout << " Task 5: Warehouse Layout and Navigation\n";
            cout << "========================================\n";
            cout << "1. Display full warehouse layout\n";
            cout << "2. Search for location\n";
            cout << "3. Generate route to shelf\n";
            cout << "4. Traverse warehouse layout\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                showWarehouseLayout();
                break;

            case 2:
                cout << "\nEnter Zone Letter (A/B/C): ";
                cin >> zone;

                cout << "Enter Aisle Code (Example: A1, B2, C3): ";
                cin >> aisle;

                cout << "Enter Shelf Number (1-3): ";
                cin >> shelf;

                searchLocation(zone, aisle, shelf);
                break;

            case 3:
                cout << "\nEnter Zone Letter (A/B/C): ";
                cin >> zone;

                cout << "Enter Aisle Code (Example: A1, B2, C3): ";
                cin >> aisle;

                cout << "Enter Shelf Number (1-3): ";
                cin >> shelf;

                generateRoute(zone, aisle, shelf);
                break;

            case 4:
                showTraversal();
                break;

            case 0:
                cout << "\nExiting Task 5 module...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
            }

        } while (choice != 0);
    }
};

// Temporary main function for testing Task 5 alone.
// Later, when combining with your group, remove this main()
// and call layout.task5Menu() from the group's main menu.
int main()
{
    WarehouseLayout layout;
    layout.task5Menu();

    return 0;
}