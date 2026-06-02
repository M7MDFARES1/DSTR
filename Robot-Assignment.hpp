#ifndef ROBOT_ASSIGNMENT_HPP
#define ROBOT_ASSIGNMENT_HPP

#include <iostream>
#include <string>
using namespace std;

// Maximum number of robots and assignment records
const int MAX_ROBOTS = 10;
const int MAX_ASSIGNMENTS = 50;

// Robot status enum enumeration is to name values to use later for choice
enum RobotStatus {
    AVAILABLE,
    BUSY,
    MAINTENANCE
};

// Robot struct
struct Robot {
    string robotID;
    string robotName;
    RobotStatus status;
    int currentTaskID;
    int totalTasksAssigned;
};

// Assignment struct
struct Assignment {
    int taskID;
    string robotID;
    string robotName;
};

// Global arrays
extern Robot robotQueue[MAX_ROBOTS];
extern Assignment assignments[MAX_ASSIGNMENTS];

// Queue variables
extern int queueFront;
extern int queueRear;
extern int robotCount;

// Assignment counter
extern int assignmentCount;

// This is used for robot assignment rotation
extern int currentRobotIndex;

// Function declarations
string getStatusText(RobotStatus status);

bool isEmpty();
bool isFull();

void enqueueRobot();
void displayRobots();
void updateRobotStatus();
void assignTask();
void completeRobotTask();
void displayAssignments();
void showMenu();

#endif