#include "MySimulator.h"
#include <iostream>


MySimulator::MySimulator() : algorithm(nullptr), robot(&house), wallSensor(&house, &robot), 
    dirtSensor(&house, &robot), batteryMeter(house.getBatteryCapacity()), houseFilePath(" ")
{}


bool MySimulator::readHouseFile(const std::string& houseFilePath) {
    this->houseFilePath = houseFilePath;
    return house.loadFromFile(houseFilePath);
}


void MySimulator::setAlgorithm(MyAlgorithm& algo) {
    algorithm = &algo;
    algorithm->setStepsAndTotalDirt(house.getMaxStepsAllowed(), house.getTotalDirt());
    robot = VacuumCleaner(&house);
    wallSensor = MyWallsSensor(&house, &robot);
    dirtSensor = MyDirtSensor(&house, &robot);
    batteryMeter = MyBatteryMeter(house.getBatteryCapacity());

    algorithm->initAlgo(robot, wallSensor, dirtSensor, batteryMeter);
}


void MySimulator::run() {
    
    while (algorithm->getRemainedSteps() > 0 && robot.getBatteryLevel() > 0) {
        
        //printGraphStatus(algorithm->getRemainedSteps(), robot.getBatteryLevel());
        Step step = algorithm->nextStep();
        
        // Stay/CLEAN
        if(step == Step::Stay) {
            // CHARGE
            if (algorithm->isAtDocking()) {
                robot.charge();
            } 
            // CLEAN
            else {
                robot.clean();
                algorithm->decreaseTotalDirt();
            } 
        }
        // Finish
        else if (step == Step::Finish) {
            if(robot.getBatteryLevel() > 0) {
                status = Status:: FINISHED;
                break;
            }
            else {
                status = Status:: DEAD;
                break;
            }
        }
        // step  == North/East/South/West
        else {
            Direction direction = algorithm->convertStepToDirection(step);
            algorithm->move(algorithm->convertDirectionToStep(direction));
        } 
        algorithm->decreaseRemainedSteps();
        //if(step != Step::Finish && step != Step::Stay) { printStepStatus(); } 
    }

    if(algorithm->getRemainedSteps() == 0 && robot.getBatteryLevel() > 0 && algorithm->isAtDocking()){
        status = Status:: FINISHED;
    }
    // create output file
    writeOutput();
    //printGraphStatus(algorithm->getRemainedSteps(), robot.getBatteryLevel());
}


// write the output file
void MySimulator::writeOutput() const {
    
    std::string outputFileName = MySimulator::getOutputFileName(houseFilePath);
    
    std::ofstream outFile(outputFileName);
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
    outFile << "Steps:" << std::endl;
    for(int i = 0; i < algorithm->getStepsLogSize(); i++) {
        char c = algorithm->getCharFromStepsLog(i);
        outFile << c;
    }
    outFile << std::endl;
    outFile.close();
}


std::string MySimulator::getOutputFileName(const std::string& filePath) const {
    size_t pos = filePath.find_last_of("/\\");
    std::string fileName = (pos == std::string::npos) ? filePath : filePath.substr(pos + 1);
    return "output_" + fileName;
}


// for Debugging
void MySimulator::printLocation() {
    Coordinates currentLocation = robot.getCurrentLocation();
    //algorithm->printPathToDocking();
    //algorithm->printPathToDirtySpot();
    int x = currentLocation.getX();
    int y = currentLocation.getY();
    std::cout << "currentLocation: layout[" << x << "][" << y << "] = " << house.getLayoutVal(x, y) << "\n";
}   


void MySimulator::printLayout() {
    house.printLayout();
}


void MySimulator::printStepStatus() {
    int number_of_steps = house.getMaxStepsAllowed() - algorithm->getRemainedSteps();
    printLocation();
    std::cout << "number of steps so far = " << number_of_steps << std::endl;
    std::cout << "remainedSteps = " << algorithm->getRemainedSteps() << std::endl;
    std::cout << "totalDirt = " << algorithm->getToatalDirt() << std::endl;
    std::cout << "battery = " << robot.getBatteryLevel() << std::endl;
    printLayout();
    std::cout << "\n" << std::endl;

}


void MySimulator::printGraphStatus(int remainedSteps, int battery) {
    std::cout << "remainedSteps = " << remainedSteps << std::endl;
    std::cout << "battery = " << battery << std::endl;
    algorithm->printGraph();
}
