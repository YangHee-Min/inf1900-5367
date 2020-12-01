#include <avr/io.h>

class Time{
    public:
        static const uint8_t TIME_SIZE = 5;

        static uint8_t getDigitFromChar(char digit);

        static bool timeDigitIsValid(char timeDigit, 
                                    char maxValue);

        static bool timeIsValid(char time[TIME_SIZE]);
};