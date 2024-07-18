#include "MySimulator.h"
#include <iostream>

MySimulator::MySimulator() : algorithm(nullptr), robot(&house), wallSensor(&house, &robot), dirtSensor(&house, &robot), batteryMeter(&house) {}


bool MySimulator::readHouseFile(const std::string& houseFilePath) {
    return house.loadFromFile(houseFilePath);
}


void MySimulator::setAlgorithm(Algorithm& algo) {
    algorithm = &algo;
    robot = VacuumCleaner(&house);
    wallSensor = WallsSensor(&house, &robot);
    dirtSensor = DirtSensor(&house, &robot);
    batteryMeter = BatteryMeter(&house);

    algorithm->initAlgo(house, robot, wallSensor, dirtSensor, batteryMeter);
}


void MySimulator::run() {
    while (algorithm->getRemainedSteps() > 0 && robot.getBatteryLevel() > 0) {
        //std::cout << "\n" << std::endl;
        printLocation();
        printLayout();
        std::cout << "\n" << std::endl;

        std::string action = algorithm->chooseAction();

        if (action == "MOVE") {
            Direction direction = algorithm->chooseDirection();
            robot.move(direction);
        } 
        else if (action == "CLEAN") {
            robot.clean();
        } 
        else if (action == "CHARGE") {
            robot.charge();
        } 
        else if (action == "FINISH") {
            break;
        }

        algorithm->decreaseRemainedSteps();
    }

    std::cout << "The house Layout after the cleaning of the robot is finished: " << std::endl;
    printLayout();
    std::cout << "\n" << std::endl;
}


void MySimulator::printLocation() {
    Coordinates currentLocation = robot.getCurrentLocation();
    int x = currentLocation.getX();
    int y = currentLocation.getY();
    std::cout << "currentLocation: layout[" << x << "][" << y << "] = " << (house.getLayoutVal(x, y) == ' ' ? '_' : house.getLayoutVal(x, y)) << "\n";
}   


void MySimulator::printLayout() {
    house.printLayout();
}



