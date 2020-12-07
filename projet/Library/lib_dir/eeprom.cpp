#include "eeprom.h"
#include "clock.h"
#include "time.h"

uint16_t Eeprom::endPointer_ = Eeprom::INITIAL_ADDRESS;
Uart Eeprom::uart_;

void Eeprom::addInstruction(char* timeTable, char* instructionTable){
    uint16_t insertionAddress = findInsertionAddress(timeTable);
    if(insertionAddress < endPointer_)
        shiftInstructionsDown(insertionAddress);

    saveInstruction(insertionAddress, timeTable, instructionTable);
    uart_.print("\nAction sauvegardée. Retour au menu principal...\n", 51);
}

void Eeprom::printInstructions(){
    if (endPointer_ > INITIAL_ADDRESS){
        for(uint16_t addressIterator = INITIAL_ADDRESS; addressIterator < endPointer_; addressIterator+= INSTRUCTION_SIZE_EEPROM){
            char timeTable[Time::TIME_SIZE];
            readTime(timeTable, addressIterator);
            uart_.print(timeTable, Time::TIME_SIZE - 1);
            uart_.print(" ", SINGLE_CHAR_SIZE);

            char instructionTable[INSTRUCTION_SIZE_ARRAY];
            for(uint8_t j = 0; j < INSTRUCTION_SIZE_ARRAY - INCREMENT_VALUE; j++){
                char instruction = uart_.readByteEeprom(addressIterator + INSTRUCTION_SHIFT + j);
                if(instruction != 'X')
                    instructionTable[j] = instruction;
                else{
                    instructionTable[j] = '\0';
                }
            }
            uart_.print(instructionTable, INSTRUCTION_SIZE_ARRAY - INCREMENT_VALUE);
            uart_.print("\n", SINGLE_CHAR_SIZE);
        }
    }
    else {
        uart_.print("Il n’y a aucune action programmée. Retour au menu principal...\n", 67);
    }
}

void Eeprom::readTime(char* time, uint16_t address){
    for(uint8_t i = 0; i < Time::TIME_SIZE - INCREMENT_VALUE; i++){
        time[i] = uart_.readByteEeprom(address + i);
    }
}

void Eeprom::readInstruction(char* instruction, uint16_t address){
    uint16_t addressIterator = address + INSTRUCTION_SHIFT;
    for(uint8_t i = 0; i < Time::TIME_SIZE - INCREMENT_VALUE; i++){
        instruction[i] = uart_.readByteEeprom(addressIterator + i);
    }
}

void Eeprom::deleteInstruction(const char tensChar, const char unitChar){
    uint8_t indexToDelete = convertCharTo2Digit(tensChar, unitChar);
    uint8_t indexStartCopy = indexToDelete + INCREMENT_VALUE;
    uint16_t copyStartAddress = convertIndexToByte(indexStartCopy);
    if(copyStartAddress == INITIAL_ADDRESS || copyStartAddress >= endPointer_ + INSTRUCTION_SIZE_EEPROM){
        uart_.print("\nIndex invalide. Retour au menu principal... \n", 46);
        return;
    }
    shiftInstructionsUp(copyStartAddress);
    uart_.print("\nAction supprimée. Retour au menu principal...\n", 48);
}

void Eeprom::sortInstructionsTime(char* time){
    uint16_t earliestInstructionAddress = findEarliestInstructionAddress(time);
    uint8_t numberOfCycles = (endPointer_ - earliestInstructionAddress) / INSTRUCTION_SIZE_EEPROM;
    const uint8_t START_CYCLE = 0;
    for(uint8_t currentCycle = START_CYCLE; currentCycle < numberOfCycles; currentCycle++){
        cycleInstructionsDown();
    } 
}

void Eeprom::saveInstruction(uint16_t startAddress, 
                                char* time, 
                                char* machineInstruction){
    uint16_t address = startAddress;

    for (uint8_t i = 0; i < Time::TIME_SIZE - INCREMENT_VALUE; i++){
        uart_.saveByteEeprom(address + i, time[i]);
    }
    address += Time::TIME_SIZE - INCREMENT_VALUE;
    
    for (uint8_t j = 0; j < INSTRUCTION_SIZE_ARRAY - INCREMENT_VALUE; j++){
        uart_.saveByteEeprom(address + j, machineInstruction[j]);
    }
    address += INSTRUCTION_SIZE_ARRAY - INCREMENT_VALUE;
    if(startAddress == endPointer_)
        endPointer_ = address;
}

uint16_t Eeprom::findEarliestInstructionAddress(char* time){
    uint16_t timeDifference = Time::convertTimeInTicks(time) - Clock::startTime_;
    char cmpTime[Time::TIME_SIZE];
    uint16_t cmpTimeDifference;
    for(uint16_t addressIterator = INITIAL_ADDRESS;addressIterator < endPointer_; addressIterator += INSTRUCTION_SIZE_EEPROM){
        readTime(cmpTime, addressIterator);
        cmpTimeDifference = Time::convertTimeInTicks(cmpTime) - Clock::startTime_;

        if(timeDifference <= cmpTimeDifference){
            return addressIterator;
        }
    }
    return endPointer_;
}

uint16_t Eeprom::findInsertionAddress(char* time){
    uint16_t timeDifference = Time::convertTimeInTicks(time) - Clock::startTime_;
    char cmpTime[Time::TIME_SIZE];
    uint16_t cmpTimeDifference;
    for(uint16_t addressIterator = INITIAL_ADDRESS;addressIterator < endPointer_; addressIterator+= INSTRUCTION_SIZE_EEPROM){
        readTime(cmpTime, addressIterator);
        cmpTimeDifference = Time::convertTimeInTicks(cmpTime) - Clock::startTime_;

        if(timeDifference < cmpTimeDifference){
            return addressIterator;
        }
    }
    return endPointer_;
}

uint8_t Eeprom::convertCharTo2Digit(const char tensChar, const char unitChar){
    return Time::getDigitFromChar(tensChar) * Time::TENS_FACTOR + Time::getDigitFromChar(unitChar);
}

uint16_t Eeprom::convertIndexToByte(uint8_t index){
    return (index - INCREMENT_VALUE) * INSTRUCTION_SIZE_EEPROM;
}

void Eeprom::shiftInstructionsUp(uint16_t startAddress){
    if ((startAddress < endPointer_ + INSTRUCTION_SIZE_EEPROM) && (startAddress != INITIAL_ADDRESS)){
        for(uint8_t addressIterator = startAddress; 
        addressIterator < endPointer_ + INSTRUCTION_SIZE_EEPROM; 
        addressIterator += INSTRUCTION_SIZE_EEPROM){
            for(uint8_t i = 0; i < INSTRUCTION_SIZE_EEPROM; i++){
                char instruction = uart_.readByteEeprom(addressIterator + i);
                uart_.saveByteEeprom((uint16_t) (addressIterator + i - INSTRUCTION_SIZE_EEPROM), (uint8_t) instruction);
            }   
        }
        endPointer_ -= INSTRUCTION_SIZE_EEPROM;
    }
    else{
         uart_.print("\nDécalage vers le haut échoué. Retour au menu principal\n", 59);
    }
}

void Eeprom::shiftInstructionsDown(uint16_t startAddress){
    if (startAddress < endPointer_){
        for(uint8_t addressIterator = endPointer_ - INSTRUCTION_SIZE_EEPROM; 
        (addressIterator >= startAddress) && (addressIterator < endPointer_); 
        addressIterator -= INSTRUCTION_SIZE_EEPROM){
            for(uint8_t i = 0; i < INSTRUCTION_SIZE_EEPROM; i++){
                char instruction = uart_.readByteEeprom(addressIterator + i);
                uart_.saveByteEeprom((uint16_t) (addressIterator + i + INSTRUCTION_SIZE_EEPROM), (uint8_t) instruction);
            }   
        }
        endPointer_ += INSTRUCTION_SIZE_EEPROM;
    }
    else{
         uart_.print("\nL'adresse insérée n'est pas valide. Retour au menu principal...\n", 68);
    }
}

void Eeprom::cycleInstructionsDown(){
    uint16_t lastAddress = endPointer_ - INSTRUCTION_SIZE_EEPROM;
    char lastTime[Time::TIME_SIZE];
    readTime(lastTime, lastAddress);
    char lastInstruction[Eeprom::INSTRUCTION_SIZE_ARRAY];
    readInstruction(lastInstruction, lastAddress);
    

    shiftInstructionsDown(INITIAL_ADDRESS);

    saveInstruction(INITIAL_ADDRESS, lastTime, lastInstruction);
    
    shiftInstructionsUp(endPointer_);
}

