#ifndef CLOCK_H
#define CLOCK_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "uart.h"
#include "can.h"
#include "sonar.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> 

class Clock
{
    public:
        Clock(volatile uint8_t* portPtr, 
                uint8_t pwmPin, 
                uint8_t resetPin, 
                uint8_t voltPin);
        void setTimerFrequency(uint16_t ticks);
        void setTime(char time[5]);
        void resetTime();
        static void updatePwmPin();

        static volatile uint16_t currentTime_;
        static volatile uint8_t *portPtrGlobal_;
        static uint8_t pwmPinGlobal_ ;
        static can clockCan_;
        static Sonar clockSonar_;
        static uint8_t voltPin_;

        static const uint16_t MAX_TIME = 1439;
        static const uint16_t TICK_PERIOD_1_S = 7812;

    private:
        uint16_t getTimeInTicks(char time[5]);
        uint8_t getDigitFromChar(char digit);

    
        static const uint16_t MIN_TIME = 0;

        volatile uint8_t* portPtr_;
        uint8_t pwmPin_;
        uint8_t resetPin_;
};
#endif