#include <iostream>
#include <string>
using namespace std;

// Maximum number of robots and assignment records
const int MAX_ROBOTS = 10;
const int MAX_ASSIGNMENTS = 50;

// Robot status enum enumeration is to name vlaues to use later for choice
enum RobotStatus {
    AVAILABLE,
    BUSY,
    MAINTENANCE
};

// Robot struct
struct Robot {
    int robotID;
    string robotName;
    RobotStatus status;
    int currentTaskID;
    int totalTasksAssigned;
};

// Assignment struct
struct Assignment {
    int taskID;
    int robotID;
    string robotName;
};

// Circular queue array for robots and assignment history array
Robot robotQueue[MAX_ROBOTS];

Assignment assignments[MAX_ASSIGNMENTS];

// Queue variables
int queueFront = -1;
int queueRear  = -1;
int robotCount = 0;
// Assignment counter
int assignmentCount = 0;
//this is used for robot assignment rotation, which robot should get/check the nect task 
int currentRobotIndex = 0;


// Convert robot status to text
string getStatusText(RobotStatus status) {
    if (status == AVAILABLE) {
        return "AVAILABLE";
    }

    else if (status == BUSY) {
        return "BUSY";
    }

    else {
        return "MAINTENANCE";
    }
}


// Check if robot circular queue is empty
bool isEmpty() {
    return robotCount == 0;
}


// Check if robot circular queue is full
bool isFull() {
    return robotCount == MAX_ROBOTS;
}


// Enqueue means add robot to the rear of the circular queue
void enqueueRobot() {
    if (isFull()) {
        cout << "\nRobot queue is full Cannot add more robots.\n";
        return;
    }
    int id;
    string name;

    cout << "\nEnter robot ID: ";
    cin >> id;
    
    cout << "Enter robot name: ";
    cin >> name;

    // If this is the first robot which is in the front starts at index 0
    if (queueFront == -1) {
        queueFront = 0;
    }

    // Move rear circularly and we use the % so that we dont exceed the max robot value number
    queueRear = (queueRear + 1) % MAX_ROBOTS;

    //we  store the robot details inside the array rear positions

    robotQueue[queueRear].robotID = id;
    robotQueue[queueRear].robotName = name;
    robotQueue[queueRear].status = AVAILABLE;
    robotQueue[queueRear].currentTaskID = 0;
    robotQueue[queueRear].totalTasksAssigned = 0;
    robotCount++;

    cout << "\nRobot added into the circular queue successfully.";

}

// Display all robots in the circular queue
void displayRobots() {
    if (isEmpty()) {
        cout << "\nNo robots in the queue.\n";

        return;
    }

    cout << "\nRobot Status Overview\n";
    for (int i = 0 ; i < robotCount ; i++) {
        cout << "\nRobot " << i + 1 << endl;
        cout << "Robot ID: " << robotQueue[i].robotID << endl;
        cout << "Robot Name: " << robotQueue[i].robotName << endl;
        cout << "Status: " << getStatusText(robotQueue[i].status) << endl;

        if (robotQueue[i].currentTaskID == 0) {
            cout << "Current Task: None " << endl;
        }

        else {
            cout << "Current Task: " << robotQueue[i].currentTaskID << endl ;
        }

        cout << "Total Tasks Assigned: " << robotQueue[i].totalTasksAssigned << endl ;

    }

}

// Update robot status
void updateRobotStatus() {

    if (isEmpty()) {
        cout << "\nNo robots available to update.\n";
        return;
    }

    int id;
    int statusChoice;
    bool found = false;

    cout << "\nEnter robot ID to update the status: ";
    cin >> id;

    for (int i = 0; i < robotCount; i++) {
        if (robotQueue[i].robotID == id) {
            found = true;

            cout << "\nChoose new status:\n " ;
            cout << "1. Available\n" ;
            cout << "2. Busy\n" ;
            cout << "3. Maintenance\n" ;
            cout << "Enter choice: " ;
            cin >> statusChoice ;

            if (statusChoice == 1) {
                robotQueue[i].status = AVAILABLE;
                robotQueue[i].currentTaskID = 0;
                cout << "\nRobot is now AVAILABLE.\n";
            }
            else if (statusChoice == 2) {
                robotQueue[i].status = BUSY;
                cout << "\nRobot is now BUSY.\n";
            }
            else if (statusChoice == 3) {
                robotQueue[i].status = MAINTENANCE;
                robotQueue[i].currentTaskID = 0;
                cout << "\nRobot is now under MAINTENANCE.\n";
            }

            else {
                cout << "\nInvalid status choice.\n";
            }
            break;
        }

    }
    if (!found) {
        cout << "\nRobot ID not found.\n";
    }

}

// Assign task using circular queue rotation
// Assign task using circular queue rotation
void assignTask() {
    if (isEmpty()) {
        cout << "\nNo robots available in the system.\n";
        return;
    }
    if (assignmentCount >= MAX_ASSIGNMENTS) {
        cout << "\nAssignment history is full.\n";
        return;
    }

    int taskID;
    int checkedRobots = 0;

    cout << "\nEnter task / order ID to assign: ";
    cin >> taskID;

    while (checkedRobots < robotCount) {
        cout << "\nChecking Robot " << robotQueue[currentRobotIndex].robotID;
        cout << " (" << robotQueue[currentRobotIndex].robotName << ")... ";

        if (robotQueue[currentRobotIndex].status == AVAILABLE) {
            robotQueue[currentRobotIndex].status = BUSY;
            robotQueue[currentRobotIndex].currentTaskID = taskID;
            robotQueue[currentRobotIndex].totalTasksAssigned++ ;

            assignments[assignmentCount].taskID = taskID;
            assignments[assignmentCount].robotID = robotQueue[currentRobotIndex].robotID;
            assignments[assignmentCount].robotName = robotQueue[currentRobotIndex].robotName;
            assignmentCount++;

            cout << "AVAILABLE\n";
            cout << "Task " << taskID << " assigned to Robot ";
            cout << robotQueue[currentRobotIndex].robotID << " (" << robotQueue[currentRobotIndex].robotName << ").\n";

            // Move to the next robot in circular order
            currentRobotIndex = (currentRobotIndex + 1) % robotCount;
            return;
        }
        else {
            cout << getStatusText(robotQueue[currentRobotIndex].status) << " - skipped.\n";

            // Move to the next robot in circular order
            currentRobotIndex = (currentRobotIndex + 1) % robotCount;
            checkedRobots++;
        }
    }

    cout << "\nNo available robots right now. Task cannot be assigned.\n";
}

// Complete robot task and make robot available again
void completeRobotTask() {
    if (isEmpty()) {
        cout << "\nNo robots available.\n";
        return;
    }

    int id;
    bool found = false;
    cout << "\nEnter robot ID that completed the task: ";
    cin >> id;

    for (int i = 0 ; i < robotCount ; i++) {

        if (robotQueue[i].robotID == id) {
            found = true;
            if (robotQueue[i].status == BUSY) {
                cout << "\nRobot " << robotQueue[i].robotID;
                cout << " completed Task " << robotQueue[i].currentTaskID << ".\n";

                robotQueue[i].currentTaskID = 0;
                robotQueue[i].status = AVAILABLE;
                cout << "Robot is now AVAILABLE again.\n" ;

            }

            else {
                cout << "\nThis robot is not busy, so it has no task to complete.\n";
            }

            break;
        }
    }

    if (!found) {
        cout << "\nRobot ID not found.\n";
    }

}

// Display assignment history
void displayAssignments() {
    if (assignmentCount == 0) {
        cout << "\nNo task assignments yet.\n";
        return;

    }
    cout << "\nRobot Assignment History\n";

    for (int i = 0; i < assignmentCount; i++) {
        cout << "\nAssignment " << i + 1 << endl;
        cout << "Task ID: " << assignments[i].taskID << endl;
        cout << "Robot ID: " << assignments[i].robotID << endl;
        cout << "Robot Name: " << assignments[i].robotName << endl;
    }

}

// Display menu
void showMenu() {
    cout << "\n=====================================\n";
    cout << "Task 2: Robot Assignment Module\n";
    cout << "=====================================\n";
    cout << "1. Enqueue/Add robot\n";
    cout << "2. Display robot status\n";
    cout << "3. Assign task to robot\n";
    cout << "4. Update robot status\n";
    cout << "5. Complete robot task\n";
    cout << "6. Display assignment history\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";
}

int main() {
    int choice;

    cout << "Warehouse Robot Navigation System\n";
    cout << "Task 2: Robot Assignment Module\n";

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            enqueueRobot();
            break;

        case 2:
            displayRobots();
            break;

        case 3:
            assignTask();
            break;

        case 4:
            updateRobotStatus();
            break;

        case 5:
            completeRobotTask();
            break;

        case 6:
            displayAssignments();
            break;

        case 0:
            cout << "\nExiting Robot Assignment Module.\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}