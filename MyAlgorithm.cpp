#include "MyAlgorithm.h"
#include <iostream>


MyAlgorithm::~MyAlgorithm() {}


MyAlgorithm::MyAlgorithm() 
    : graph(), robot(nullptr), wallSensor(nullptr), dirtSensor(nullptr), 
    batteryMeter(nullptr), remainedSteps(0), totalDirt(0), maxSteps(0) 
{}


void MyAlgorithm::setMaxSteps(std::size_t maxSteps) {
    this->maxSteps = maxSteps;
}


void MyAlgorithm::setWallsSensor(const WallsSensor& sensor) {
    this->wallSensor = &sensor;
}


void MyAlgorithm::setDirtSensor(const DirtSensor& sensor) {
    this->dirtSensor = &sensor;
}


void MyAlgorithm::setBatteryMeter(const BatteryMeter& meter) {
    this->batteryMeter = &meter;
}


void MyAlgorithm::setStepsAndTotalDirt(int steps, int dirt){
    remainedSteps = steps;
    totalDirt = dirt;
}


Step MyAlgorithm::nextStep() {
    
    graphReduceLines();
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

    // Check if there are walls around the current location and add to the graph if so
    addWalls();

    int dist_from_docking = minDistanceToDockingStation();
    int battery = robot->getBatteryLevel();
    int dist_from_dirty_spot = minDistanceToClean();
    // Edge case of low battery - Finish (don't go to unnecessary trips)
    if(isAtDocking() && isCharged() && battery == (2 * dist_from_dirty_spot + 1)) {
        stepsListLog.push_back('F');
        return Step::Finish;
    }
    // CLEAN or go to CHARGE
    if(battery == robot->getMaxBattery()) {
        isCargging = false;
    }
    // if the house is clean OR the battery is low - go to the Docking station
    if(totalDirt == 0 || isBatteryLow(battery, dist_from_docking) || isCargging || dist_from_docking == remainedSteps) {
        return returningToDocking();    
    }
    // if there is no new point in the graph that needs to be checked and there is also no point that needs to be cleared, 
    // resize the graph and try to find again
    if(dist_from_dirty_spot == -1) {
        graph.resize();
        dist_from_dirty_spot = minDistanceToClean();
    }
    // We are done or it is not possible to continue cleaning - go to Docking station and Finish
    if(dist_from_dirty_spot == -1) {
        // at a docking station and there is no way to reach the remaining dirt
        if(isAtDocking()) {
            stepsListLog.push_back(convertStepToChar(Step::Stay));
            return Step::Finish;
        }
        return returningToDocking();
    }
    // if there are not enough steps to clean or check new spot - go to Docking station and Finish 
    else if ((2 * dist_from_dirty_spot) > remainedSteps) {
        return returningToDocking();
    }
    // if there is no new spot known to the robot go to a dirt spot 
    else { //(dist_from_dirty_spot != -1) {
        return goToClean();
    }
    // Default setting
    return returningToDocking();
}


void MyAlgorithm::graphReduceLines() {
    while(graph.updateLayout());
}


void MyAlgorithm::addWalls() {
    Coordinates wallCoordinates = getCurrLocation();
    int colSize = graph.getNumOfCols();
    int rowSize = graph.getNumOfRows();
    int x = wallCoordinates.getX();
    int y = wallCoordinates.getY(); 
    if (x == 0 || x == colSize-1 || y == 0 || y == rowSize-1) {
        //graph.resize();
        if (y == 0) {
            graph.resizeN();
        }
        if (y == rowSize-1) {
            graph.resizeS();
        }
        if (x == 0) {
            graph.resizeW();
        }
        if (x == colSize-1) {
            graph.resizeE();
        }
    }
    Direction directions[4] = { Direction::North, Direction::East, Direction::South, Direction::West };
    for(int i = 0; i < 4; i++) {
        Direction dir = directions[i];
        wallCoordinates = getCurrLocation();
        if(wallSensor->isWall(dir)) {
            wallCoordinates = moveCoordinates(wallCoordinates,dir);
            graph.setVal(wallCoordinates, 'W');
        }
    }
}


Step MyAlgorithm::returningToDocking() {
    Step step;
    // already in the docking station
    if(isCargging || isAtDocking()) { 
        if(remainedSteps == 0) {
            step = Step::Finish;
            stepsListLog.push_back(convertStepToChar(step));
            return step; // Finish
        }
        else if(isCharged()) {
            isCargging = false;
            return goToClean(); // MOVE
        }
        else { //(still chargging)
            isCargging = true;
            step = Step::Stay;
            stepsListLog.push_back(convertStepToChar(step));
            return step; // CHARGE
        }
    }
    else { // Move - on the way to Docking station
        Direction dir = pathToDocking.front();
        pathToDocking.erase(pathToDocking.begin());
        step = convertDirectionToStep(dir); // Move
        stepsListLog.push_back(convertStepToChar(step));
        return step;
    }
}


Step MyAlgorithm::goToClean() {
    Step step;
    // reached the dirty point
    if(dirtSensor->dirtLevel() > 0) { 
        step = Step::Stay;
    }
    // on our way to the dirty spot
    else { 
        Direction dir = pathToDirtySpot.front();
        pathToDirtySpot.erase(pathToDirtySpot.begin());
        step = convertDirectionToStep(dir); // Move
    }
    stepsListLog.push_back(convertStepToChar(step));
    return step;
}


void  MyAlgorithm::initAlgo(VacuumCleaner& robot, WallsSensor& wallSensor, DirtSensor& dirtSensor, BatteryMeter& batteryMeter){
    
    this->robot = &robot; 
    setWallsSensor(wallSensor); 
    setDirtSensor(dirtSensor);
    setBatteryMeter(batteryMeter); 
    setMaxSteps(remainedSteps);
}


void MyAlgorithm::move(Step step){
    robot->move(convertStepToDirection(step));
    graph.move(convertStepToDirection(step));
    if(isAtDocking()) { return; }
    char c = '0' + dirtSensor->dirtLevel();
    if(c == '0') { c = ' '; }
    graph.setVal(graph.getCurrLocation(), c);
}


Coordinates MyAlgorithm::moveCoordinates (Coordinates coor, Direction d) {
    switch (d) {
        case Direction::North:
            coor = coor.getCoordinatesN();
            break;
        case Direction::South:
            coor = coor.getCoordinatesS();
            break;
        case Direction::West:
            coor = coor.getCoordinatesW();
            break;
        case Direction::East:
            coor = coor.getCoordinatesE();
            break;
    }
    return coor;
}

// helper functions for nextStep
int MyAlgorithm::minDistanceToDockingStation() {

    // Clear the pathToDocking for the new run
    pathToDocking.clear();
    //if already at a docking station    
    if (isAtDocking()) {
        return 0;
    }
    // Dimensions of the graph
    int rows = graph.getNumOfRows();
    int cols = graph.getNumOfCols();

    // Queue for BFS and a set for visited cells
    std::queue<Coordinates> q;
    std::vector<std::vector<bool>> visited(cols, std::vector<bool>(rows, false));
    std::vector<std::vector<int>> distance(cols, std::vector<int>(rows, std::numeric_limits<int>::max()));
    std::map<Coordinates, std::pair<Coordinates, Direction>> parent; // To track the path
      
    // Start BFS from the current location
    Coordinates currentLocation = graph.getCurrLocation();
    q.push(currentLocation);
    visited[currentLocation.getX()][currentLocation.getY()] = true;
    distance[currentLocation.getX()][currentLocation.getY()] = 0;
    
    // Directions for moving in the grid (Nort, South, West, East)
    std::vector<std::pair<int, int>> directions = { {0, -1}/*Nort*/, {0, 1}/*South*/, {1, 0}/*East*/, {-1, 0}/*West*/ };
    std::vector<Direction> directionEnums = { Direction::North, Direction::South, Direction::East, Direction::West };

    // docking station and current loction coordinates
    int dis = 0;
    Coordinates dock = graph.getDockingLocation();
    Coordinates current = graph.getCurrLocation();
    while (!q.empty()) {
        current = q.front();
        q.pop();
        // if current is out of the graph
        if(current.getX() >= cols || current.getY() >= rows || current.getX() < 0 || current.getY() < 0) {
            continue;
        }
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
            if (newX >= cols || newX < 0 || newY >= rows || newY < 0) {
                continue;;
            }
            Coordinates neighbor = {newX, newY};
            if (graph.getVal(neighbor) != '-' && validLocation(neighbor) && !visited[newX][newY]) {
                q.push(neighbor);
                visited[newX][newY] = true;
                distance[newX][newY] = distance[current.getX()][current.getY()] + 1;
                parent[neighbor] = {current, directionEnums[i]};
            }
        }
    }
    // Return -1 if the docking station is not reachable
    if (current.getX() != dock.getX() || current.getY() != dock.getY()) {
        return -1;
    }

    // creating path to the dirty spot
    current = graph.getDockingLocation();
    while (!(current == graph.getCurrLocation())) {
        auto p = parent[current];
        pathToDocking.push_back(p.second);
        current = p.first;
    }
    // The path is in reverse order, so reverse it
    std::reverse(pathToDocking.begin(), pathToDocking.end());
    return dis; 
}


int MyAlgorithm::minDistanceToClean() {
    
    // Clear the pathToDirtySpot for the new run
    pathToDirtySpot.clear();
    Coordinates currentLocation = graph.getCurrLocation();
    char charVal = graph.getVal(currentLocation);

    // if found a dirty spot
    if((charVal > '0' && charVal <= '9') || charVal == '-') {
        return 0;
    }
    // if there is no dirt left, return
    if (totalDirt == 0) {
        return -1;
    }
    // Dimensions of the layout
    int rows = graph.getNumOfRows();
    int cols = graph.getNumOfCols();;

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
    std::vector<std::pair<int, int>> directions = { {0, -1}/*Nort*/, {1, 0}/*East*/, {0, 1}/*South*/, {-1, 0}/*West*/ };
    std::vector<Direction> directionEnums = { Direction::North, Direction::East, Direction::South, Direction::West };
    
    int dis = 0;
    Coordinates current = graph.getCurrLocation();
    while (!q.empty()) {
        current = q.front();
        q.pop();       
        // if the current cell is a dirty spot or a new spot
        if(locationIsDirty(current) || graph.getVal(current) == '-') {
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
            if(newX >= graph.getNumOfCols() || newX < 0 || newY >= graph.getNumOfRows() || newY < 0) {
                continue;
            }
            Coordinates neighbor = {newX, newY};
            if (validLocation(neighbor) && !visited[newX][newY]) {
                q.push(neighbor);
                visited[newX][newY] = true;
                distance[newX][newY] = distance[current.getX()][current.getY()] + 1;
                parent[neighbor] = {current, directionEnums[i]};
            }
        }
    }
    // Return -1 if the the house is clean
    if (dirtySpot.getX() == -1 && dirtySpot.getY() == -1) {
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


Coordinates MyAlgorithm::getCurrLocation() const {
    return graph.getCurrLocation();
}


int MyAlgorithm::getRemainedSteps() {
    return remainedSteps;
}


int MyAlgorithm::getToatalDirt() {
    return totalDirt;
}


char MyAlgorithm::getCharFromStepsLog(int index) {
    return stepsListLog[index];
}


int MyAlgorithm::getStepsLogSize() {
    return int(stepsListLog.size());
}


bool MyAlgorithm::isAtDocking() const {
    return graph.getCurrLocation() == graph.getDockingLocation();
}


bool MyAlgorithm::isCharged() const{
    return robot->isCharged();
}


bool MyAlgorithm::validLocation(Coordinates coor) const {
    char c = graph.getVal(coor);
    int rowSize = graph.getNumOfRows();
    int colSize = graph.getNumOfCols();
    int x = coor.getX();
    int y = coor.getY();
    
    bool b1 = ((c >= '0' && c <= '9') || c == ' ' || c == 'D' || c == '-');
    bool b2 = (x >= 0 && y >= 0 && x <= colSize && y <= rowSize);
    return b1 && b2;
}


bool MyAlgorithm::locationIsDirty(Coordinates coor) const {
    char val = graph.getVal(coor);
    return (val > '0' && val <= '9');
}


void MyAlgorithm::decreaseRemainedSteps() {
    remainedSteps--;
}


void MyAlgorithm::decreaseTotalDirt(){
    totalDirt--;
    graph.clean();
}


bool MyAlgorithm::isBatteryLow(int battery, int dist_from_docking){
    return (battery < dist_from_docking + 3);
}


Step MyAlgorithm::convertDirectionToStep(Direction d) {
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


Direction MyAlgorithm::convertStepToDirection(Step s){
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


char MyAlgorithm::convertStepToChar(Step s){
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



// Debugging functions
void MyAlgorithm::printGraph() {
    graph.printGraph();
}


void MyAlgorithm::printPathToDocking() {
    std::cout << "pathToDocking: { ";
    for (int i = 0; i < static_cast<int>(pathToDocking.size()); ++i) {
        switch(pathToDocking[i]) {
            case Direction::North: std::cout << "North"; break;
            case Direction::South: std::cout << "South"; break;
            case Direction::East:  std::cout << "East"; break;
            case Direction::West:  std::cout << "West"; break;
        }
        if(i < static_cast<int>(pathToDocking.size()) - 1) { std::cout << ", "; }
    }
    std::cout << "}" << std::endl;
}


void MyAlgorithm::printPathToDirtySpot() {
    std::cout << "pathToDirtySpot: { ";
    for (int i = 0; i < static_cast<int>(pathToDirtySpot.size()); ++i) {
        switch(pathToDirtySpot[i]) {
            case Direction::North: std::cout << "North"; break;
            case Direction::South: std::cout << "South"; break;
            case Direction::East:  std::cout << "East"; break;
            case Direction::West:  std::cout << "West"; break;
        }
        if(i < static_cast<int>(pathToDirtySpot.size()) - 1) { std::cout << ", "; }
    }
    std::cout << "}" << std::endl;
}


void MyAlgorithm::printStepsLog() {
    char c;
    std::cout << "stepsListLog: { ";
    for (int i = 0; i < static_cast<int>(stepsListLog.size()); ++i) {
        c = stepsListLog[i];
        std::cout << c;
    }
    std::cout << "}" << std::endl;
}
