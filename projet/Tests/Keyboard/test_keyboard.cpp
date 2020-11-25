#include "keyboard.h"
#include "uart.h"

int main(){
    uint8_t demuxS1 = PORTA3;
    uint8_t demuxS0 = PORTA2;
    uint8_t muxS1 = PORTA1;
    uint8_t muxS0 = PORTA0;
    uint8_t inputPin = PORTA4;
    // 1 for write, 0 for read
    DDRA |=  (1 << PORTA3) | (1 << PORTA2) |(1 << PORTA1) |(1 << PORTA0);
    DDRA &= ~(1 << PORTA4);
    Keyboard keyboard = Keyboard(&PORTA, &PINA, demuxS1, demuxS0, muxS1, muxS0, inputPin);
    Uart uart = Uart();

    char message[7] = "start\n";
    uart.print(message, 7);
    for(;;){
        int readValue = keyboard.readKey();
        uart.transmission(readValue);
        while(PINA & (1 << PORTA4)){}
    }
}