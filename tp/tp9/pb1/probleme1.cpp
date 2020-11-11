/**********************************
* File: matrixLedFourByFour.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 3 2020
* Updated: November 11 2020
* Description: Receives a binary file by RS232 representing the 
*              list of actions to be performed by the hardware. 
*              Then stores it onto the eeprom and executes the 
*              instructions in order.
* Materials: 1 Atmega324pa, 1 3D LED matrix, 1 4D LED matrix, 
*            1 bi-color LED, 2 wheels and 1 H-Bridge, 
***********************************/
#define OUTPUT_PORT 0xFF

#include <avr/io.h>
#include <avr/eeprom.h> 
#include "../../tp7/lib_dir/debug.h"
#include "../../tp7/lib_dir/uart.h"
#include "../../tp7/lib_dir/fileReader.h"

void initialisation(){
    DDRA = OUTPUT_PORT; 
    DDRB = OUTPUT_PORT;
    DDRC = OUTPUT_PORT;
    DDRD = OUTPUT_PORT;
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
    readProgram();
    
}
