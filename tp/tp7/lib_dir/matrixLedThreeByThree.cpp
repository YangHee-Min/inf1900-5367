/**********************************
* File: led.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Implementation of methods related to LEDs.
***********************************/

#include "./matrixLedThreeByThree.h"

MatrixLedThreeByThree::MatrixLedThreeByThree(int initialDirection, volatile uint8_t* portPtr)
    : MatrixLed::MatrixLed(portPtr),
    currentDirection_(initialDirection){
}

void MatrixLedThreeByThree::turnLeft(){
    changeLedDirection(LEFT);
}

void MatrixLedThreeByThree::turnRight(){
    changeLedDirection(RIGHT);
}

void MatrixLedThreeByThree::changeLedDirection(int direction){ 

    currentDirection_ += direction;
    if(currentDirection_ == -1)
        currentDirection_ = WEST;
    
    if(currentDirection_ == 4)
        currentDirection_ = NORTH;
    
    switch(currentDirection_){
        case NORTH:
            changeLed(NORTH_LED);
            break;

        case EAST:
            changeLed(EAST_LED);
            break;

        case SOUTH:
            changeLed(SOUTH_LED);
            break;

        case WEST:
            changeLed(WEST_LED);
    }
    
}

void MatrixLedThreeByThree::setDirection(int direction) {
    currentDirection_ = direction;
}