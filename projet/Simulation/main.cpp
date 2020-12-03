#include "../Library/lib_dir/sonar.h"
#include "../Library/lib_dir/clock.h"
#include "../Library/lib_dir/keyboard.h"
#include "../Library/lib_dir/uart.h"
#include "../Library/lib_dir/servomotor.h"
#include "../Library/lib_dir/LEDBar.h"
#include "../Library/lib_dir/time.h"
#include "../Library/lib_dir/eeprom.h"
#include <avr/io.h>
#include <avr/interrupt.h>

const uint8_t MINIMUM_ANGLE_VALUE = 0;
const uint8_t MAXIMUM_ANGLE_VALUE = 180;
const uint8_t ADDRESS_SIZE = 8;
const uint8_t INITIAL_ADDRESS = 0x0000;
volatile bool isRunning = true;

const uint8_t INSTRUCTION_SIZE = 5;

enum instructionIndex:uint8_t{
    DEVICE_INDEX,
    STATE_INDEX_1, 
    STATE_INDEX_2,
    STATE_INDEX_3
};

enum doorState{OPEN, CLOSE};
enum doorStateChar{OPEN_CHAR = '0', CLOSE_CHAR = '1'};
Uart uart;

//a
void displayMenu(){
    uart.print("\n", 2);
    uart.print("1- Définir l'heure de départ\n", 32);
    uart.print("2- Définir l'état d'un dispositif\n", 37);
    uart.print("3- Afficher les actions programmées\n", 38);
    uart.print("4- Programmer une action\n", 26); 
    uart.print("5- Supprimer une action programmée\n", 37);
    uart.print("6- Démarrer la simulation\n", 27);
}

void printInvalidMessage(){
    uart.print("\nOption invalide. Retour au menu principal...\n", 46);
}

void initialisationISR(){
    cli ();
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC11);
    sei ();

}

ISR(INT1_vect){
    isRunning = false;
}

bool validateMachineAction(char* machineInstruction, Keyboard& keyboard){
    //uart.print("Entrez l’identifiant d’un dispositif suivi de sa valeur de configuration. (A|B|C|D)(0|1) ou (E|F)(000-180)\n", 112);
    char deviceLetter = keyboard.readKey();
    machineInstruction[DEVICE_INDEX] = deviceLetter;

    switch(deviceLetter){
        case 'A':
        case 'B':
        case 'C':
        case 'D':{
            char gateStateLetter = keyboard.readKey();

            uint8_t gateState = gateStateLetter - '0';

            if(gateState == CLOSE || gateState == OPEN){
                machineInstruction[STATE_INDEX_1] = gateStateLetter;
                machineInstruction[STATE_INDEX_2] = 'X';
                machineInstruction[STATE_INDEX_3] = 'X';
                return true;
            }
            else {
                return false;
            }
            break;
        }
        case 'E':
        case 'F':{
            char servoValue1 = keyboard.readKey();
            char servoValue2 = keyboard.readKey();
            char servoValue3 = keyboard.readKey();

            const uint8_t ANGLE_STRING_SIZE = 4;
            char servoValues[ANGLE_STRING_SIZE] = {servoValue1, servoValue2, servoValue3};
            uint16_t angleValue = Servomotor::getAngleFromString(servoValues);

            if((angleValue >= MINIMUM_ANGLE_VALUE) && (angleValue <= MAXIMUM_ANGLE_VALUE)){
                machineInstruction[STATE_INDEX_1] = servoValue1;
                machineInstruction[STATE_INDEX_2] = servoValue2;
                machineInstruction[STATE_INDEX_3] = servoValue3;
                return true;
            }
            
            return false;
        }
        default: 
            return false;
    }
    return false;
}

void option1(Keyboard& keyboard, Clock& clock){
    uart.print("\nEntrez l’heure et les minutes de départ de la simulation. HHMM\n", 68);
    char decadeHours = keyboard.readKey();
    char unitHours = keyboard.readKey();
    char decadeMinutes = keyboard.readKey();
    char unitMinutes = keyboard.readKey();
    char time[Time::TIME_SIZE] = {decadeHours, unitHours, decadeMinutes, unitMinutes};
    
    if(Time::timeIsValid(time)){
        clock.setStartTime(time);
    }
    else{
        printInvalidMessage();
    }
    
}

void option2(LEDBar& ledbar, Keyboard& keyboard, Servomotor& servomotorE, Servomotor& servomotorF){
    uart.print("\nEntrez l’identifiant d’un dispositif suivi de sa valeur de configuration. (A|B|C|D)(0|1) ou (E|F)(000-180)\n", 113);
    char machineInstruction[INSTRUCTION_SIZE];
    if(validateMachineAction(machineInstruction, keyboard)){
        if(machineInstruction[DEVICE_INDEX] >= 'A' && machineInstruction[0] <= 'D'){
            uint8_t door = machineInstruction[DEVICE_INDEX] - 'A';
            if(machineInstruction[STATE_INDEX_1] == OPEN_CHAR)
                ledbar.openDoor(door);
            else if(machineInstruction[STATE_INDEX_1] == CLOSE_CHAR)
                ledbar.closeDoor(door);
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
    else{ 
        printInvalidMessage();
    }
}

void option3(){
    uart.print("\nAffichage des actions programmées:\n", 37);
    Eeprom::printInstructions();
}

void option4(Keyboard& keyboard){
    uart.print("\nEntrez une action à programmer. HHMM (A|B|C|D)(0|1) ou (E|F)(000-180)\n", 72);
    char decadeHours = keyboard.readKey();
    char unitHours = keyboard.readKey();
    char decadeMinutes = keyboard.readKey();
    char unitMinutes = keyboard.readKey();
    
    char machineInstruction[Eeprom::INSTRUCTION_SIZE_ARRAY];
    char time[Time::TIME_SIZE] = {decadeHours, unitHours, decadeMinutes, unitMinutes};
    if(!(validateMachineAction(machineInstruction, keyboard)) || !(Time::timeIsValid(time))){
        printInvalidMessage();
        return;
    }
    
    Eeprom::addInstruction(time, machineInstruction);
}

void option5(Keyboard& keyboard){
    uart.print("Entrez le numéro d’une action à supprimer\n", 47);
    char deleteValue1 = keyboard.readKey();
    char deleteValue2 = keyboard.readKey();

    Eeprom::deleteInstruction(deleteValue1, deleteValue2);//
}

/*
H|H|M|M|G|X|X|X|
Assumptions: 
    - All actions are programmed in chronological order
Logic: 
    - If the instruction time hasn't been reached yet:
        - If Clock::isClockRunning_ = false:
            - Clock is finished. Any actions later than current time will not be executed.
        - else:
            - Clock is still running. Actions programmed for later might be executed.

*/
void option6(Clock& clock, LEDBar& ledbar, Servomotor& servomotorE, Servomotor& servomotorF){
    
    uart.print("Option simulation choisie. Début de la simulation...\n", 55);
    clock.startClock();
    initialisationISR();
    uint8_t addressIterator = INITIAL_ADDRESS;
    char time[Time::TIME_SIZE];
    while(isRunning){
        // TODO
        for(;addressIterator <= address; addressIterator += INSTRUCTION_SIZE){
            for(uint8_t i = 0; i < Time::TIME_SIZE - 1; i++, addressIterator++){
                time[i] = uart.readByteEeprom(addressIterator);
            }
            if(Clock::convertTimeInTicks(time) >= clock.getCurrentTimeInTicks()){
                char instruction[INSTRUCTION_SIZE];
                for(uint8_t i = 0; i < INSTRUCTION_SIZE; i++, addressIterator++){
                    instruction[i] = uart.readByteEeprom(addressIterator);
                }
                uint8_t door;
                switch(instruction[0]){
                    case 'A':
                        door = LEDBar::DOOR_A;
                        instruction[0] = 'G';
                    case 'B':
                        door = LEDBar::DOOR_B;
                        instruction[0] = 'G';
                    case 'C':
                        door = LEDBar::DOOR_C;
                        instruction[0] = 'G';
                    case 'D':
                        door = LEDBar::DOOR_D;
                        instruction[0] = 'G';
                    case 'G':
                        switch(instruction[1]){
                            case CLOSE_CHAR:
                                ledbar.closeDoor(door);
                                break;
                            case OPEN_CHAR:
                                ledbar.openDoor(door);
                        }
                        break;
                    case 'E':
                        servomotorE.changeAngle(Servomotor::getAngleFromString(&instruction[1]));
                        break;

                    case 'F':
                        servomotorF.changeAngle(Servomotor::getAngleFromString(&instruction[1]));
                }
            }
        }
        // If time matches, run instruction
            // increment ur address to get machine instruction one by one

            // Make switch case depending on machine instruction.
            // NOTE: instructions have already been validated during instruciton addition

        // If not, pass

        // Checks if 24 hour limit passed
            // If so stop clock
    }
    clock.stopClock();
    isRunning = true;
    uart.print("Simulation terminée. Retour au menu principal...\n", 50);
}

int main(){
    Keyboard keyboard = Keyboard(&PORTA, &PINA, PORTA4, PORTA3, PORTA2, PORTA1, PORTA5);
    Clock clock = Clock(&PORTD, PORTD4, PORTD6, PORTA0);
    const char startTime[5] = "0000";
    clock.setStartTime(startTime); 
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
                break;
            case '3':
                option3();
                break;
            case '4':
                option4(keyboard);
                break;
            case '5':
                option5(keyboard);
                break;
            case '6':
                option6(clock, ledbar, servomotorE, servomotorF);
                break;
            default:
                printInvalidMessage();

        }
    }
}//a
