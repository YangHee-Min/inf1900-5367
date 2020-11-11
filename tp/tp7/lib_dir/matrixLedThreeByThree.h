/**********************************
* File: MatrixLedThreeByThree.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 1 2020
* Description: Definition of methods related to Matrix LED 3x3.
***********************************/

#ifndef MATRIXLEDTHREEBYTHREE_H
#define MATRIXLEDTHREEBYTHREE_H

#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>


class MatrixLedThreeByThree {
    public:
        MatrixLedThreeByThree(int currentDirection);
        void setDirection(int direction);
        uint8_t ledDirection(int turning);
    private:
		int currentDirection_;
};
#endif