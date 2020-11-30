#include "clock.h"

volatile uint16_t Clock::currentTime_ = 0;
volatile uint8_t* Clock::portPtrGlobal_ = &PORTD;
uint8_t Clock::pwmPinGlobal_ = PORTD4;

Clock::Clock(volatile uint8_t* portPtr, 
            uint8_t pwmPin, 
            uint8_t resetPin,
            uint8_t voltPin)
            :portPtr_(portPtr)
            ,pwmPin_(pwmPin)
            ,resetPin_(resetPin)
            ,voltPin_(voltPin)
{
    if(*portPtr_ != PORTD)
        portPtrGlobal_ = portPtr_;

    if(pwmPin_ != PORTD4)
        pwmPinGlobal_ = pwmPin_;
}

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
    TIMSK1 |= (1 << OCIE1A);
    #endif
    sei();
}

void Clock::setTime(char time[5]){
    resetTime();
    uint16_t timeInTicks = getTimeInTicks(time);

    for(uint16_t i = 0; i < timeInTicks; i++){
        *portPtr_ |= (1 << pwmPin_);
        *portPtr_ &= ~(1 << pwmPin_);
    }
}

void Clock::resetTime(){
    currentTime_ = 0;
    *portPtr_ |=  (1 << resetPin_);
    *portPtr_ &= ~(1 << resetPin_);
}

uint16_t Clock::getTimeInTicks(char time[5]){
    const uint8_t TIME_SIZE = 5;
    const uint8_t DECADE_SCALE_FACTOR = 10;
    const uint8_t TIME_SCALE_FACTOR = 60;

    uint8_t timeInNumber[TIME_SIZE];
    for(int currentDigit = 0; currentDigit < TIME_SIZE - 1; currentDigit++){
        timeInNumber[currentDigit] = getDigitFromChar(time[currentDigit]);
    }
    uint16_t returnValue = (timeInNumber[0] * DECADE_SCALE_FACTOR  + timeInNumber[1]) * TIME_SCALE_FACTOR + timeInNumber[2] * DECADE_SCALE_FACTOR + timeInNumber[3];
    if(returnValue > MAX_TIME)
        return MAX_TIME;
    
    return returnValue;
}

uint8_t Clock::getDigitFromChar(char digit){
    return digit - '0';
}

ISR ( TIMER1_COMPA_vect ) {
    *Clock::portPtrGlobal_ |= (1 << Clock::pwmPinGlobal_);
    *Clock::portPtrGlobal_ &= ~(1 << Clock::pwmPinGlobal_);
    Clock::currentTime_ +=1;
    if(Clock::currentTime_ > Clock::MAX_TIME)
        Clock::currentTime_ = 0;
}
