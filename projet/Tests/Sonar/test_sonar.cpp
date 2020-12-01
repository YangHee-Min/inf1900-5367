#define CLOCK 1
#include "../../Library/lib_dir/sonar.h"
#include "../../Library/lib_dir/clock.h"

int main(){
    DDRD |= (1 << PORTD0) | (1 << PORTD1) | (1 << PORTD4) | (1 << PORTD6);
    Uart uart;
    
    #if CLOCK == 0
    OCR1A = 7812;
    Sonar sonar = Sonar();
    uint16_t distance = 0;
    #endif

    #if CLOCK == 1
    DDRA &= ~(1 << PORTA0);
    Clock clock = Clock(&PORTD, PORTD4, PORTD6, PORTA0);
    clock.resetTime();
    clock.setTimerFrequency((uint16_t) 7812);
    #endif 

    #if CLOCK == 0
    for(;;){
        distance = sonar.obstaclesDetection();
        //uart.print("dist\n", 6);
        // 6634 is 1 meter
        const uint16_t TWO_METER_MARK = 13278;

        // Green
        if(distance >= TWO_METER_MARK){
            PORTD |= (1 << PORTD1);
            PORTD &= ~(1 << PORTD0);
        }
        // Red
        else if(distance < TWO_METER_MARK){
            PORTD |= (1 << PORTD0);
            PORTD &= ~(1 << PORTD1);
        }
    }
    #endif
    #if CLOCK == 1
    for(;;){
        uart.print("running...\n", 12);
    }
    #endif
}