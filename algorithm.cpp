#include "Algorithm.h"
#include <iostream>
#include <vector>
#include <queue>



Algorithm::~Algorithm() {}


Algorithm::Algorithm() : house(nullptr), robot(nullptr), wallSensor(nullptr), dirtSensor(nullptr), 
                        batteryMeter(nullptr), remainedSteps(0), totalDirt(0), maxSteps(0) {}



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
    
    int dis = minDistanceToDockingStation();
    std::cout << "distance from docking station = " << dis << std::endl;
    return Step::North;
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

    Coordinates CurrLocation = robot->getCurrentLocation();
    if (CurrLocation == house->getDockingCoordinates()) {
        return 0;
    }

    //std::vector<std::vector<char>> layout = house->getLayout();
    std::vector<std::vector<bool>> visited(house->getRows(), std::vector<bool>(house->getCols(), false));
    std::queue<std::pair<Coordinates, int>> q; // pair of Coordinates and current distance
    
    // Start BFS from the current location
    q.push({CurrLocation, 0});
    visited[CurrLocation.getY()][CurrLocation.getX()] = true;

    Coordinates n, s, w, e;
    while (!q.empty()) {
        auto current = q.front();
        Coordinates temp = current.first;
        int dist = current.second;
        q.pop();

        if (temp == house->getDockingCoordinates()) {
            return dist;
        }

        // Explore all four possible movements
        if(!wallSensor->isWall(Direction::North)) {
            n = temp.getCoordinatesN();
            visited[n.getY()][n.getX()] = true;
            q.push({Coordinates(n.getX(), n.getY()), dist + 1});
        }
        if(!wallSensor->isWall(Direction::East)) {
            e = temp.getCoordinatesE();
            visited[e.getY()][e.getX()] = true;
            q.push({Coordinates(e.getX(), e.getY()), dist + 1});
        }
        if(!wallSensor->isWall(Direction::South)) {
            s = temp.getCoordinatesS();
            visited[s.getY()][s.getX()] = true;
            q.push({Coordinates(s.getX(), s.getY()), dist + 1});
        }
        if(!wallSensor->isWall(Direction::West)) {
            w = temp.getCoordinatesW();
            visited[w.getY()][w.getX()] = true;
            q.push({Coordinates(w.getX(), w.getY()), dist + 1});
        }
    }
    return -1;
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


/*/ to do
Direction Algorithm::chooseDirection(){
    
    Direction d = Direction::North;
    
    switch (d) {
        case Direction::North:
            break;
        case Direction::South:
            break;
        case Direction::East:
            break;
        case Direction::West:
            break;
    }

    return d;
}
/**/


bool Algorithm::isAtDocking() const {
    return robot->getCurrentLocation() == house->getDockingCoordinates();
}

bool Algorithm::isCharged() const{
    return robot->isCharged();
}

void Algorithm::decreaseRemainedSteps() {
    remainedSteps--;
}

void Algorithm::decreaseTotalDirt(){
    totalDirt--;
}

// from ex1

std::string Algorithm::chooseAction() {
    
    // the house is clean
    if(totalDirt == 0) {
        isReturningToDocking = true;
        if(isAtDocking()){
            return actions[3]; // FINISH
        }
        return actions[0]; // MOVE
    }

    //int distance_from_docking_station = minDistanceToDockingStation();
    int distance_from_docking_station = pathToDocking.size();
    
    if(isAtDocking()){
        // if get to the docking station (even accidentally), reset the route back
        emptyQueue();

        // if the robot finish charging
        if(isCharged()) {
            isCargging = false;
            isReturningToDocking = false;
            return actions[0]; // MOVE
        }
        // if the robot is charging or has returned to docking station to charge
        if(isCargging || robot->getBatteryLevel() == 1) {
            isCargging = true;
            return actions[2]; // CHARGE
        }
        // There is still some battery left, so you don't have to charge it
        if(robot->getBatteryLevel() > distance_from_docking_station + 2){
            return actions[0]; // MOVE
        }
        // There is very little battery left so charge now
        else {
            isCargging = true;
            return actions[2]; // CHARGE
        }
    }

    // if the distance from the charging station is equal to the remaining battery + 1 or 2 steps - go charge
    else if((robot->getBatteryLevel() == distance_from_docking_station + 2) || 
            (robot->getBatteryLevel() == distance_from_docking_station + 1)) {
        isReturningToDocking = true;
        return actions[0]; // MOVE    
    }
    // no need to charge right now
    else { 
        // still dirty - keep cleaning
        if(dirtSensor->dirtLevel() > 0) {
            return actions[1]; // CLEAN
        }
        // this spot is clean - move
        else { 
            return actions[0]; // MOVE      
        }
    }
}


Direction Algorithm::chooseDirection() {

    if(isReturningToDocking){ 
        if(!pathToDocking.empty()){
            Direction dirction = pathToDocking.top();
            pathToDocking.pop(); 
            return dirction;
        } 
    }
    
    std::vector<Direction> possibleDirections;
    if (!wallSensor->isWall(Direction:: North)) {  possibleDirections.push_back(Direction::North); }
    if (!wallSensor->isWall(Direction:: South)) {  possibleDirections.push_back(Direction::South); }
    if (!wallSensor->isWall(Direction:: East))  {  possibleDirections.push_back(Direction::East); }
    if (!wallSensor->isWall(Direction:: West))  {  possibleDirections.push_back(Direction::West); }

    // No possible directions
    if (possibleDirections.empty()) {
        throw std::runtime_error("The robot is stuck and cannot move in any direction\n"); 
    }

    // Choose a random direction from the possible directions
    //int randomIndex = ((totalDirt + 19) % possibleDirections.size());
    //Direction direction = possibleDirections[randomIndex];
    
    Direction direction;
    for(int i = 0; i < possibleDirections.size(); i++ ){
        direction = possibleDirections[i];
        if(nextStepDirty(direction)){
            break;
        } 
    }

    // Enter the opposite direction to the direction of progress to know how to return
    switch (direction) {
        case Direction::North:
            pathToDocking.push(Direction::South);
            break;
        case Direction::South:
            pathToDocking.push(Direction::North);
            break;
        case Direction::West:
            pathToDocking.push(Direction::East);
            break;
        case Direction::East:
            pathToDocking.push(Direction::West);
            break;
    }    
    return direction;
}


bool Algorithm::nextStepDirty(Direction d) {
    Coordinates temp = robot->getCurrentLocation();
    int x = temp.getX();
    int y = temp.getY();
    char c = '0';
    switch (d) {
        case Direction::North:
            c = house->getLayoutVal(x,y-1);
            break;
        case Direction::South:
            c = house->getLayoutVal(x,y+1);
            break;
        case Direction::West:
            c = house->getLayoutVal(x-1,y);
            break;
        case Direction::East:
            c = house->getLayoutVal(x+1,y);
            break;
    }
    return (c > '0' && c <= '9' && c != 'D' && c != ' ');
}


void Algorithm::emptyQueue(){
    while (!pathToDocking.empty()) {
        pathToDocking.pop();
    }
}


void Algorithm::printQueue() {
    std::stack<Direction> temp = pathToDocking;  // Make a copy of the stack to preserve the original
    std::vector<Direction> elements;

    // Transfer elements from the stack to a vector to print in the correct order
    while (!temp.empty()) {
        elements.push_back(temp.top());
        temp.pop();
    }

    // Print elements in reverse order to maintain stack order
    std::cout << "Queue: ";
    for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
        // Convert the enum to an integer for printing
        std::cout << static_cast<int>(*it) << " ";
    }
    std::cout << std::endl;
}


int Algorithm::getQueueSize(){
    return pathToDocking.size();
}


