#ifndef COORDINATES_H
#define COORDINATES_H

class Coordinates
{
    private:
        int xValue;
        int yValue;

    public:
        // constructor
        Coordinates(int x=0, int y=0); // default constractor (0,0)
        
        // getters
        int getX() const;
        int getY() const;

        Coordinates getCoordinatesN() const;
        Coordinates getCoordinatesE() const;
        Coordinates getCoordinatesS() const;
        Coordinates getCoordinatesW() const;

        // equality operator
        bool operator==(const Coordinates& other) const;
};

#endif 

