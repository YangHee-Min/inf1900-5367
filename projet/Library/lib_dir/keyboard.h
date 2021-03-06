/**********************************
* File: keyboard.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 29 2020
* Updated: December 1 2020
* Description: Definition of methods related to keyboard.
***********************************/

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <avr/io.h> 
#include <util/delay.h>
#include "uart.h"

class Keyboard{
    public:
        // Constructor
        Keyboard(volatile uint8_t* portPtr, 
                    volatile uint8_t* pinPtr,
                    uint8_t demuxS1, 
                    uint8_t demuxS0, 
                    uint8_t muxS1, 
                    uint8_t muxS0,
                    uint8_t inputPin);

        // Functions
        bool buttonIsPressed(uint8_t button, volatile uint8_t& pinx);
        char readKey();
        
    private:
        // Function
        char readKeyboard();

        // Attributes
        int currentScoutedKeyValue_;
        volatile uint8_t* portPtr_;
        volatile uint8_t* pinPtr_;
        uint8_t demuxS1_;
        uint8_t demuxS0_;
        uint8_t muxS1_;
        uint8_t muxS0_;
        uint8_t inputPin_;
        Uart uart_;

        // Constants
        static const uint8_t PAST_END_OF_ENUM = 16;
        static const uint8_t INPUT_DELAY = 1;
        enum KeyboardValue: uint8_t{KEY_0 = 0b0000,
                                    KEY_4 = 0b0001, 
                                    KEY_8 = 0b0010,
                                    KEY_C = 0b0011,
                                    KEY_1 = 0b0100,
                                    KEY_5 = 0b0101,
                                    KEY_9 = 0b0110,
                                    KEY_D = 0b0111, 
                                    KEY_2 = 0b1000,
                                    KEY_6 = 0b1001, 
                                    KEY_A = 0b1010,
                                    KEY_E = 0b1011,
                                    KEY_3 = 0b1100,
                                    KEY_7 = 0b1101,
                                    KEY_B = 0b1110,
                                    KEY_F = 0b1111};
};
#endif