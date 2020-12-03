#ifndef EEPROM_H
#define EEPROM_H

#include "time.h"
#include "uart.h"
#include <avr/io.h>

class Eeprom{
    public:
        static void deleteInstruction(const char tensChar, const char unitChar);
        static void addInstruction(char* timeTable, char* instructionTable);
        static void printInstructions();
        static uint16_t endPointer_;
        static Uart uart_;

        static const uint8_t INSTRUCTION_SIZE_EEPROM = 8;
        static const uint8_t INSTRUCTION_SIZE_ARRAY = 5;
        static const uint8_t INITIAL_ADDRESS = 0;
        static const uint8_t SINGLE_CHAR_SIZE = 2;
        static const uint8_t INCREMENT_VALUE = 1;
        
    private:
        static void saveInstruction(uint16_t startAddress, char* timeTable, char* machineInstruction);
        static uint16_t findInsertionAddress(char* time);
        static uint8_t convertCharTo2Digit(char tensChar, char unitChar);
        static uint16_t convertIndexToByte(uint8_t index); 
        static void shiftInstructionsUp(uint16_t startAddress);
        static void shiftInstructionsDown(uint16_t startAddress);
        Eeprom(){}
};
#endif