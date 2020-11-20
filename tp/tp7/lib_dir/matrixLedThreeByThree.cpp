/**********************************
* File: matrixLedThreeByThree.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 11 2020
* Description: Implementation of methods related to Matrix 3x3.
***********************************/

#include "./matrixLedThreeByThree.h"

//! Parametrized constructor. Creates an object by taking the initial orientation  
//! and a pointer to the parametrized port.
//! \param initialOrientation   Initial orientation of the robot.
//! \param portPtr              Pointer to the 3D matrix port.
MatrixLedThreeByThree::MatrixLedThreeByThree(int initialOrientation, volatile uint8_t* portPtr)
    : MatrixLed::MatrixLed(portPtr),
    currentDirection_(initialOrientation){
}

//! Function that changes the LED display when turning left.
void MatrixLedThreeByThree::turnLeft(){
    changeLedDirection(LEFT);
}

//! Function that changes the LED display when turning right.
void MatrixLedThreeByThree::turnRight(){
    changeLedDirection(RIGHT);
}

//! Function that changes the LED display based on the current direction.
//! \param turnDirection  Orientation of the turn.
void MatrixLedThreeByThree::changeLedDirection(int turnDirection){ 

    currentDirection_ += turnDirection;
    if(currentDirection_ == NORTH + LEFT)
        currentDirection_ = WEST;
    
    if(currentDirection_ == WEST + RIGHT)
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

//! Function that sets the direction of the LED based on the input direction.  
//! \param direction  New direction of the LED.
void MatrixLedThreeByThree::setDirection(int direction) {
    currentDirection_ = direction;
}
