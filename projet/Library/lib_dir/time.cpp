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