/**********************************
* File: led.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Implementation of methods related to LEDs.
***********************************/

#include "./matrixLedThreeByThree.h"

MatrixLedThreeByThree::MatrixLedThreeByThree(int currentDirection)
    :currentDirection_(currentDirection){
}

void MatrixLedThreeByThree::setDirection(int direction) {
    currentDirection_ = direction;
}

uint8_t MatrixLedThreeByThree::ledDirection(int turning){   
    enum {NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3};
    uint8_t NORTH_LED = 0b01000101;
    uint8_t EAST_LED = 0b00100011;
    uint8_t SOUTH_LED = 0b00010101;
    uint8_t WEST_LED = 0b00100110;

    currentDirection_ += turning;
    if(currentDirection_ == -1){
        currentDirection_ = WEST;
    }
    if(currentDirection_ == 4){
        currentDirection_ = NORTH;
    }
    
    uint8_t returnValue = NORTH;
    switch(currentDirection_){
        case NORTH:
            returnValue = NORTH_LED;
            break;

        case EAST:
            returnValue = EAST_LED;
            break;

        case SOUTH:
            returnValue = SOUTH_LED;
            break;

        case WEST:
            returnValue = WEST_LED;
    }
    return returnValue;
}