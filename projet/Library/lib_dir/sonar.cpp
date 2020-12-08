/**********************************
* File: sonar.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 22 2020
* Updated: November 26 2020
* Description: Implementation of methods related to sonar.
***********************************/

#include "sonar.h"
#include <avr/interrupt.h>
#include <util/delay.h>

volatile bool Sonar::detectedObject_ = false;

// Variable holding the last distance detected by the sonar.
volatile uint16_t Sonar::lastDistance_ = 0;

//! Default constructor of sonar that initializes
//! the port, the trig and echo pins.
Sonar::Sonar()
    :portPtr_(&PORTD)
    ,trigPin_(PORTD5)
    ,echoPin_(INT0)
{   
    DDRD |= (1<< trigPin_);
    DDRD &= ~(1 << INT0);
    initialisationISR();
}

//! ISR for the echo pin.
//! \param INT0   vector responsible for interrupt0
ISR ( INT0_vect ) {
    uint32_t counter = 0;
    while(PIND & (1 << PIND2)){
        counter++;
    }
    Sonar::lastDistance_ = counter;
    Sonar::detectedObject_ = true;
}

//! ISR for the trig pin to send out signals periodically.
//! \param TIMER1_COMPB_vect    vector responsible for timer1.
ISR ( TIMER1_COMPB_vect ) {
    PORTD ^= (1 << PORTD5);
    OCR1B += Sonar::TRIG_FREQUENCY;
    if(OCR1B > OCR1A)
        OCR1B = Sonar::TRIG_FREQUENCY;
}

//! Function that initializes registers for ISR 
//! and pins for sonar.
void Sonar::initialisationISR(){
    // Prevent any other isr
    cli ();
    #ifndef TIMER_ISR
    #define TIMER_ISR
    // mode CTC of timer 1 with 1024 prescaler
    TCNT1 = 0;
    TCCR1A = 0;
    TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12);
    TCCR1C = 0;
    #endif

    TIMSK1 |= (1 << OCIE1B);

    // PORTD2 as input pin
    DDRD &= ~(1 << echoPin_); 

    // PORTD1 as ouput pin
    DDRD |= (1 << trigPin_);

    // activate INT0 pin
    EIMSK |= (1 << echoPin_);
    EICRA |= (1 << ISC00) | (1 << ISC01);
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}

//! Function that returns distance of an object.
//! \return     Distance of the object from sonar.
uint16_t Sonar::obstacleDetection(){
    while(!detectedObject_){}
    cli();
    detectedObject_ = false;
    sei();
    return lastDistance_;
    
}