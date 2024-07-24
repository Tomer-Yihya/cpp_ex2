#include "Algorithm.h"
#include <iostream>
#include <algorithm>


Algorithm::~Algorithm() {}


Algorithm::Algorithm() : house(nullptr), robot(nullptr), wallSensor(nullptr), dirtSensor(nullptr), 
                        batteryMeter(nullptr), remainedSteps(0), totalDirt(0), maxSteps(0) 
{}


void Algorithm::setMaxSteps(std::size_t maxSteps) {
    this->maxSteps = maxSteps;
}


void Algorithm::setWallsSensor(const WallsSensor& sensor) {
    this->wallSensor = &sensor;
}


void Algorithm::setDirtSensor(const DirtSensor& sensor) {
    this->dirtSensor = &sensor;
}


void Algorithm::setBatteryMeter(const BatteryMeter& meter) {
    this->batteryMeter = &meter;
}


Step Algorithm::nextStep() {
    
    // DEAD
    if(remainedSteps <= 0) {
        robotIsDead = true;
        return Step::Finish; // DEAD
    }
    // FINISH
    if(totalDirt == 0 && isAtDocking()){
            stepsListLog.push_back('F');
            return Step::Finish;
    }

    Step step;
    Direction dir;
    int battery = robot->getBatteryLevel();
    int dist_from_docking = minDistanceToDockingStation();
    int dist_from_dirty_spot = minDistanceToDirtySpot();
    if(dist_from_dirty_spot == -1){
        isReturningToDocking = true;
        goToDirtySpot = false;
        step = chooseDirection(); 
        stepsListLog.push_back(convertStepToChar(step));
        return step; // MOVE - to Docking station
    }

    // if the house is clean OR the battery is low - go to the Docking station
    if(totalDirt == 0 || isBatteryLow(battery, dist_from_docking, dist_from_dirty_spot) || isCargging) {
        isReturningToDocking = true;
        goToDirtySpot = false; 
    }
    else {
        isReturningToDocking = false;
        goToDirtySpot = true;
    }

    // if the robot is on his way to the Docking station
    if(isReturningToDocking) {
        // already in the docking station
        if(isCargging || isAtDocking()) { 
            if(isCharged()) {
                isCargging = false;
                isReturningToDocking = false;
                goToDirtySpot = true;
                step = chooseDirection();
                stepsListLog.push_back(convertStepToChar(step));
                return step; // MOVE
            }
            //else (still chargging)
            isCargging = true;
            step = Step::Stay;
            stepsListLog.push_back(convertStepToChar(step));
            return step; // CHARGE
        }
        else { // Move - to Docking station
            dir = pathToDocking.front();
            pathToDocking.erase(pathToDocking.begin());
            step =  convertDirectionToStep(dir); // Move
            stepsListLog.push_back(convertStepToChar(step));
            return step;
        }
    }
    // if the robot is on his way to the closest dirty spot
    if(goToDirtySpot) {
        // reached the dirty point
        if(dirtSensor->dirtLevel() > 0) { 
            goToDirtySpot = false;
            stepsListLog.push_back('s');
            return Step::Stay; // CLEAN
        }
        // on our way to the dirty spot
        else { 
            dir = pathToDirtySpot.front();
            pathToDirtySpot.erase(pathToDirtySpot.begin());
            step =  convertDirectionToStep(dir); // Move
            stepsListLog.push_back(convertStepToChar(step));
            return step;
        }
    }

    // if we got here it's a bug!!!
    step = chooseDirection(); 
    stepsListLog.push_back(convertStepToChar(step));
    return step; // MOVE - to Docking station    
}


void  Algorithm::initAlgo(House& house, VacuumCleaner& robot, WallsSensor& wallSensor, DirtSensor& dirtSensor, BatteryMeter& batteryMeter){
    
    this->house = &house; 
    this->robot = &robot; 
    setWallsSensor(wallSensor); 
    setDirtSensor(dirtSensor);
    setBatteryMeter(batteryMeter); 
    remainedSteps = house.getMaxStepsAllowed();
    setMaxSteps(house.getMaxStepsAllowed());
    totalDirt = house.getTotalDirt();
}


// helper functions for nextStep
int Algorithm::minDistanceToDockingStation() {

    // Clear the pathToDocking for the new run
    pathToDocking.clear();

    // if there is no dirt left, return
    if (isAtDocking()) {
        return 0;
    }

    // Dimensions of the layout
    int rows = house->getRows() + 2;
    int cols = house->getCols() + 2;

    // Queue for BFS and a set for visited cells
    std::queue<Coordinates> q;
    std::vector<std::vector<bool>> visited(cols, std::vector<bool>(rows, false));
    std::vector<std::vector<int>> distance(cols, std::vector<int>(rows, std::numeric_limits<int>::max()));
    std::map<Coordinates, std::pair<Coordinates, Direction>> parent; // To track the path
      
    // Start BFS from the current location
    Coordinates currentLocation = robot->getCurrentLocation();
    q.push(currentLocation);
    visited[currentLocation.getX()][currentLocation.getY()] = true;
    distance[currentLocation.getX()][currentLocation.getY()] = 0;
    
    // Directions for moving in the grid (Nort, South, West, East)
    std::vector<std::pair<int, int>> directions = { {0, -1}/*Nort*/, {0, 1}/*South*/, {1, 0}/*East*/, {-1, 0}/*West*/ };
    std::vector<Direction> directionEnums = { Direction::North, Direction::South, Direction::East, Direction::West };

    // docking station and current loction coordinates
    int dis = 0;
    Coordinates dock = house->getDockingCoordinates();
    Coordinates current = robot->getCurrentLocation();
    while (!q.empty()) {
        current = q.front();
        q.pop();
        // check if the current cell is the docking station
        if (current == dock) {
            dis = distance[current.getX()][current.getY()];
            break;
        }
        // check neighbors
        int newX = -1;
        int newY = -1;
        for (int i = 0; i < 4; ++i) {
            newX = current.getX() + directions[i].first;
            newY = current.getY() + directions[i].second;
            if (validLocation(newX, newY) && !visited[newX][newY]) {
                Coordinates neighbor = {newX, newY};
                q.push(neighbor);
                visited[newX][newY] = true;
                distance[newX][newY] = distance[current.getX()][current.getY()] + 1;
                parent[neighbor] = {current, directionEnums[i]};
            }
        }
    }
    // Return -1 if the docking station is not reachable
    if (current.getX() != dock.getX() || current.getY() != dock.getY()) {
        std::cout << "The docking station cannot be found\n";
        return -1;
    }

    // creating path to the dirty spot
    current = house->getDockingCoordinates();
    while (!(current == robot->getCurrentLocation())) {
        auto p = parent[current];
        pathToDocking.push_back(p.second);
        current = p.first;
    }
    // The path is in reverse order, so reverse it
    std::reverse(pathToDocking.begin(), pathToDocking.end());
    return dis; 
}


int Algorithm::minDistanceToDirtySpot() {
    
    // Clear the pathToDirtySpot for the new run
    pathToDirtySpot.clear();
    
    Coordinates currentLocation = robot->getCurrentLocation();
    if(locationIsDirty(currentLocation.getX(), currentLocation.getY())) {
        return 0;
    }
    // If there is no dirt left, return
    if (totalDirt == 0) {
        return -1;
    }
    // Dimensions of the layout
    int rows = house->getRows() + 2;
    int cols = house->getCols() + 2;

    // Queue for BFS and a set for visited cells
    std::queue<Coordinates> q;
    std::vector<std::vector<bool>> visited(cols, std::vector<bool>(rows, false));
    std::vector<std::vector<int>> distance(cols, std::vector<int>(rows, std::numeric_limits<int>::max()));
    std::map<Coordinates, std::pair<Coordinates, Direction>> parent; // To track the path

    // Start BFS from the current location of the robot
    //Coordinates currentLocation = robot->getCurrentLocation();
    q.push(currentLocation);
    visited[currentLocation.getX()][currentLocation.getY()] = true;
    distance[currentLocation.getX()][currentLocation.getY()] = 0;

    Coordinates dirtySpot = {-1, -1};

    // Directions for moving in the grid (North, South, East, West)
    std::vector<std::pair<int, int>> directions = { {0, -1}/*Nort*/, {0, 1}/*South*/, {1, 0}/*East*/, {-1, 0}/*West*/ };
    std::vector<Direction> directionEnums = { Direction::North, Direction::South, Direction::East, Direction::West };
    
    int dis = 0;
    Coordinates current = robot->getCurrentLocation();
    while (!q.empty()) {
        current = q.front();
        q.pop();
        
        // if the current cell is a dirty spot
        if(locationIsDirty(current.getX(), current.getY())) {
            dis = distance[current.getX()][current.getY()];
            dirtySpot = current;
            break;
        }
        // Explore neighbors
        int newX = -1;
        int newY = -1;
        for (int i = 0; i < 4; ++i) {
            newX = current.getX() + directions[i].first;
            newY = current.getY() + directions[i].second;
            if (validLocation(newX, newY) && !visited[newX][newY]) {
                Coordinates neighbor = {newX, newY};
                q.push(neighbor);
                visited[newX][newY] = true;
                distance[newX][newY] = distance[current.getX()][current.getY()] + 1;
                parent[neighbor] = {current, directionEnums[i]};
            }
        }
    }
    // Return -1 if the the house is clean
    if (dirtySpot.getX() == -1 && dirtySpot.getY() == -1) {
        std::cout << "No dirty spot found.\n";
        return -1;
    }
    // Creating the route to the dirty spot
    current = dirtySpot;
    while (!(current == currentLocation)) {
        auto p = parent[current];
        pathToDirtySpot.push_back(p.second);
        current = p.first;
    }
    // The path is in reverse order, so reverse it
    std::reverse(pathToDirtySpot.begin(), pathToDirtySpot.end());
    return dis; 
}


Coordinates Algorithm::getCurrLocation() const {
    return robot->getCurrentLocation();
}


int Algorithm::getRemainedSteps() {
    return remainedSteps;
}


int Algorithm::getToatalDirt() {
    return totalDirt;
}


char Algorithm::getCharFromStepsLog(int index) {
    return stepsListLog[index];
}


int Algorithm::getStepsLogSize() {
    return stepsListLog.size();
}


bool Algorithm::isAtDocking() const {
    return robot->getCurrentLocation() == house->getDockingCoordinates();
}


bool Algorithm::isCharged() const{
    return robot->isCharged();
}


bool Algorithm::validLocation(int x, int y) const {
    int maxCol = house->getRows()+2;
    int maxRow = house->getCols()+2;
    char c = house->getLayoutVal(x, y);
    return (x >= 0  && x < maxRow && y >= 0 && y < maxCol && c != 'W');
}


bool Algorithm::locationIsDirty(int x, int y) const {
    char val = house->getLayoutVal(x,y);
    return (val > '0' && val <= '9');
}


void Algorithm::decreaseRemainedSteps() {
    remainedSteps--;
}


void Algorithm::decreaseTotalDirt(){
    totalDirt--;
}


bool Algorithm::isBatteryLow(int battery, int dist_from_docking, int dist_from_dirty_spot){
    return ((battery == dist_from_docking + 2) || (battery == dist_from_docking + 1));
}


// call this function only in "Move" cases
Step Algorithm::chooseDirection() {

    Direction direction;
    
    if(isReturningToDocking){ 
        if(!pathToDocking.empty()){
            direction = pathToDocking.front();
            pathToDocking.erase(pathToDocking.begin());
            return convertDirectionToStep(direction);
        } 
    }
    else if(goToDirtySpot){ 
        if(!pathToDirtySpot.empty()){
            direction = pathToDirtySpot.front();
            pathToDirtySpot.erase(pathToDirtySpot.begin());
            return convertDirectionToStep(direction);
        } 
    }
    // if we got here it's a bug!
    return Step::North;
}


Step Algorithm::convertDirectionToStep(Direction d) {
    switch (d) {
        case Direction::North:
            return Step::North;
        case Direction::South:
            return Step::South;
        case Direction::West:
            return Step::West;
        case Direction::East:
            return Step::East;
        default:
            return Step::North;
    }
}


Direction Algorithm::convertStepToDirection(Step s){
    switch (s) {
        case Step::North:
            return Direction::North;
        case Step::South:
            return Direction::South;
        case Step::West:
            return Direction::West;
        case Step::East:
            return Direction::East;
        default:
            return Direction::North;
    }
}


char Algorithm::convertStepToChar(Step s){
    switch (s) {
        case Step::North:
            return 'N';
        case Step::South:
            return 'S';
        case Step::West:
            return 'W';
        case Step::East:
            return 'E';
        case Step::Stay:
            return 's';
        case Step::Finish:
            return 'F';
        default:
            return 's';
    }

}


void Algorithm::printPathToDocking() {
    std::cout << "pathToDocking: { ";
    for (int i = 0; i < pathToDocking.size(); ++i) {
        switch(pathToDocking[i]) {
            case Direction::North: std::cout << "North"; break;
            case Direction::South: std::cout << "South"; break;
            case Direction::East:  std::cout << "East"; break;
            case Direction::West:  std::cout << "West"; break;
        }
        if(i < pathToDocking.size() - 1) { std::cout << ", "; }
    }
    std::cout << "}" << std::endl;
}


void Algorithm::printPathToDirtySpot() {
    std::cout << "pathToDirtySpot: { ";
    for (int i = 0; i < pathToDirtySpot.size(); ++i) {
        switch(pathToDirtySpot[i]) {
            case Direction::North: std::cout << "North"; break;
            case Direction::South: std::cout << "South"; break;
            case Direction::East:  std::cout << "East"; break;
            case Direction::West:  std::cout << "West"; break;
        }
        if(i < pathToDirtySpot.size() - 1) { std::cout << ", "; }
    }
    std::cout << "}" << std::endl;
}


void Algorithm::printStepsLog() {
    char c;
    std::cout << "stepsListLog: { ";
    for (int i = 0; i < stepsListLog.size(); ++i) {
        c = stepsListLog[i];
        std::cout << c;
    }
    std::cout << "}" << std::endl;
}