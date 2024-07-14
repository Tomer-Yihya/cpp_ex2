#include "House.h"
#include "enums.h"
/*/#include "battery_meter.h"
#include "Coordinates.h"
#include "dirt_sensor.h"
#include "MyAlgorithm.h"
/**/
#include <iostream>
#include <string>

void layout_test (std::string file_name){
    
    std::cout << std::endl;
    std::string folder_path = "C:\\Users\\Admin\\Desktop\\ex1_C++\\Cpp_ex2\\inputs\\";
    std::string file_path = folder_path;
    file_path += file_name;

    House house;
    //std::cout << "Testing: " << file_name << std::endl;
    try {
        house.loadFromFile(file_path);
    } 
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return;
    }
    //house.printLayout(); // Add this to print the layout and verify
    std::cout << std::endl;
}

void house_layout_test(){
    std::string file_name = "input.txt";
    std::string file_name1 = "input1.txt";
    std::string file_name2 = "input2.txt";
    std::string file_name3 = "input3.txt";
    std::string file_name4 = "input4.txt";
    
    layout_test(file_name);
    layout_test(file_name1);
    layout_test(file_name2);
    layout_test(file_name3);
    layout_test(file_name4);
}







int main() {
    
    house_layout_test();
    
   
    return 0;
}

