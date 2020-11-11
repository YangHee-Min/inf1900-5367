
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
    Motor leftMotor = Motor(&OCR1A, PORTD6);
    Motor rightMotor = Motor(&OCR1B, PORTD3);

    Led greenLed = Led(PORTA0, PORTA1, PORTA);
    Led redLed = Led(PORTA1, PORTA0, PORTA);

    MatrixLedFourByFour fourLedMatrix = MatrixLedFourByFour(&PORTC);
    MatrixLedThreeByThree threeLedMatrix = MatrixLedThreeByThree( MatrixLedThreeByThree::NORTH, &PORTB);



	FileReader fileReader = FileReader(&leftMotor, &rightMotor, &greenLed, &redLed, &threeLedMatrix, &fourLedMatrix);
    fileReader.sendFileToEeprom();
    fileReader.readFileFromEeprom();
}

int main(){
    initialisation();
    Uart uart; 
    readProgram();
    
}
