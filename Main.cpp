#include <iostream>
#include <limits>

using namespace std;

namespace task1 {
#define main task1Main
#include "Order-Management.cpp"
#undef main
}

#undef ORDER_MANAGEMENT_HPP
#undef ROBOT_ASSIGNMENT_HPP

namespace task2 {
#define main task2Main
#include "Robot-Assignment.cpp"
#undef main
}

#undef ROBOT_ASSIGNMENT_HPP

namespace task3 {
#define main task3Main
#include "Robot-Navigation.cpp"
#undef main
}

#undef TASK3_ROBOT_NAVIGATION_HPP

namespace task4 {
#define main task4Main
#include "Item-Search-Management.cpp"
#undef main
}

#undef ITEM_SEARCH_MANAGEMENT_HPP

namespace task5 {
#define main task5Main
#include "Warehouse-Layout.cpp"
#undef main
}

#undef WAREHOUSE_LAYOUT_HPP

void showMainMenu() {
    cout << "\n=====================================\n";
    cout << "Warehouse Robot Navigation System\n";
    cout << "=====================================\n";
    cout << "1. Order Management\n";
    cout << "2. Robot Assignment\n";
    cout << "3. Robot Navigation and Path Tracking\n";
    cout << "4. Item Search and Management\n";
    cout << "5. Warehouse Layout and Navigation\n";
    cout << "0. Exit System\n";
    cout << "Enter choice: ";
}

int main() {
    int choice;

    do {
        showMainMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                task1::task1Main();
                break;

            case 2:
                task2::task2Main();
                break;

            case 3:
                task3::task3Main();
                break;

            case 4:
                task4::task4Main();
                break;

            case 5:
                task5::task5Main();
                break;

            case 0:
                cout << "\nExiting Warehouse Robot Navigation System.\n";
                break;

            default:
                cout << "\nInvalid choice. Please enter a number from the menu.\n";
        }

    } while (choice != 0);

    return 0;
}
