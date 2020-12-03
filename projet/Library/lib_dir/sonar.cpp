#include "sonar.h"

volatile bool Sonar::detectedObject_ = false;
volatile uint16_t Sonar::lastDistance_ = 0;

Sonar::Sonar()
    :portPtr_(&PORTD)
    ,trigPin_(PORTD5)
    ,echoPin_(INT0)
{   
    DDRD |= (1<< trigPin_);
    DDRD &= ~(1 << INT0);
    initialisationISR();
    debug_ = Uart();
}

ISR ( INT0_vect ) {
    uint32_t counter = 0;
    while(PIND & (1 << PIND2)){
        counter++;
    }
    Sonar::lastDistance_ = counter;
    Sonar::detectedObject_ = true;
}

ISR ( TIMER1_COMPB_vect ) {
    PORTD ^= (1 << PORTD5);
    OCR1B += Sonar::TRIG_FREQUENCY;
    if(OCR1B > OCR1A)
        OCR1B = Sonar::TRIG_FREQUENCY;
}

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

uint16_t Sonar::obstacleDetection(){
    while(!detectedObject_){}
    cli();
    detectedObject_ = false;
    sei();
    return lastDistance_;
    
}