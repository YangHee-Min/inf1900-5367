#define CLOCK 1
#include "../../Library/lib_dir/sonar.h"
#include "../../Library/lib_dir/clock.h"

int main(){
    Uart uart;
    
    #if CLOCK == 0
    OCR1A = 7812;
    Sonar sonar = Sonar();
    uint16_t distance = 0;
    #endif

    #if CLOCK == 1
    Clock clock = Clock(&PORTD, PORTD4, PORTD6, PORTA0);
    clock.setStartTime("0325");
    uart.print("Go!\n", 5);
    clock.startClock();
    Sonar sonar = Sonar();
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
    _delay_ms(3000);
    uart.print("STOP\n", 6);
    clock.stopClock();
    _delay_ms(3000);
    uart.print("START\n", 7);
    clock.toggleClock();
    for(;;){
        uart.print("running...\n", 12);
    }
    #endif//
}