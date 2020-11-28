/**********************************
* File: LEDBar.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 23 2020
* Updated: November 27 2020
* Description: Definition of methods related to LEDBARs.
***********************************/

#ifndef LED_BAR_H
#define LED_BAR_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h> 
#include <util/delay.h>
#include "debug.h"

class LEDBar {

    public:

        LEDBar(uint8_t SHC,
                uint8_t STC, 
                uint8_t DS, 
                uint8_t MR, 
                uint8_t OE, 
                volatile uint8_t* portPtr);

        void openDoor(uint8_t doorType);
        void closeDoor(uint8_t doorType);
        void displayState();
        uint32_t LEDState_;
    private:
        
        uint8_t SHC_;
        uint8_t STC_;
        uint8_t DS_;
        uint8_t MR_;
        uint8_t OE_;
        volatile uint8_t* portPtr_;
        
        static const uint8_t MAX_LED_BAR_POSITION = 8;
        static const uint8_t MIN_BIT_POSITION = 0;
        static const uint8_t MAX_BIT_POSITION = 32;

        enum Doors
        {
            doorA,
            doorB,
            doorC,
            doorD,
        };

};
#endif
