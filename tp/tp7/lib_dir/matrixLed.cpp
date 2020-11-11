#include "./matrixLed.h"

MatrixLed::MatrixLed(volatile uint8_t* portPtr)
    :portPtr_(portPtr){
}

void MatrixLed::turnOff(){
    *portPtr_ = OFF;
}

void MatrixLed::changeLed(uint8_t newLedValue){
    *portPtr_ = newLedValue;
}
