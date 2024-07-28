# Project Name: Vacuum Cleaner Simulation

## submitters
- Tomer Yihya
- Or Asheri

## Overview
This project simulates the operation of a robotic vacuum cleaner that navigates around the house in an intelligent way. The purpose of the simulation is to simulate and trace the actions of the robot during the house cleaning operation while taking into account its condition in terms of location and operation, the amount of dirt in the house and the battery limitations.

## File Structure
The project consists of the following files:

### Header Files
1. `abstract_algorithm.h` - Abstract class defining the interface for algorithms.
2. `battery_meter.h` - Interface for battery meter functionality.
3. `Coordinates.h` - Defines the `Coordinates` class to handle position data.
4. `dirt_sensor.h` - Interface for dirt sensor functionality.
5. `enums.h` - Enumerations used throughout the project.
6. `House.h` - Defines the `House` class, representing the environment.
7. `MyAlgorithm.h` - Implementation of the custom algorithm.
8. `MyBatteryMeter.h` - Implementation of the battery meter interface.
9. `MyDirtSensor.h` - Implementation of the dirt sensor interface.
10. `MySimulator.h` - Defines the simulator class.
11. `MyWallSensor.h` - Implementation of the wall sensor interface.
12. `wall_sensor.h` - Interface for wall sensor functionality.
13. `VacuumCleaner.h` - Defines the `VacuumCleaner` class.

### Source Files
1. `Coordinates.cpp` - Implementation of the `Coordinates` class.
2. `House.cpp` - Implementation of the `House` class.
3. `MyAlgorithm.cpp` - Implementation of the custom algorithm.
4. `MyBatteryMeter.cpp` - Implementation of the battery meter interface.
5. `MyDirtSensor.cpp` - Implementation of the dirt sensor interface.
6. `MySimulator.cpp` - Implementation of the simulator class.
7. `MyWallSensor.cpp` - Implementation of the wall sensor interface.
8. `VacuumCleaner.cpp` - Implementation of the `VacuumCleaner` class.
9. `main.cpp` - Main file to run the simulation.

## Project Statuses
- `WORKING` - The vacuum cleaner is still operating.
- `FINISH` - The vacuum cleaner has finished cleaning.
- `DEAD` - The vacuum cleaner is out of battery.

### Input and Output Files
1. `input.txt` - Example of an input file specifying house layout and simulation parameters.
2. `output_input.txt` - Example of an output file showing the results of the simulation.

## Error Handling
The program includes error handling to manage invalid input files, runtime errors, and unexpected conditions.
It ensures that the simulation can gracefully handle errors without abruptly crashing.

## How to Run the Simulation
1. Ensure you have `make` and `g++` installed on your system.
2. Compile the project using the make command:
   ```sh
   make
   ```
3. Run the executable, give an input file as an argument:
   ```sh
   ./myrobot input_file.txt
   ```

## Input File Format

The input file should contain the following information:
1. MaxSteps - The Maximum number of steps allowed.
2. MaxBattery - The battery capacity. 
3. Rows - The number of rows in the home representation.
4. Cols - The number of columns in the home representation.
5. House layout:
   each char represents a dirt level (`0-9`), a wall (`W`), or the docking station (`D` - must have one).

## Output File Format
The program generates an output file which has the following data:
1. NumSteps - The number of steps taken.
2. DirtLeft - Remaining Dirt.
3. Status - FINISHED, WORKING or DEAD.
4. All steps performed:
- 'S' for South
- 'N' for north
- 'E' to the east
- 'W' for West
- 's' to stay
- 'F' to finish

### Input File - example (`inputfile.txt`)
```
1-Small house
MaxSteps = 100
MaxBattery=20
Rows = 4
Cols =10
WWWW
W D
W 123456789
## Example
```
### Output File - example (`output_inputfile.txt`)
```
NumSteps = 100
DirtLeft = 15
Status = FINISHED
Steps:
SsEssEsssEssssNWWWssssssssssssssssssSEEEEsssssEsNWWWWWssssssssssssssssssSEEEEEsssssENWWWWWWsssssssss
```

