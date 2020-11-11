#ifndef MATRIXLEDFOURBYFOUR_H
#define MATRIXLEDFOURBYFOUR_H


#include "./matrixLed.h"

class MatrixLedFourByFour : public MatrixLed{
    public:
        MatrixLedFourByFour(volatile uint8_t* portPtr);
};
#endif