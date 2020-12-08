/**********************************
* File: clock.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: December 2 2020
* Updated: December 5 2020
* Description: Implementation of methods related to clock.
***********************************/

#include <avr/interrupt.h>
#include <util/delay.h> 
#include "clock.h"


volatile uint16_t Clock::currentTime_ = 0;
uint16_t Clock::stopTime_ = 0;
uint16_t Clock::startTime_ = 0;
volatile uint8_t* Clock::portPtrGlobal_ = &PORTD;
uint8_t Clock::pwmPinGlobal_ = PORTD4;
volatile bool Clock::isClockStopped_ = false;
can Clock::clockCan_;
Sonar Clock::clockSonar_;
uint8_t Clock::voltPin_ = PORTA0;

//! Constructor by parameters of Clock 
//! \param portPtr  Pointer to the port (PORTX) on the atmega 
//!                 to which clock is connected
//! \param pwmPin   Pin which generates the pwm
//! \param resetPin Pin that resets the clock
//! \param voltPin  Pin that controls the speed of the clock 
//!                 linked to the variable voltage source.
Clock::Clock(volatile uint8_t* portPtr, 
            uint8_t pwmPin, 
            uint8_t resetPin,
            uint8_t voltPin)
            :portPtr_(portPtr)
            ,pwmPin_(pwmPin)
            ,resetPin_(resetPin)
{
    if(*portPtr_ != PORTD)
        portPtrGlobal_ = portPtr_;

    if(pwmPin_ != PORTD4)
        pwmPinGlobal_ = pwmPin_;

    if(voltPin_ != PORTA0)
        voltPin_ = voltPin;

    DDRA &= ~(1 << voltPin_);
    DDRD |= (1 << pwmPin_) | (1 << resetPin_);
}

//! Gets the current time on the clock
//! \return  Returns the current time 
uint16_t Clock::getCurrentTimeInTicks(){
    return Clock::currentTime_;
}

//! Sets the initial time on the clock
//! \param time  Pointer to a char of the format HHMM which indicates hours and minutes 
void Clock::setStartTime(const char* time){
    Clock::startTime_ = Time::convertTimeInTicks(time);
    Clock::stopTime_ = Clock::startTime_ - 1;
    if(Clock::stopTime_ > MAX_TIME)
        Clock::stopTime_ = MAX_TIME;

    setTime(Clock::startTime_);
}

//! Resets the time to the initial time set by the user using setStartTime()
void Clock::rewindToStartTime(){
    setTime(startTime_);
}

//! Resets the time to zero
void Clock::resetTime(){
    Clock::currentTime_ = MIN_TIME;
    *portPtr_ |=  (1 << resetPin_);
    _delay_ms(1);
    *portPtr_ &= ~(1 << resetPin_);
}

//! Starts the clock
void Clock::startClock(){
    Clock::isClockStopped_ = false;
    setTimerFrequency(TICK_PERIOD_1_S);
}

//! Stops the clock
void Clock::stopClock(){
    isClockStopped_ = true;
}

//! Pauses the clock if the clock is running, 
//! starts the clock if the clock is paused
void Clock::toggleClock(){
    isClockStopped_ = !isClockStopped_;
}

//! Accelerates or slows the clock speed depending on the output of voltage
void Clock::updatePwmPin(){
    uint16_t tenBitVoltValue = Clock::clockCan_.lecture(Clock::voltPin_);
    double VOLT_TO_TICK_FACTOR = -9.925;
    double newOcr1A = VOLT_TO_TICK_FACTOR * tenBitVoltValue + TICK_PERIOD_1_S;
    if(newOcr1A < MINIMUM_TICK_PERIOD)
        newOcr1A = MINIMUM_TICK_PERIOD;
    uint16_t newOcr1a16Bit = newOcr1A;
    OCR1A = newOcr1a16Bit;
}

//! Changes the current time on the clock
//! \param time  Array of char of the format HHMM which indicates hours and minutes
void Clock::setTime(const char time[5]){
    resetTime();
    setTime(Time::convertTimeInTicks(time));
}

//! Changes the current time on the clock
//! \param ticks  Time in number of minutes
void Clock::setTime(uint16_t ticks){
    resetTime();
    Clock::currentTime_ = ticks;
    _delay_ms(5);
    for(uint16_t i = 0; i < Clock::currentTime_; i++){
        *portPtr_ |= (1 << pwmPin_);
        *portPtr_ &= ~(1 << pwmPin_);
    }
}

//! Sets the frenquency of the timer
//! \param ticks  Time in number of minutes
void Clock::setTimerFrequency ( uint16_t ticks ) {
    cli();
    OCR1A = ticks;
    #ifndef TIMER_ISR
    #define TIMER_ISR
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0;
    TCCR1A = 0;
    TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12);
    TCCR1C = 0;
    #endif
    TIMSK1 |= (1 << OCIE1A);
    sei();
}

//! Does not increment clock display by 1 minute if:
//!     1. sonar detects an obstacle under two meters from it
//!     2. clock is supposed to be stopped
//!     3. Interrupts when current time on the clock reaches 
//!        one minute before stop time.
ISR ( TIMER1_COMPA_vect ) {
    if(Clock::clockSonar_.lastDistance_ < Sonar::TWO_METER_TICK_VALUE){
        return;
    }
    if(Clock::isClockStopped_)
        return;
    
    if(Clock::currentTime_ == Clock::stopTime_){
        Clock::isClockStopped_ = true;
        return;
    }
    
    Clock::updatePwmPin();

    // Increment clock display by 1 minute
    *Clock::portPtrGlobal_ |= (1 << Clock::pwmPinGlobal_);
    *Clock::portPtrGlobal_ &= ~(1 << Clock::pwmPinGlobal_);
    
    Clock::currentTime_++;
    if(Clock::currentTime_ > Clock::MAX_TIME)
        Clock::currentTime_ = 0;
}
