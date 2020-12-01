#include "../../Library/lib_dir/clock.h"
#include "../../Library/lib_dir/uart.h"
#include "../../Library/lib_dir/can.h"


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
    DDRD = 0xFE;
    DDRA &= ~(1 << PORTA0);

    Clock clock = Clock(&PORTD, PORTD4, PORTD6, PORTA0);
    clock.resetTime();
    clock.setTimerFrequency((uint16_t) 7812);
    
    for(;;){
    }
}
