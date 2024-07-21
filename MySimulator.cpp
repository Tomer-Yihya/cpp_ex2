#include "MySimulator.h"
#include <iostream>


MySimulator::MySimulator() :
    algorithm(nullptr), robot(&house), wallSensor(&house, &robot), 
    dirtSensor(&house, &robot), batteryMeter(house.getBatteryCapacity())
{}


bool MySimulator::readHouseFile(const std::string& houseFilePath) {
    return house.loadFromFile(houseFilePath);
}


void MySimulator::setAlgorithm(Algorithm& algo) {
    algorithm = &algo;
    robot = VacuumCleaner(&house);
    wallSensor = WallsSensor(&house, &robot);
    dirtSensor = DirtSensor(&house, &robot);
    batteryMeter = BatteryMeter(house.getBatteryCapacity());

    algorithm->initAlgo(house, robot, wallSensor, dirtSensor, batteryMeter);
}


void MySimulator::run() {
    while (algorithm->getRemainedSteps() > 0 && robot.getBatteryLevel() > 0) {
        
        // for Debugging
        printStepStatus();
        
        std::string action = algorithm->chooseAction();
        Step step;

        if (action == "MOVE") {
            //Step step = algorithm->chooseDirection();
            step = algorithm->nextStep();
            stepsLog.push_back(step);
            Direction direction = algorithm->convertStepToDirection(step);
            robot.move(direction);
        } 
        else if (action == "CLEAN") {
            robot.clean();
            stepsLog.push_back(Step::Stay);
            algorithm->decreaseTotalDirt();
        } 
        else if (action == "CHARGE") {
            robot.charge();
            stepsLog.push_back(Step::Stay);
        } 
        else if (action == "FINISH") {
            stepsLog.push_back(Step::Finish);
            return;
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


void MySimulator::printStepStatus() {
    printLocation();
            std::cout << "remainedSteps = " << algorithm->getRemainedSteps() << std::endl;
            std::cout << "totalDirt = " << algorithm->getToatalDirt() << std::endl;
            std::cout << "battery = " << robot.getBatteryLevel() << std::endl;
            printLayout();
            std::cout << "\n" << std::endl;

}

// write the output file
void MySimulator::writeOutput(std::string outputFilePath) const {
    outputFilePath +=  "output.txt";
    std::ofstream outFile(outputFilePath);
    if (!outFile) {
        std::cerr << "Error opening output file." << std::endl;
        return;
    }
    
    int totalSteps = house.getMaxStepsAllowed() - algorithm->getRemainedSteps();
    int remainedDirt = algorithm->getToatalDirt();


    outFile << "NumSteps = " << totalSteps << std::endl;
    outFile << "DirtLeft = " << remainedDirt << std::endl;
    switch (status) {
        case Status::FINISHED:
            outFile << "Status = FINISHED" << std::endl;
            break;
        case Status::WORKING:
            outFile << "Status = WORKING" << std::endl;
            break;
        case Status::DEAD:
            outFile << "Status = DEAD" << std::endl;
            break;
    }

    // add a print of the steps list
    char c;
    for(Step s : stepsLog) {
        c = algorithm->convertStepToChar(s);
        outFile << c;
    }
    outFile << std::endl;

    outFile.close();
}