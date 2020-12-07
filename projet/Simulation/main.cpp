#include "includes.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile bool isClockInterrupted = false;

const uint8_t MINIMUM_ANGLE_VALUE = 0;
const uint8_t MAXIMUM_ANGLE_VALUE = 180;
const uint8_t ADDRESS_SIZE = 8;
const uint8_t INITIAL_ADDRESS = 0x0000;

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

void printInstruction(const char* instruction){
    uint8_t lastIndex = STATE_INDEX_3;
    if(instruction[DEVICE_INDEX] >= 'A' && instruction[DEVICE_INDEX] <= 'D'){
        lastIndex = STATE_INDEX_1;
    }
    lastIndex++;
    uart.print(instruction, lastIndex);
    uart.print("\n", 2);
}

void initialisationISR(){
    cli ();
    EIMSK |= (1 << INT1);
    EICRA |= (1 << ISC11);
    sei ();

}

ISR(INT1_vect){
    isClockInterrupted = true;
}

bool validateMachineAction(char* machineInstruction, Keyboard& keyboard){
    char deviceLetter = keyboard.readKey();
    machineInstruction[DEVICE_INDEX] = deviceLetter;

    switch(machineInstruction[DEVICE_INDEX]){
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
            
            char servoValues[Servomotor::ANGLE_STRING_SIZE] = {servoValue1, servoValue2, servoValue3};
            for(uint8_t currentDigit = Servomotor::HUNDREDS_INDEX; currentDigit <= Servomotor::UNIT_INDEX; currentDigit++){
                if(servoValues[currentDigit] < '0' || servoValues[currentDigit] > '9')
                    return false;
            }
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
        Eeprom::sortInstructionsTime(time);
        clock.setStartTime(time);
        uart.print("\nHeure de départ sauvegardée. Retour au menu principal...\n", 60);
    }
    else{
        printInvalidMessage();
    }
    
}

void executeInstruction(const char* machineInstruction, LEDBar& ledbar, Servomotor& servomotorE, Servomotor& servomotorF){
    if(machineInstruction[DEVICE_INDEX] >= 'A' && machineInstruction[DEVICE_INDEX] <= 'D'){
        uint8_t door = machineInstruction[DEVICE_INDEX] - 'A';
        if(machineInstruction[STATE_INDEX_1] == OPEN_CHAR)
            ledbar.openDoor(door);
        else if(machineInstruction[STATE_INDEX_1] == CLOSE_CHAR)
            ledbar.closeDoor(door);
    }
    else if(machineInstruction[DEVICE_INDEX] == 'E' || machineInstruction[DEVICE_INDEX == 'F']){
        char angleString[Servomotor::ANGLE_STRING_SIZE] = {machineInstruction[STATE_INDEX_1], machineInstruction[STATE_INDEX_2], machineInstruction[STATE_INDEX_3]};
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

void option2(LEDBar& ledbar, Keyboard& keyboard, Servomotor& servomotorE, Servomotor& servomotorF){
    uart.print("\nEntrez l’identifiant d’un dispositif suivi de sa valeur de configuration. (A|B|C|D)(0|1) ou (E|F)(000-180)\n", 113);
    char machineInstruction[Eeprom::INSTRUCTION_SIZE_ARRAY];
    if(validateMachineAction(machineInstruction, keyboard)){
        executeInstruction(machineInstruction, ledbar, servomotorE, servomotorF);
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
    uart.print("\nEntrez le numéro d’une action à supprimer\n", 47);
    char deleteValue1 = keyboard.readKey();
    char deleteValue2 = keyboard.readKey();

    Eeprom::deleteInstruction(deleteValue1, deleteValue2);
}

void option6(Clock& clock, LEDBar& ledbar, Servomotor& servomotorE, Servomotor& servomotorF, LCM& lcd){
    lcd.clear();
    lcd << "Simulation";
    uart.print("\nOption simulation choisie. Début de la simulation...\n", 55);
    clock.startClock();
    initialisationISR();
    bool isRunning = true;
    uint16_t addressIterator = Eeprom::INITIAL_ADDRESS;
    char time[Time::TIME_SIZE];
    char instruction[Eeprom::INSTRUCTION_SIZE_ARRAY];
    while(isRunning){
        
        if(addressIterator >= Eeprom::endPointer_){
            if(Clock::currentTime_ == Clock::stopTime_){
                isRunning = false;
            }
            continue;
        }

        Eeprom::readTime(time, addressIterator);

        if((clock.getCurrentTimeInTicks() - Clock::startTime_) >= Time::convertTimeInTicks(time) - (Clock::startTime_)){
            Eeprom::readInstruction(instruction, addressIterator);
            executeInstruction(instruction, ledbar, servomotorE, servomotorF);
            printInstruction(instruction);
            addressIterator += Eeprom::INSTRUCTION_SIZE_EEPROM;
        }
        else{
            if(Clock::isClockStopped_)
                isRunning = false;
            else if(isClockInterrupted)
                isRunning = false;
        }
    }
    clock.stopClock();
    isRunning = true;
    if(isClockInterrupted){
        isClockInterrupted = false;
        uart.print("Simulation interrompu. Retour au menu principal...\n", 52);
        clock.rewindToStartTime();
    }
    else{
        uart.print("Simulation terminée. Retour au menu principal...\n", 50);
    }
}

int main(){
    Keyboard keyboard = Keyboard(&PORTA, &PINA, PORTA4, PORTA3, PORTA2, PORTA1, PORTA5);
    Clock clock = Clock(&PORTD, PORTD4, PORTD6, PORTA0);
    const char startTime[5] = "0000";
    clock.setStartTime(startTime); 
    LEDBar ledbar = LEDBar(PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, &PORTC);
    Servomotor servomotorE = Servomotor(PORTA6, &PORTA);
    Servomotor servomotorF = Servomotor(PORTA7, &PORTA);
    LCM lcd = LCM(&DDRB, &PORTB);

    for(;;){
        lcd.clear();
        lcd << "Configuration";
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
                option6(clock, ledbar, servomotorE, servomotorF, lcd);
                break;
            default:
                printInvalidMessage();

        }
    }
}
