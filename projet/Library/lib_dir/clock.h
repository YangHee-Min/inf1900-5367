/**********************************
* File: clock.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: December 2 2020
* Updated: December 5 2020
* Description: Definition of methods related to clock.
***********************************/

#ifndef CLOCK_H
#define CLOCK_H

#include <avr/io.h>
#include "can.h"
#include "sonar.h"
#include "time.h"

class Clock
{
    public:
        // Constructor
        Clock(volatile uint8_t* portPtr, 
                uint8_t pwmPin, 
                uint8_t resetPin, 
                uint8_t voltPin);

        // Functions
        uint16_t getCurrentTimeInTicks();
        void setStartTime(const char* time);
        void rewindToStartTime();
        void resetTime();
        void startClock();
        void stopClock();
        void toggleClock();
        static void updatePwmPin();

        // Attributes
        static volatile uint16_t currentTime_;
        static uint16_t stopTime_;
        static uint16_t startTime_;
        static volatile uint8_t *portPtrGlobal_;
        static uint8_t pwmPinGlobal_ ;
        static volatile bool isClockStopped_;
        static can clockCan_;
        static Sonar clockSonar_;
        static uint8_t voltPin_;

        // Constants
        static const uint16_t MAX_TIME = 1439;
        static const uint16_t TICK_PERIOD_1_S = 7812;
        static const uint16_t MINIMUM_TICK_PERIOD = 100;
        
    private:
        // Function
        void setTime(const char time[Time::TIME_SIZE]);
        void setTime(uint16_t ticks);
        void setTimerFrequency(uint16_t ticks);

        // Attributes
        volatile uint8_t* portPtr_;
        int8_t pwmPin_;
        uint8_t resetPin_;

        // Constants
        static const uint16_t MIN_TIME = 0;
        
};
#endif