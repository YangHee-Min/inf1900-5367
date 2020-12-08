/**********************************
* File: eeprom.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: December 4 2020
* Updated: December 6 2020
* Description: Implementation of methods related to eeprom.
***********************************/

#include "eeprom.h"
#include "clock.h"
#include "time.h"

uint16_t Eeprom::endPointer_ = Eeprom::INITIAL_ADDRESS;
Uart Eeprom::uart_;

//! Function that adds an instruction to the eeprom.
//! \param  timeTable           Array that contains the instruction timestamp
//! \param  instructionTable    Array that contains the current instruction
void Eeprom::addInstruction(char* timeTable, char* instructionTable){
    uint16_t insertionAddress = findInsertionAddress(timeTable);
    if(insertionAddress < endPointer_)
        shiftInstructionsDown(insertionAddress);

    saveInstruction(insertionAddress, timeTable, instructionTable);
    uart_.print("\nAction sauvegardée. Retour au menu principal...\n", 51);
}

//! Function to display the instructions contained in the eeprom.
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

//! Function that puts the time of the instruction at the 
//! specified address into an array.
//! \param time     Array that will contain the read time 
//! \param address  The starting address where the time chars 
//!                 are located
void Eeprom::readTime(char* time, uint16_t address){
    for(uint8_t i = 0; i < Time::TIME_SIZE - INCREMENT_VALUE; i++){
        time[i] = uart_.readByteEeprom(address + i);
    }
}

//! Function that reads an instruction at a 
//! specific address and puts it into an array.
//! \param instruction  Array that will contain the instruction
//! \param address      The starting address where the instruction 
//!                     is located
void Eeprom::readInstruction(char* instruction, uint16_t address){
    uint16_t addressIterator = address + INSTRUCTION_SHIFT;
    for(uint8_t i = 0; i < Time::TIME_SIZE - INCREMENT_VALUE; i++){
        instruction[i] = uart_.readByteEeprom(addressIterator + i);
    }
}

//! Function that deletes an instruction from the eeprom.
//! \param  tensChar    Most significant digit 
//!                     of two digit number as char
//! \param  unitChar    Least significant digit of 
//!                     two digit number as char   
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

//! Function that sorts the instructions in teh eeprom according 
//! to their execution order in function of the specified time.
//! \param  time    Reference time according to which instructions 
//!                 will be sorted.                  
void Eeprom::sortInstructionsTime(char* time){
    uint16_t earliestInstructionAddress = findEarliestInstructionAddress(time);
    uint8_t numberOfCycles = (endPointer_ - earliestInstructionAddress) / INSTRUCTION_SIZE_EEPROM;
    const uint8_t START_CYCLE = 0;
    for(uint8_t currentCycle = START_CYCLE; currentCycle < numberOfCycles; currentCycle++){
        cycleInstructionsDown();
    } 
}

//! Function that saves an instruction into the eeprom.
//! \param  startAddress        first address where instruction will be saved
//! \param  time                Array that contains the instruction timestamp
//! \param  machineInstruction  Array that contains the current instruction
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

//! Function that finds the earliest instruction to be executed
//! according to specified time.
//! \param  time    Time in "HHMM" format
//! \return address of the earliest instruction 
//!         after specified time.
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

//! Finds insertion address of an instruction according to 
//! its start time.
//! \param      time    Start time of the instruction to add.
//! \return     byte address where new instruction will be added.
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

//! Function that converts the two digit char  into its int value.
//! \param  tensChar    Most significant digit of two digit 
//!                     number as char
//! \param  unitChar    Least significant digit of two digit 
//!                     number as char
//! \return     int value of the two digit number passed as char.
uint8_t Eeprom::convertCharTo2Digit(const char tensChar, const char unitChar){
    return Time::getDigitFromChar(tensChar) * Time::TENS_FACTOR + Time::getDigitFromChar(unitChar);
}

//! Function that converts an index to its byte address.
//! \param  index      Index of the instruction starting 
//!                    from 1
//! \return byte address of the instruction of the 
//!         corresponding index.
uint16_t Eeprom::convertIndexToByte(uint8_t index){
    return (index - INCREMENT_VALUE) * INSTRUCTION_SIZE_EEPROM;
}

//! Shifts all instructions up by 1 starting from the startAddress.
//! \param  startAddress    lowest address to shift upwards.
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

//! Shifts all instructions down by 1 start from the startAddress.
//! \param  startAddress    lowest address to shift downwards.
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

//! Function that shifts all instructions down by 1 index except 
//! for the last one that becomes the first instruction.
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

