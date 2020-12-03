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

uint16_t Clock::getCurrentTimeInTicks(){
    return Clock::currentTime_;
}

void Clock::setStartTime(const char time[Time::TIME_SIZE]){
    Clock::startTime_ = convertTimeInTicks(time);
    Clock::stopTime_ = Clock::startTime_ - 1;
    if(Clock::stopTime_ > MAX_TIME)
        Clock::stopTime_ = MAX_TIME;

    setTime(Clock::startTime_);
}

void Clock::resetTime(){
    Clock::currentTime_ = MIN_TIME;
    *portPtr_ |=  (1 << resetPin_);
    *portPtr_ &= ~(1 << resetPin_);
    _delay_ms(3000);
}

void Clock::startClock(){
    Clock::isClockStopped_ = false;
    setTimerFrequency(TICK_PERIOD_1_S);
}

void Clock::stopClock(){
    isClockStopped_ = true;
}

void Clock::toggleClock(){
    isClockStopped_ = !isClockStopped_;
}

void Clock::updatePwmPin(){
    uint16_t tenBitVoltValue = Clock::clockCan_.lecture(Clock::voltPin_);
    double VOLT_TO_TICK_FACTOR = -9.925;
    double newOcr1A = VOLT_TO_TICK_FACTOR * tenBitVoltValue + TICK_PERIOD_1_S;
    if(newOcr1A < MINIMUM_TICK_PERIOD)
        newOcr1A = MINIMUM_TICK_PERIOD;
    OCR1A = (uint16_t) newOcr1A;
}


uint16_t Clock::convertTimeInTicks(const char time[5]){
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

void Clock::setTime(const char time[5]){
    resetTime();
    setTime(convertTimeInTicks(time));
}

void Clock::setTime(uint16_t ticks){
    resetTime();
    Clock::currentTime_ = ticks;

    for(uint16_t i = 0; i < Clock::currentTime_; i++){
        *portPtr_ |= (1 << pwmPin_);
        *portPtr_ &= ~(1 << pwmPin_);
    }
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
    #endif
    TIMSK1 |= (1 << OCIE1A);
    sei();
}

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
    *Clock::portPtrGlobal_ |= (1 << Clock::pwmPinGlobal_);
    *Clock::portPtrGlobal_ &= ~(1 << Clock::pwmPinGlobal_);
    Clock::currentTime_++;
    if(Clock::currentTime_ > Clock::MAX_TIME)
        Clock::currentTime_ = 0;
}
