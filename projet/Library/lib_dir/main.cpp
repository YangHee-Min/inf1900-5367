#include "sonar.h"
#include "clock.h"
#include "keyboard.h"
#include "uart.h"
#include "servomotor.h"
#include "LEDBar.h"
#include "time.h"
#include <avr/io.h>


const uint8_t MINIMUM_ANGLE_VALUE = 0;
const uint8_t MAXIMUM_ANGLE_VALUE = 180;
const uint8_t ADDRESS_SIZE = 8;
const uint8_t INITIAL_ADDRESS = 0x0002;

const uint8_t INSTRUCTION_SIZE = 5;
const char[INSTRUCTION_SIZE] INVALID_INSTRUCTION = "XXXX";

enum instructionIndex:uint8_t{
    DEVICE_INDEX,
    STATE_INDEX_1, 
    STATE_INDEX_2,
    STATE_INDEX_3;
};

enum doorState{OPEN, CLOSE};
volatile uint8_t address = 0;
Uart uart;


Keyboard keyboardPortInit(uint8_t demuxS1, uint8_t demuxS0, uint8_t muxS1, uint8_t muxS0, uint8_t inputPin){
    DDRA |=  (1 << demuxS1) | (1 << demuxS0) |(1 << muxS1) |(1 << muxS0);
    DDRA &= ~(1 << inputPin);
    Keyboard keyboard = Keyboard(&PORTA, &PINA, demuxS1, demuxS0, muxS1, muxS0, inputPin);
    return keyboard;

}

void displayMenu(){
    uart.print("1- Définir l'heure de départ\n", 32);
    uart.print("2- Définir l'état d'un dispositif\n", 37);
    uart.print("3- Afficher les actions programmées\n", 38);
    uart.print("4- Programmer une action\n", 26); 
    uart.print("5- Supprimer une action programmée\n", 37)
    uart.print("6- Démarrer la simulation\n", 27);
}

void printInvalidMessage(){
    uart.print("Option invalide. Retour au menu principal...\n", 45);
}

bool validateMachineAction(const char* machineInstruction, Keyboard& keyboard){
     
    uart.print("Entrez l’identifiant d’un dispositif suivi de sa valeur de configuration. (A|B|C|D)(0|1) ou (E|F)(000-180)\n", 112);
    char deviceLetter = keyboard.readKey();
    machineInstruction[DEVICE_INDEX] = deviceLetter;

    switch(deviceLetter){
        case 'A':
        case 'B':
        case 'C':
        case 'D':
            
            char gateStateLetter = keyboard.readKey();
            uint8_t gateId = deviceLetter - 'A';

            uint8_t gateState = gateState - '0';

            if(gateState == close || gateState == open){
                machineInstruction[STATE_INDEX_2] = 'X';
                machineInstruction[STATE_INDEX_3] = 'X';
                return true;
            }
            else {
                return false;
            }
            break;
        case 'E':
        case 'F':
            char servoValue1 = keyboard.readKey();
            char servoValue2 = keyboard.readKey();
            char servoValue3 = keyboard.readKey();

            const uint8_t ANGLE_STRING_SIZE = 4;
            char 
            uint16_t angleValue = (hundredsValue + tensValue + unitsValue);

            if((angleValue >= MINIMUM_ANGLE_VALUE) && (angleValue <= MAXIMUM_ANGLE_VALUE))
                return true;
            
            return false;
        default: 
            return false;
    }
    return false;
}

void option1(Keyboard& keyboard, Clock& clock){
    uart.print("Entrez l’heure et les minutes de départ de la simulation. HHMM\n", 67);
    char decadeHours = keyboard.readKey();
    char unitHours = keyboard.readKey();
    char decadeMinutes = keyboard.readKey();
    char unitMinutes = keyboard.readKey();
    char time[TIME_SIZE] = {decadeHours, unitHours, decadeMinutes, unitMinutes};
    
    if(Time::timeIsValid(time)){
        clock.setTime(time);
    }
    else{
        printInvalidMessage();
    }
    
}

void option2(LEDBar& ledbar, Keyboard& keyboard, Servomotor& servomotorE, Servomotor& servomotorF){
    uart.print("Entrez l’identifiant d’un dispositif suivi de sa valeur de configuration. (A|B|C|D)(0|1) ou (E|F)(000-180)\n", 112);
    char deviceLetter = keyboard.readKey();
    char machineInstruction[INSTRUCTION_SIZE];
    if(validateMachineAction(machineInstruction, keyboard)){
        if(machineInstruction[DEVICE_INDEX] >= 'A' || machineInstruction[0] <= 'D'){
            if(machineInstruction[STATE_INDEX_1] == OPEN)
                ledbar.openDoor(machineInstruction[DEVICE_INDEX]);
            else if(machineInstruction[STATE_INDEX_1] == CLOSE)
                ledbar.closeDoor(machineInstruction[DEVICE_INDEX]);
        }
        else if(machineInstruction[DEVICE_INDEX] == 'E' || machineInstruction[DEVICE_INDEX == 'F']){
            char angleString[4] = {machineInstruction[STATE_INDEX_1], machineInstruction[STATE_INDEX_2], machineInstruction[STATE_INDEX_3]};
            uint16_t angle = Servomotor::getAngleFromString(angleString);
            
            switch(machineInstruction[DEVICE_INDEX]){
                case 'E': 
                    servomotorE.changeAngle(angle);
                    break;
                case 'F':
                    servomotorF.changeAngle(angle);
            }
        }
    }
    else{ // invalidate option
        printInvalidMessage();
    }
}

void option3(){
    const uint8_t SINGLE_CHAR_SIZE = 2;
    const uint8_t DECREMENT_VALUE = 1;
    if (address > INITIAL_ADDRESS){
        for(uint8_t addressIterator = INITIAL_ADDRESS; addressIterator != address; addressIterator += ADDRESS_SIZE){
            for(uint8_t i = 0; i < Time::TIME_SIZE - DECREMENT_VALUE; i++){
                char instruction = uart.readByteEeprom(addressIterator);
                uart.print(instruction, SINGLE_CHAR_SIZE);
            }

            uart.print("\0", SINGLE_CHAR_SIZE);            
            
            for(uint8_t j = 0; j < INSTRUCTION_SIZE - DECREMENT_VALUE; j++){
                char instruction = uart.readByteEeprom(addressIterator);
                if(instruction != 'X')
                    uart.print(instruction, SINGLE_CHAR_SIZE);
            }

            uart.print("\n", SINGLE_CHAR_SIZE);
        }
    }
    else {
        uart.print("Il n’y a aucune action programmée.\n", 39);
    }
}
void option4(Keyboard& keyboard){
    const uint8_t DECREMENT_VALUE = 1;
    uart.print("Entrez une action à programmer. HHMM (A|B|C|D)(0|1) ou (E|F)(000-180)\n", 71);
    char decadeHours = keyboard.readKey();
    char unitHours = keyboard.readKey();
    char decadeMinutes = keyboard.readKey();
    char unitMinutes = keyboard.readKey();
    

    char deviceLetter = keyboard.readKey();
    char machineInstruction[INSTRUCTION_SIZE];
    char time[TIME_SIZE] = {decadeHours, uintHours, decadeMinutes, unitMinutes};
    if(!(validateMachineAction(machineInstruction, keyboard)) || !(time::timeIsValid(time))){
        printInvalidMessage();
        return;
    }
    
    for (uint8_t i = 0; i < Time::TIME_SIZE - DECREMENT_VALUE; i++){
        Uart::saveByteEeprom(address + i, time[i]);
    }
    address += Time::TIME_SIZE - DECREMENT_VALUE;
    
    for (uint8_t j = 0; j < INSTRUCTION_SIZE - DECREMENT_VALUE; j++){
        Uart::saveByteEeprom(address + j, machineInstruction[j]);
    }
    address += INSTRUCTION_SIZE - DECREMENT_VALUE;
}

void option5(Keyboard& keyboard){
    uart.print("Entrez le numéro d’une action à supprimer\n", 47);
    char deletevalue1 = keyboard.readKey();
    char deletevalue2 = keyboard.readKey();

    const uint16_t COPY_START_ADDRESS = (Time::getDigitFromChar(deleteValue1) * Servomotor::TENS_FACTOR + Time::getDigitFromChar(deleteValue2)) * 8;
    
    const uint8_t SINGLE_CHAR_SIZE = 2;
    const uint8_t DECREMENT_VALUE = 1;
    if (address > INITIAL_ADDRESS){
        for(uint8_t addressIterator = COPY_START_ADDRESS; addressIterator < address + ADDRESS_SIZE; addressIterator += ADDRESS_SIZE){
            for(uint8_t i = 0; i < ADDRESS_SIZE; i++){
                char instruction = uart.readByteEeprom(addressIterator);
                uart.saveByteEeprom((uint16_t) (addressIterator - ADDRESS_SIZE), (uint8_t) instruction);
            }   
        }
        address -= ADDRESS_SIZE;
    }
}
void option6(Clock& clock){
    uart.print("Option simulation choisie. Début de la simulation...\n", 55);
    clock.setTimerFrequency((uint16_t) 7812);
}

int main(){
    
    Keyboard keyboard = keyboardPortInit(PORTA3, PORTA2, PORTA1, PORTA0, PORTA4);
    Clock clock = Clock(&PORTD, PORTD4, PORTD6, PORTA0);
    LEDBar ledbar = LEDBar(PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, &PORTC);
    Servomotor servomotorE = Servomotor(PORTA6, &PORTA);
    Servomotor servomotorF = Servomotor(PORTA7, &PORTA);

    for(;;){

        displayMenu();
        char optionKey = keyboard.readKey();
        
        switch(optionKey){
            case '1':
                option1(keyboard, clock);
                break;
            case '2':
                option2(ledbar, keyboard, servomotorE, servomotorF);
            case '3':
                option3();
            case '4':
                option4(keyboard);
            case '5':
                option5(keyboard);
            case '6':
                option6(clock);
            default:
                uart.print("Option invalide. Retour au menu principal...\n", 45);

        }
    }
}
