/**********************************
* File: eeprom.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: December 4 2020
* Updated: December 6 2020
* Description: Definition of methods related to eeprom.
***********************************/

#ifndef EEPROM_H
#define EEPROM_H

#include "uart.h"
#include <avr/io.h>

class Eeprom{
    public:
        // Functions
        static void deleteInstruction(const char tensChar, const char unitChar);
        static void deleteInstruction(uint16_t address);
        static void addInstruction(char* timeTable, char* instructionTable);
        static void printInstructions();
        static void readTime(char* time, uint16_t address);
        static void readInstruction(char* instruction, uint16_t address);
        static void sortInstructionsTime(char* time);

        // Attributes
        static uint16_t endPointer_;
        static Uart uart_;
        
        // Constants
        static const uint8_t INSTRUCTION_SIZE_EEPROM = 8;
        static const uint8_t INSTRUCTION_SIZE_ARRAY = 5;
        static const uint8_t INITIAL_ADDRESS = 0;
        static const uint8_t SINGLE_CHAR_SIZE = 2;
        static const uint8_t INCREMENT_VALUE = 1;
        static const uint8_t INSTRUCTION_SHIFT = 4;
        
    private:
        // Functions
        static void saveInstruction(uint16_t startAddress, char* timeTable, char* machineInstruction);
        static uint16_t findEarliestInstructionAddress(char* time);
        static uint16_t findInsertionAddress(char* time);
        static uint8_t convertCharTo2Digit(char tensChar, char unitChar);
        static uint16_t convertIndexToByte(uint8_t index); 
        static void shiftInstructionsUp(uint16_t startAddress);
        static void shiftInstructionsDown(uint16_t startAddress);
        static void cycleInstructionsDown();

        // Protection against copy
        Eeprom(){}
};
#endif