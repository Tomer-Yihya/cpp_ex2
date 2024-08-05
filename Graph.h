#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Coordinates.h"
#include "enums.h"

class Graph {

    private:
        std::vector<std::vector<char>> layout;
        Coordinates docking;
        Coordinates currLocation;


    public:
        Graph();
        void addNode(const Coordinates& coords, char value);
        void clean();
        void resize();
        void resizeN();
        void resizeS();
        void resizeW();
        void resizeE();
        bool updateLayout();
        bool updateNorthLayout();
        bool updateSouthLayout();
        bool updateWestLayout();
        bool updateEastLayout();

        Coordinates getDockingLocation() const;
        Coordinates getCurrLocation() const;
        char getVal(Coordinates coor) const;
        void setVal(Coordinates coor, char c);
        int getNumOfRows() const;
        int getNumOfCols() const;
        void move(Direction d);

        void printGraphStatus() const;
        void printGraph() const;
};

#endif // GRAPH_H
