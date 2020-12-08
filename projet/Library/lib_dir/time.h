/**********************************
* File: time.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 26 2020
* Updated: November 26 2020
* Description: Definition of methods related to time.
***********************************/

#ifndef TIME_H
#define TIME_H

#include <avr/io.h>

class Time{
    public:
        // Constants
        static const uint8_t TENS_FACTOR = 10;
        static const uint8_t TIME_SIZE = 5;
        static const uint16_t MAX_TIME = 1439;
        
        // Functions
        static uint8_t getDigitFromChar(char digit);
        static bool timeDigitIsValid(char timeDigit, char maxValue);
        static bool timeIsValid(char time[TIME_SIZE]);
        static uint16_t convertTimeInTicks(const char* time);

    private:
        // Protection against copy
        Time(){}
};
#endif
