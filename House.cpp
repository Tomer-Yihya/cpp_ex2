#ifndef SENSORS_H
#define SENSORS_H

#include "House.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// construnctor
/*House (const std::string& file_path) { 
    loadFromFile(file_path);
}
*/



bool House::loadFromFile(const std::string& file_path) {
    
    std::ifstream file(file_path);
    if (!file) {
        //return false;
        throw std::runtime_error("Failed to open the input file.");
    }
    std::string line;
    //std::vector<char> row = std::vector<char>(line.begin(), line.end());
    if (std::getline(file, line)) fileName = line;
    std::getline(file, line); 
    if (!checkParameter(line, "MaxSteps", maxSteps)) return false;
    std::getline(file, line); 
    if (!checkParameter(line, "MaxBattery", maxBattery)) return false;
    std::getline(file, line); 
    if (!checkParameter(line, "Rows", rows)) return false;
    std::getline(file, line); 
    if (!checkParameter(line, "Cols", cols)) return false;
    
    battery = maxBattery;

    int index = 0;
    bool firstOrLast = false;
    std::vector<char> row;
    while (std::getline(file, line)) {
        row = std::vector<char>(line.begin(), line.end());
        fixLine(row, firstOrLast);
        layout.push_back(row);
    }

    // for Debugging    
    std::vector<std::vector<char>> originalLayout = layout;

    // makes sure that the Layout is exactly the size rows on cols
    cutExtraWalls();
    
    // adding an outer frame of walls
    addWalls();
    
    // Find the docking station
    bool found_docking = false;
    for (int y = 0; y < static_cast<int>(layout.size()); ++y) {
        for (int x = 0; x < static_cast<int>(layout[y].size()); ++x) {
            if (layout[y][x] == 'D') {
                found_docking = true;
                docking_x = x;
                docking_y = y;
                curr_x = docking_x;
                curr_y = docking_y;
                break;
            }
        }
    }
    
    /*/ Debugging prints
    std::cout << "fileName = " << fileName << std::endl;
    std::cout << "MaxSteps = " << maxSteps << std::endl;
    std::cout << "maxBattery = " << maxBattery << std::endl;
    std::cout << "Rows = " << rows << std::endl;
    std::cout << "Cols = " << cols << std::endl;
    //std::cout << "Layout after addWalls:" << std::endl;
    printTwoLayout(originalLayout);
    //printLayout();
    printDocking();
    /**/

    if (!found_docking) {
        throw std::runtime_error("Docking station not found in house layout.");
    }
    
    file.close();
    return true;
}


// helping functions
bool House::checkParameter(const std::string line, const std::string paramName, int& param) {
    std::string firsrNewParam = paramName + " =";
    std::string secondNewParam = paramName + "=";
    try {
        if (line.find(firsrNewParam) != std::string::npos) {
            param = std::stoi(line.substr(line.find('=') + 1));
            return true;
        }
        else if (line.find(secondNewParam) != std::string::npos) {
            param = std::stoi(line.substr(line.find('=') + 1));
            return true;
        }
        else {
            std::cout << "The " << paramName << " was not provided as required by the format" << std::endl;
            return false;
        }        
    } 
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "For some reason, std::stoi function can't convert the " << paramName << " into int" << std::endl;
        return false;
    }
    return false;
}

void House::cutExtraWalls() {
    if (static_cast<int>(layout.size()) == rows) {
        return;
    }
    else if (static_cast<int>(layout.size()) > rows) {
        layout.resize(rows);
    }
    // if there are fewer rows than rows, add empty rows
    else{
        while (static_cast<int>(layout.size()) < rows) {
            std::vector<char> newRow(cols, ' ');
            layout.push_back(newRow);
        }

    }
}

void House::addWalls() {
    // add upper walls (first line) of length cols
    layout.insert(layout.begin(), std::vector<char>(cols, 'W'));
    // add buttom walls (last line) of length cols
    layout.push_back(std::vector<char>(cols, 'W'));
    // add 'W' char to the first and last char of ech line
    for (size_t i = 0; i < layout.size(); i++) {
        layout[i].insert(layout[i].begin(), 'W');
        layout[i].push_back('W');
    }
}

void House::fixLine(std::vector<char>& line, bool firstOrLast) {
    // if it's an empty line replace it with ' ' line
    if (line.empty() || line[0] == '\r') {
        line = std::vector<char>(cols, ' ');
        return;
    }
    // if line.size() < cols add 'W' if  it's a only walls row or ' ' if not
    if (static_cast<int>(line.size()) < cols) {
        line.resize(cols, ' ');
    }
    // // if line.size() < cols reduce its size to cols
    if (static_cast<int>(line.size()) > cols) {
        line.resize(cols);
    }

    // Check each character and replace invalied char with ' '
    for (char& ch : line) {
        if (!(ch == 'W' || ch == 'D' || (ch >= '0' && ch <= '9') || ch == ' ')) {
            ch = ' ';
        }
    }
}



// getters implementations.
std::vector<std::vector<char>> House::getLayout() const{
    return layout;
}

int House::getMaxStepsAllowed() const{
    return maxSteps;
}

int House::getBatteryCapacity() const{
    return maxBattery;
}

int House::getBattery() const{
    return maxBattery;
}

int House::getRows() const{
    return rows;
}

int House::getCols() const{
    return cols;
}

int House::getXDocking() const{
    return docking_x;
}

int House::getYDocking() const{
    return docking_y;
}

int House::getCurrX() const{
    return curr_x;
}

int House::getCurrY() const{
    return curr_y;
}



// print function - Debugging
void House::printDocking() {
    std::cout << "Docking Station: Layout[" << docking_x << "][" << docking_y << "]" << std::endl;
}

void House::printline(std::vector<char> line) {
    for (char ch : line) {
        std::cout << ch << " ";
    }
    std::cout << std::endl;
}

void House::printLayout() {
    
    std::vector<std::vector<char>> layout = getLayout();
    for (const auto& line : layout) {
        for (char ch : line) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
}

void House::printTwoLayout(const std::vector<std::vector<char>> originalLayout) {
    
    std::cout << "Output file: ";
    int diff = layout[0].size();
    diff -= 13;
    while(diff > 0){  
        std::cout << " "; 
        diff--;
    }
    const std::string tabSpacing = "\t\t\t\t";
    std::cout << tabSpacing << "Input file:" << std::endl;
    
    std::vector<std::vector<char>> layout = getLayout();
    size_t maxRows = std::max(originalLayout.size(), layout.size());

    for (size_t i = 0; i < maxRows; ++i) {
        
        if (i < layout.size()) {
            for (char c : layout[i]) {
                std::cout << c;
            }
        }
        if(i >= layout.size()){
            for (int j = 0; j < layout[0].size(); j++) {
                std::cout << " ";
            }
        }
        std::cout << tabSpacing;
        
        if (i < originalLayout.size()) {
            for (char c : originalLayout[i]) {
                std::cout << c;
            }
        }
        std::cout << std::endl;
    }
}




#endif // SENSORS_H