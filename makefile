# Makefile for Vacuum Cleaner Simulation Project

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic -g
SOURCES = MyAlgorithm.cpp Graph.cpp Coordinates.cpp House.cpp MySimulator.cpp MyBatteryMeter.cpp MyDirtSensor.cpp MyWallSensor.cpp VacuumCleaner.cpp main.cpp
EXECUTABLE = myrobot

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean
