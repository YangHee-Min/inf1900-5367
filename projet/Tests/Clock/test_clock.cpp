#include "../../Library/lib_dir/clock.h"
#include "../../Library/lib_dir/uart.h"
#include "../../Library/lib_dir/can.h"


int main(){
    Uart uart;

    Clock clock = Clock(&PORTD, PORTD4, PORTD6, PORTA0);
    clock.setStartTime("0001");
    clock.startClock();
    //uart.print("Starting clock...\n", 19);
    //clock.startClock();
    for(;;){
        
    }
}//a