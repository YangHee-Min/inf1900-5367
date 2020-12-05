/**********************************
* File: servomotor.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 27 2020
* Updated: November 27 2020
* Description: Definition of methods related to Servomotor.
***********************************/

#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H

#include <avr/io.h> 
#include <util/delay.h>



class Servomotor {

    public:
        //Constructor
        Servomotor(uint8_t pinServomotor, volatile uint8_t* portPtr);
        void changeAngle(double angle);
        static uint16_t getAngleFromString(char* angleString);

        static const uint8_t ANGLE_STRING_SIZE = 4;
        enum CONVERSION_FACTOR: uint8_t {
            TENS_FACTOR = 10,
            HUNDREDS_FACTOR = 100
        };

        enum angleIndex: uint8_t {
            HUNDREDS_INDEX,
            TENS_INDEX,
            UNIT_INDEX
        };

    private:
        double ANGLE_TO_MS_FACTOR = 1.1/180;
        double MINIMUM_MS_VALUE = 0.9;
       

        uint8_t pinServomotor_;
        volatile uint8_t* portPtr_;
        
};
#endif
