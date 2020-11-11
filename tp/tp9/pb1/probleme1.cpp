
#include <avr/io.h>
#include <avr/eeprom.h> 
#include "../../tp7/lib_dir/debug.h"
#include "../../tp7/lib_dir/uart.h"
#include "../../tp7/lib_dir/fileReader.h"

void initialisation(){
    DDRA = 0xFF; // MODIFY
    DDRB = 0xFF;
    DDRC = 0xFF;
    DDRD = 0xFF;
}

void readProgram(){
    Motor leftMotor = Motor(&OCR1A, PORTD1);
    Motor rightMotor = Motor(&OCR1B, PORTD2);

    Led greenLed = Led(PORTA0, PORTA1, PORTA);
    Led redLed = Led(PORTA1, PORTA0, PORTA);

	FileReader fileReader = FileReader(&leftMotor, &rightMotor, &greenLed, &redLed);
    fileReader.readFile(PORTB, PORTC);
}

int main(){
    initialisation();
    
    Uart uart;
    uint16_t initialAddress = 0x0000;
    uint16_t word = uart.receiveWord(initialAddress);

    char ONE = (word >> 8);
    char TWO = ((word << 8) >> 8);
    char table[3] = {ONE, TWO};
    uart.write(table, 3);
    uart.write("end", 4);
}
