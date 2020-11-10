
#include <avr/io.h>
#include <avr/eeprom.h> 
#include "../../tp7/lib_dir/debug.h"
#include "../../tp7/lib_dir/uart.h"
#include "../../tp7/lib_dir/fileReader.h"


int main(){
    PORTA = 0xFF;
    PORTB = 0xFF;
    PORTC = 0xFF;
    PORTD = 0xFF;
	readFile(PORTA0, PORTA1, PORTA, PORTD1, PORTD2, PORTC, PORTB);
}
