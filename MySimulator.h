#ifndef MYSIMULATOR_H
#define MYSIMULATOR_H

#include "House.h"
#include "MyAlgorithm.h"
#include "Sensors.h"

class MySimulator {
    
    private:
        House house;
        MyAlgorithm* algorithm;
        // Other attributes and methods for simulation
    

    public:
        bool readHouseFile(const std::string& houseFilePath);
        void setAlgorithm(MyAlgorithm& algo);
        void run();

};

#endif // MYSIMULATOR_H
