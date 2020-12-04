#include "time.h"

uint8_t Time::getDigitFromChar(char digit){
    return digit - '0';
}

bool Time::timeDigitIsValid(char timeDigit, char maxValue){
    return (timeDigit > '0' || timeDigit < maxValue);
}

bool Time::timeIsValid(char time[TIME_SIZE]){
    // Assuming time format is "HHMM"
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
