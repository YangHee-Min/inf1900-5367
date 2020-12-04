#ifndef CLOCK_H
#define CLOCK_H

#include <avr/io.h>
#include "can.h"
#include "sonar.h"
#include "time.h"

class Clock
{
    public:
        Clock(volatile uint8_t* portPtr, 
                uint8_t pwmPin, 
                uint8_t resetPin, 
                uint8_t voltPin);
        uint16_t getCurrentTimeInTicks();
        void setStartTime(const char* time);
        void resetTime();
        void startClock();
        void stopClock();
        void toggleClock();
        static void updatePwmPin();

        static volatile uint16_t currentTime_;
        static uint16_t stopTime_;
        static uint16_t startTime_;
        static volatile uint8_t *portPtrGlobal_;
        static uint8_t pwmPinGlobal_ ;
        static volatile bool isClockStopped_;
        static can clockCan_;
        static Sonar clockSonar_;
        static uint8_t voltPin_;

        static const uint16_t MAX_TIME = 1439;
        static const uint16_t TICK_PERIOD_1_S = 7812;
        static const uint16_t MINIMUM_TICK_PERIOD = 100;
        
    private:
        void setTime(const char time[Time::TIME_SIZE]);
        void setTime(uint16_t ticks);
        void setTimerFrequency(uint16_t ticks);
    
        static const uint16_t MIN_TIME = 0;

        volatile uint8_t* portPtr_;
        uint8_t pwmPin_;
        uint8_t resetPin_;
};
#endif