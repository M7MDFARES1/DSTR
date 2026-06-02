#ifndef TASK3_ROBOT_NAVIGATION_HPP
#define TASK3_ROBOT_NAVIGATION_HPP

#include <string>

const int MAX_STEPS = 100;
const int MAX_LOGS = 200;

std::string toLowerCase(std::string input);
std::string formatMovement(std::string input);
bool isExitChoice(std::string input);
bool isNormalMovement(std::string movement);
std::string getReverseMovement(std::string movement);

class MovementStack {
private:
    std::string steps[MAX_STEPS];
    int topIndex;

public:
    MovementStack();

    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;

    bool push(std::string movement);
    bool pop(std::string &movement);

    void displayForwardPath() const;
};

class NavigationLog {
private:
    std::string entries[MAX_LOGS];
    int logCount;

public:
    NavigationLog();

    bool addEntry(std::string message);
    void displayLog() const;
};

void showMenu();
void addMovementStep(
    MovementStack &pathStack,
    NavigationLog &navigationLog,
    std::string userInput
);
void addMovementStepsUntilDone(
    MovementStack &pathStack,
    NavigationLog &navigationLog
);
void returnUsingReversePath(
    MovementStack &pathStack,
    NavigationLog &navigationLog
);

#endif
