/**********************************
* File: matrixLedThreeByThree.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 11 2020
* Description: Definition of methods related to Matrix LED 3x3.
***********************************/

#ifndef MATRIXLEDTHREEBYTHREE_H
#define MATRIXLEDTHREEBYTHREE_H

#include "matrixLed.h"


class MatrixLedThreeByThree : public MatrixLed {
    public:
        // Constructor
        MatrixLedThreeByThree(int initialOrientation, volatile uint8_t* portPtr);
        
        // Functions
        void turnLeft();
        void turnRight();

        // Constants
        enum CardinalDirection {    NORTH, 
                                    EAST, 
                                    SOUTH, 
                                    WEST};

    private:
        // Attributes
		int currentDirection_;

        // Functions
        void changeLedDirection(int turnDirection);
        void setDirection(int direction);

        // Constants
        enum LedDirectionValues: uint8_t{   NORTH_LED = 0b01000101,
                                            EAST_LED = 0b00100011,
                                            SOUTH_LED = 0b00010101, 
                                            WEST_LED = 0b00100110};
        enum Direction{ LEFT = -1, 
                        RIGHT = 1};
};
#endif
