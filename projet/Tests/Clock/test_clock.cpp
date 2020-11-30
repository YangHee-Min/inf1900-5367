#include "../../Library/lib_dir/clock.h"
#include "../../Library/lib_dir/uart.h"


void timeSetTest(Clock clock){
    const uint8_t TIME_SIZE = 5;
    char test1[TIME_SIZE] = "0024";
    char test2[TIME_SIZE] = "0242";
    char test3[TIME_SIZE] = "1222";
    char test4[TIME_SIZE] = "2351";

    clock.setTime(test1);
    _delay_ms(1000);
    clock.setTime(test2);
    _delay_ms(1000);
    clock.setTime(test3);
    _delay_ms(1000);
    clock.setTime(test4);
    _delay_ms(1000);
}

int main(){
    DDRD = 0xFF;
    Clock clock = Clock(&PORTD, PORTD4, PORTD6, PORTA0);
    char time[5] = "1222";
    clock.setTime(time);
    clock.setTimerFrequency((uint16_t) 7812);
    for(;;){
        OCR1A -=1;
        if(OCR1A <= 0)
            OCR1A = 7812;
        _delay_ms(2);
    }//}
}
// void partirMinuterie ( uint16_t duree ) {
//     cli();
//     // mode CTC du timer 1 avec horloge divisée par 1024
//     // interruption après la durée spécifiée
//     TCNT1 = 0;
//     OCR1A = duree;
//     OCR1B = duree/4;
//     TCCR1A = 0;
//     TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12);
//     TCCR1C = 0;
//     TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);
//     sei();
// }

// ISR ( TIMER1_COMPA_vect ) {
//     PORTD |= (1 << PORTD6);
//     PORTD &= ~(1 << PORTD6);
// }

// ISR ( TIMER1_COMPB_vect ) {
//     PORTD |= (1 << PORTD4);
//     PORTD &= ~(1 << PORTD4);
//     OCR1B += 1953;
//     if(OCR1B > 7812)
//         OCR1B = 1953;
// }

// int main(){
//     DDRD |= (1 << PORTD6) | (1 << PORTD4);


//     PORTD |= (1 << PORTD6);
//     PORTD &= ~(1 << PORTD6);
//     _delay_us(2);
//     // for(int i = 0; i < 1439; i++){
//     //     PORTD |= (1 << PORTD4);
//     //     PORTD &= ~(1 << PORTD4);
//     //     _delay_us(2);
//     // }

//     uint16_t duration = 7812;
//     partirMinuterie(duration);
//     //for(;;){}
//     for(;;){}
// }
