#include "MySimulator.h"
#include "House.h"
#include "enums.h"
#include "Coordinates.h"
#include "MyAlgorithm.h"
#include "Coordinates.h"
#include <iostream>
#include <string>



// getting command line arguments for the house file
/*int main(int argc, char** argv) {
    
    if (argc < 2) {
        std::cerr << "houseFilePath was not found in the argument list" << std::endl;
        return 1;
    }

    try {
        std::string houseFilePath = argv[1];
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
*/


// main for Debbuging
void algorithm_test(std::string file_path, std::string folder_path) {
    
    MyAlgorithm algo;
    MySimulator simulator;
    simulator.readHouseFile(file_path);
    simulator.setAlgorithm(algo);
    simulator.run();
    simulator.writeOutput(folder_path);

}



int main() {
        
    std::string folder_path = "C:\\Users\\Admin\\Desktop\\CPP Projects\\ex2\\inputs\\";
    std::string file_path = folder_path;
    file_path += "input.txt";
    
    std::string file_path1 = folder_path;
    file_path1 += "input1.txt";
    
    std::string file_path2 = folder_path;
    file_path2 += "input2.txt";

    std::string file_path3 = folder_path;
    file_path3 += "input3.txt";

    std::string file_path4 = folder_path;
    file_path4 += "input4.txt";

    algorithm_test(file_path, folder_path);
    algorithm_test(file_path1, folder_path);
    algorithm_test(file_path2, folder_path);
    algorithm_test(file_path3, folder_path);
    algorithm_test(file_path4, folder_path);


    return 0;
}

