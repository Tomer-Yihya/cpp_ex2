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
        void printGraph() const;
        void resizeN();
        void resizeS();
        void resizeW();
        void resizeE();


        Coordinates getDockingLocation() const;
        Coordinates getCurrLocation() const;
        char getVal(Coordinates coor) const;
        void setVal(Coordinates coor, char c);
        int getGraphSize() const;
        void move(Direction d);
};

#endif // GRAPH_H
