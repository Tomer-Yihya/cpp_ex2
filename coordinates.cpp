#include "Coordinates.h"
#include <iostream>

Coordinates::Coordinates(int x, int y): xValue(x), yValue(y) {}

int Coordinates::getX() const {return xValue;}
int Coordinates::getY() const {return yValue;}

Coordinates Coordinates::getCoordinatesN() const{
    return Coordinates(xValue, yValue-1);
}

Coordinates Coordinates::getCoordinatesE() const{
    return Coordinates(xValue+1, yValue);
}

Coordinates Coordinates::getCoordinatesS() const{
    return Coordinates(xValue, yValue+1);
}

Coordinates Coordinates::getCoordinatesW() const{
    return Coordinates(xValue-1, yValue);
}


// equality operator
bool Coordinates::operator==(const Coordinates& other) const {
    return (xValue == other.getX() && yValue == other.getY());
}


