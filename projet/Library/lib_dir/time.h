#ifndef TIME_H
#define TIME_H

#include <avr/io.h>

class Time{
    public:
        static const uint8_t TIME_SIZE = 5;

        static uint8_t getDigitFromChar(char digit);

        static bool timeDigitIsValid(char timeDigit, 
                                    char maxValue);

        static bool timeIsValid(char time[TIME_SIZE]);

        static uint16_t convertTimeInTicks(const char* time);

        static const uint8_t TENS_FACTOR = 10;

        static const uint16_t MAX_TIME = 1439;
};
#endif
