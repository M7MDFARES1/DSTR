#include "Task3RobotNavigation.hpp"

#include <cstddef>
#include <iostream>

using namespace std;

string toLowerCase(string input) {
    string lowerInput = "";

    for (size_t i = 0; i < input.length(); i++) {
        char letter = input[i];

        if (letter >= 'A' && letter <= 'Z') {
            letter = letter + 32;
        }

        lowerInput += letter;
    }

    return lowerInput;
}

string formatMovement(string input) {
    string lowerInput = toLowerCase(input);

    if (lowerInput == "forward") {
        return "Forward";
    }
    else if (lowerInput == "left") {
        return "Left";
    }
    else if (lowerInput == "right") {
        return "Right";
    }
    else if (lowerInput == "back") {
        return "Back";
    }
    else if (lowerInput == "obstacle") {
        return "Obstacle";
    }

    return "Invalid";
}

bool isExitChoice(string input) {
    string lowerInput = toLowerCase(input);

    return lowerInput == "0" ||
           lowerInput == "exit";
}

bool isNormalMovement(string movement) {
    return movement == "Forward" ||
           movement == "Left" ||
           movement == "Right" ||
           movement == "Back";
}

string getReverseMovement(string movement) {
    if (movement == "Forward") {
        return "Back";
    }
    else if (movement == "Back") {
        return "Forward";
    }
    else if (movement == "Left") {
        return "Right";
    }
    else if (movement == "Right") {
        return "Left";
    }

    return movement;
}

MovementStack::MovementStack() {
    topIndex = -1;
}

bool MovementStack::isEmpty() const {
    return topIndex == -1;
}

bool MovementStack::isFull() const {
    return topIndex == MAX_STEPS - 1;
}

int MovementStack::getSize() const {
    return topIndex + 1;
}

bool MovementStack::push(string movement) {
    if (isFull()) {
        return false;
    }

    topIndex++;
    steps[topIndex] = movement;
    return true;
}

bool MovementStack::pop(string &movement) {
    if (isEmpty()) {
        return false;
    }

    movement = steps[topIndex];
    topIndex--;
    return true;
}

void MovementStack::displayForwardPath() const {
    if (isEmpty()) {
        cout << "\nNo movement steps have been added yet.\n";
        return;
    }

    cout << "\nForward Path Taken by Robot\n";
    for (int i = 0; i <= topIndex; i++) {
        cout << i + 1 << ". " << steps[i] << endl;
    }
}

NavigationLog::NavigationLog() {
    logCount = 0;
}

bool NavigationLog::addEntry(string message) {
    if (logCount == MAX_LOGS) {
        return false;
    }

    entries[logCount] = message;
    logCount++;
    return true;
}

void NavigationLog::displayLog() const {
    if (logCount == 0) {
        cout << "\nNavigation log is empty.\n";
        return;
    }

    cout << "\nComplete Navigation Log\n";
    for (int i = 0; i < logCount; i++) {
        cout << i + 1 << ". " << entries[i] << endl;
    }
}

void showMenu() {
    cout << "\n=====================================\n";
    cout << "Task 3: Robot Navigation Module\n";
    cout << "=====================================\n";
    cout << "1. Add movement step\n";
    cout << "2. Show forward path\n";
    cout << "3. Return using reverse path\n";
    cout << "4. Show complete navigation log\n";
    cout << "5. Exit\n";
    cout << "Enter choice: ";
}

void addMovementStep(MovementStack &pathStack, NavigationLog &navigationLog, string userInput) {
    string movement = formatMovement(userInput);

    if (movement == "Invalid") {
        return;
    }

    if (movement == "Obstacle") {
        string previousMovement;
        string reverseMovement;

        cout << "\nObstacle detected.\n";
        navigationLog.addEntry("Obstacle detected.");

        if (pathStack.pop(previousMovement)) {
            reverseMovement = getReverseMovement(previousMovement);

            cout << "Backtracking one step: " << reverseMovement;
            cout << " (reverse of " << previousMovement << ")" << endl;

            navigationLog.addEntry("Backtracked using " + reverseMovement +
                                   " (reverse of " + previousMovement + ")");
        }
        else {
            cout << "No previous movement to backtrack from.\n";
            navigationLog.addEntry("Obstacle found at starting point. No backtracking needed.");
        }

        string alternativeMovement;

        do {
            cout << "Enter alternative movement (Forward, Left, Right, Back): ";
            getline(cin, userInput);
            alternativeMovement = formatMovement(userInput);

        } while (!isNormalMovement(alternativeMovement));

        if (pathStack.push(alternativeMovement)) {
            cout << "\nAlternative movement added: " << alternativeMovement << endl;
            navigationLog.addEntry("Alternative movement added: " + alternativeMovement);
        }
        else {
            cout << "\nAlternative movement could not be added because the stack is full.\n";
            navigationLog.addEntry("Alternative movement was not added because the stack is full.");
        }

        return;
    }

    if (pathStack.isFull()) {
        cout << "\nPath stack is full. No more movements can be added.\n";
        navigationLog.addEntry("Movement was not added because the path stack is full.");
        return;
    }

    if (pathStack.push(movement)) {
        cout << "\nMovement added: " << movement << endl;
        navigationLog.addEntry("Movement added: " + movement);
    }
    else {
        cout << "\nMovement could not be added because the stack is full.\n";
        navigationLog.addEntry("Movement was not added because the stack is full.");
    }
}

void addMovementStepsUntilDone(MovementStack &pathStack, NavigationLog &navigationLog) {
    string userInput;

    cout << "\nAdd movements one by one.";
    cout << "\nType 0 or Exit when you are finished.\n";

    while (!pathStack.isFull()) {
        cout << "\nEnter movement (Forward, Left, Right, Back, Obstacle, or Exit): ";
        getline(cin, userInput);

        if (isExitChoice(userInput)) {
            cout << "\nFinished adding movements. Returning to main menu.\n";
            return;
        }

        addMovementStep(pathStack, navigationLog, userInput);
    }

    cout << "\nPath stack is full. Returning to main menu.\n";
}

void returnUsingReversePath(MovementStack &pathStack, NavigationLog &navigationLog) {
    if (pathStack.isEmpty()) {
        cout << "\nNo path available. Add movement steps first.\n";
        navigationLog.addEntry("Return requested, but no movement steps were available.");
        return;
    }

    string originalMovement;
    string reverseMovement;
    int stepNumber = 1;

    cout << "\nReverse Path for Robot Return\n";

    while (!pathStack.isEmpty()) {
        pathStack.pop(originalMovement);
        reverseMovement = getReverseMovement(originalMovement);

        cout << stepNumber << ". " << reverseMovement;
        cout << " (reverse of " << originalMovement << ")" << endl;

        navigationLog.addEntry("Return step: " + reverseMovement +
                               " (reverse of " + originalMovement + ")");

        stepNumber++;
    }

    cout << "\nRobot has returned to the starting point.\n";
    navigationLog.addEntry("Robot returned to the starting point.");
}

int main() {
    MovementStack pathStack;
    NavigationLog navigationLog;
    string choice;

    cout << "Warehouse Robot Navigation System\n";
    cout << "Task 3: Robot Navigation and Path Tracking Module\n";

    do {
        showMenu();
        getline(cin, choice);

        if (choice == "1") {
            addMovementStepsUntilDone(pathStack, navigationLog);
        }
        else if (choice == "2") {
            pathStack.displayForwardPath();
        }
        else if (choice == "3") {
            returnUsingReversePath(pathStack, navigationLog);
        }
        else if (choice == "4") {
            navigationLog.displayLog();
        }
        else if (choice == "5") {
            cout << "\nExiting Robot Navigation Module.\n";
        }
        else {
            cout << "\nInvalid choice. Please enter a number from 1 to 5.\n";
        }

    } while (choice != "5");

    return 0;
}
