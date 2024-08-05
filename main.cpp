#include "MySimulator.h"
#include "House.h"
#include "enums.h"
#include "Coordinates.h"
#include "MyAlgorithm.h"
#include <iostream>
#include <string>
#include <cstring>


int main(int argc, char** argv) {
    
    if (argc < 2) {
        std::cerr << "houseFilePath was not found in the argument list" << std::endl;
        return 1;
    }
    try {
        std::string houseFilePath = argv[1];
        MySimulator simulator;
        if(!simulator.readHouseFile(houseFilePath)){
            throw std::runtime_error("Failed to open the input file.");
        }
        MyAlgorithm algo;
        simulator.setAlgorithm(algo);
        //simulator.printStepStatus(); // see the house before 
        simulator.run();
        //simulator.printStepStatus(); // see the house after
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}

