#ifndef HOUSE_H
#define HOUSE_H

#include <vector>
#include <string>
#include <iostream>
#include "Coordinates.h"



class House {

    private:
        
        std::string fileName;
        int maxSteps;
        int maxBattery;
        int battery;
        int rows;
        int cols;
        int totalDirt;
        Coordinates DockingStation;
        Coordinates CurrLocation;
        std::vector<std::vector<char>> layout;

        // helping functions
        bool checkParameter(const std::string line, const std::string paramName, int& param);
        void cutExtraWalls();
        void addWalls();
        void fixLine(std::vector<char>& line, bool firstOrLast);


    public:

        // construnctor
        House (const std::string& file_path);
        
        // functions
        bool loadFromFile(const std::string& file_path);
        
        // getters functions
        std::vector<std::vector<char>> getLayout() const;
        int getMaxStepsAllowed() const;
        int getBatteryCapacity() const;
        int getBattery() const;
        int getRows() const;
        int getCols() const;
        Coordinates getDockingCoordinates() const;
        Coordinates getCurrLocation() const;
        char getLayoutVal(int x, int y) const;
        
        // print function - Debugging
        void printDocking();
        void printline(std::vector<char> line);
        void printLayout();
        void printTwoLayout(std::vector<std::vector<char>> originalLayout);

};

#endif // HOUSE_H
