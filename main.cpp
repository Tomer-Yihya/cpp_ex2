#include "MySimulator.h"
#include "House.h"
#include "enums.h"
#include "Coordinates.h"
#include "MyAlgorithm.h"
#include "Coordinates.h"
#include <string>
#include <iostream>


#include <cstring>

int main(int argc, char** argv) {
    // Checking that there are enough arguments
    if (argc < 2) {
        std::cerr << "houseFilePath was not found in the argument list" << std::endl;
        return 1;
    }
    try {
        std::string houseFilePath = argv[1];
        //std::cout << houseFilePath << std::endl;
        MySimulator simulator;
        simulator.readHouseFile(houseFilePath);
        MyAlgorithm algo;
        simulator.setAlgorithm(algo);
        simulator.run();
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}

