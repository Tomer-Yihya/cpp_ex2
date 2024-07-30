#include "Graph.h"
#include <iostream>
#include <algorithm>

Graph::Graph() : docking(2, 2), currLocation(2, 2) {
    layout.resize(5, std::vector<char>(5, '-'));
    layout[docking.getY()][docking.getX()] = 'D';
}


void Graph::addNode(const Coordinates& coords, char dirtLevel) {
    int x = coords.getX();
    int y = coords.getY();

    // It is not possible to add another docking station
    if(dirtLevel == 'D') {
        dirtLevel = ' ';
    }

    if(layout[y][x] > '0' && layout[y][x] <= '9') {
        return;
    }

    // Do not change the docking station
    if (x == docking.getX() && y == docking.getY()) {
        return;
    }

    if (x < 0 || x >= static_cast<int>(layout.size()) || y < 0 || y >= static_cast<int>(layout[0].size())) {
        resize();
        x = coords.getX() + 5;
        y = coords.getY() + 5;
    }
    layout[y][x] = dirtLevel;
}


void Graph::clean() {
    char dirtLevel = layout[currLocation.getY()][currLocation.getX()];
    if(dirtLevel > '0' && dirtLevel <= '9'){
        layout[currLocation.getY()][currLocation.getX()]--;
    }
    if(layout[currLocation.getY()][currLocation.getX()] == '0') {
        layout[currLocation.getY()][currLocation.getX()] = ' ';
    }
}


void Graph::resize() {
    int newSize = static_cast<int>(layout.size()) + 2;
    // Create new layout with larger size
    std::vector<std::vector<char>> newLayout(newSize, std::vector<char>(newSize, '-'));
    // Copy old layout to the center of the new layout
    int offset = 1;
    for (int i = 0; i < static_cast<int>(layout.size()); ++i) {
        for (int j = 0; j < static_cast<int>(layout[i].size()); ++j) {
            newLayout[i + offset][j + offset] = layout[i][j];
        }
    }
    // Update layout
    layout = newLayout;
    // Update docking and currLocation coordinates
    docking.setX(docking.getX() + offset);
    docking.setY(docking.getY() + offset);
    currLocation.setX(currLocation.getX() + offset);
    currLocation.setY(currLocation.getY() + offset);
}


void Graph::resizeN() {
    // Create new layout with an additional row
    int newSize = static_cast<int>(layout.size()) + 1;
    std::vector<std::vector<char>> newLayout(newSize, std::vector<char>(newSize, '-'));

    // Copy old layout to the lower part of the new layout
    for (int i = 0; i < static_cast<int>(layout.size()); ++i) {
        for (int j = 0; j < static_cast<int>(layout[i].size()); ++j) {
            newLayout[i + 1][j] = layout[i][j];
        }
    }

    // Update layout
    layout = newLayout;

    // Update docking and currLocation coordinates
    docking.setY(docking.getY() + 1);
    currLocation.setY(currLocation.getY() + 1);
}


void Graph::resizeS() {
    // Create new layout with an additional row
    int newSize = static_cast<int>(layout.size()) + 1;
    std::vector<std::vector<char>> newLayout(newSize, std::vector<char>(newSize, '-'));

    // Copy old layout to the new layout without changing its position
    for (int i = 0; i < static_cast<int>(layout.size()); ++i) {
        for (int j = 0; j < static_cast<int>(layout[i].size()); ++j) {
            newLayout[i][j] = layout[i][j];
        }
    }

    // Update layout
    layout = newLayout;
}


void Graph::resizeW() {
    // Create new layout with an additional column
    int newSize = static_cast<int>(layout.size()) + 1;
    std::vector<std::vector<char>> newLayout(newSize, std::vector<char>(newSize, '-'));

    // Copy old layout to the right part of the new layout
    for (int i = 0; i < static_cast<int>(layout.size()); ++i) {
        for (int j = 0; j < static_cast<int>(layout[i].size()); ++j) {
            newLayout[i][j + 1] = layout[i][j];
        }
    }

    // Update layout
    layout = newLayout;

    // Update docking and currLocation coordinates
    docking.setX(docking.getX() + 1);
    currLocation.setX(currLocation.getX() + 1);
}


void Graph::resizeE() {
    // Create new layout with an additional column
    int newSize = static_cast<int>(layout.size()) + 1;
    std::vector<std::vector<char>> newLayout(newSize, std::vector<char>(newSize, '-'));

    // Copy old layout to the new layout without changing its position
    for (int i = 0; i < static_cast<int>(layout.size()); ++i) {
        for (int j = 0; j < static_cast<int>(layout[i].size()); ++j) {
            newLayout[i][j] = layout[i][j];
        }
    }

    // Update layout
    layout = newLayout;
}






Coordinates Graph::getDockingLocation() const {
    return docking;
}


Coordinates Graph::getCurrLocation() const {
    return currLocation;
}


char Graph::getVal(Coordinates coor) const {
    return layout[coor.getY()][coor.getX()];
}


void Graph::setVal(Coordinates coor, char c) {
    layout[coor.getY()][coor.getX()] = c;
}


int Graph::getGraphSize() const {
    return static_cast<int>(layout.size());
}


void Graph::move(Direction d) { 
    
    switch (d) {
        case Direction::North:
            currLocation = currLocation.getCoordinatesN();
            break;
        case Direction::South:
            currLocation = currLocation.getCoordinatesS();
            break;
        case Direction::West:
            currLocation = currLocation.getCoordinatesW();
            break;
        case Direction::East:
            currLocation = currLocation.getCoordinatesE();
            break;
    }
    int x = currLocation.getX();
    int y = currLocation.getY();
    if (x < 0 || x >= static_cast<int>(layout.size()) || y < 0 || y >= static_cast<int>(layout[0].size())) {
        resize();
    }
}


void Graph::printGraph() const {
    std::cout << "docking station: layout[" << docking.getX() << "][" << docking.getY() << "]\n";
    std::cout << "currLocation: layout[" << currLocation.getX() << "][" << currLocation.getY() << "] = " << getVal(currLocation) << "\n";
    for (const auto &row : layout) {
        for (const auto &cell : row) {
            std::cout << cell << " ";
        }
        std::cout << '\n';
    }
    std::cout << "\n" << std::endl;
}
