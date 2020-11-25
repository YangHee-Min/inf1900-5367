#include "sonar.h"

volatile bool Sonar::detectedObject_ = false;
volatile uint16_t Sonar::lastDistance_ = 0;

Sonar::Sonar()
    :portPtr_(&PORTD)
    ,trigPin_(PORTD5)
    ,echoPin_(INT0)
{
    initialisationISR();
    initialisationTrigPwm();
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

void Sonar::initialisationISR(){
    // Prevent any other isr
    cli ();
    
    // PORTD2 as input pin
    DDRD &= ~(1 << PORTD2); 

    // PORTD1 as ouput pin
    DDRD |= (1 << PORTD5);

    // activate INT0 pin
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00) | (1 << ISC01);
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
}

void Sonar::initialisationTrigPwm(){
    // Set timer to 0
    #ifndef TIMER_TCNT
    #define TIMER_TCNT
    TCNT1 = 0;

    // Clock division by 1024 with 10 bit timer
    // and clear on upcount match / set on downcount
    // match

    // Clock clear on upcount match / set on downcount
    // match. - 10 bit timer
    TCCR1A |= (1 << COM1A1);
    TCCR1A |= (1 << WGM10) | (1 << WGM11) | (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TCCR1C = 0;
    #endif

    OCR1A = 1;
}

int Sonar::obstaclesDetection(){
    while(!detectedObject_){
    }
    cli();
    detectedObject_ = false;
    sei();
    return lastDistance_;
    
}