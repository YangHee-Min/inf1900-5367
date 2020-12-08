/**********************************
* File: time.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 26 2020
* Updated: November 26 2020
* Description: Implementation of methods related to time.
***********************************/

#include "time.h"

//! Function that transforms char digit into int value.
//! \param      digit   Char digit to convert
//! \return     Int value of char digit.
uint8_t Time::getDigitFromChar(char digit){
    return digit - '0';
}

//! Function that asserts if the char digit respects 
//! lower limit and custom upper limit.
//! \param      timeDigit   Digit to assert.
//! \param      maxValue    Upper limit of digit
//! \return     true if digit is valid. False if not.
bool Time::timeDigitIsValid(char timeDigit, char maxValue){
    return (timeDigit >= '0' && timeDigit <= maxValue);
}

//! Function that asserts if the time is valid
//! according to "HHMM" format.
//! \param      time  time in char format according to "HHMM"
//! \return     true if time was valid. False if not.
bool Time::timeIsValid(char time[TIME_SIZE]){
    if(!timeDigitIsValid(time[0], '2'))
        return false;
    
    char maxHourDigit = '9';
    if(time[0] == '2')
        maxHourDigit = '4';
    
    if(!timeDigitIsValid(time[1], maxHourDigit))
        return false;
    
    if(!timeDigitIsValid(time[2], '5'))
        return false;
    
    if(!timeDigitIsValid(time[3], '9'))
        return false;
    
    return true;
}

//! Function that converts time in char format into number of 
//! ticks where each second is 1 tick.
//! \param      time time in char format according to "HHMM"
//! \return     Time in amount of ticks.
uint16_t Time::convertTimeInTicks(const char* time){
    const uint8_t TIME_SIZE = 5;
    const uint8_t DECADE_SCALE_FACTOR = 10;
    const uint8_t TIME_SCALE_FACTOR = 60;

    uint8_t timeInNumber[TIME_SIZE];
    for(int currentDigit = 0; currentDigit < TIME_SIZE - 1; currentDigit++){
        timeInNumber[currentDigit] = Time::getDigitFromChar(time[currentDigit]);
    }
    uint16_t returnValue = (timeInNumber[0] * DECADE_SCALE_FACTOR  + timeInNumber[1]) * TIME_SCALE_FACTOR + timeInNumber[2] * DECADE_SCALE_FACTOR + timeInNumber[3];
    if(returnValue > MAX_TIME)
        return MAX_TIME;
    
    return returnValue;
}
