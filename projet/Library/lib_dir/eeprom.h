#ifndef EEPROM_H
#define EEPROM_H

#include "time.h"
#include "uart.h"
#include <avr/io.h>

class Eeprom{
    public:
        static void saveInstruction(uint16_t startAddress, char* timeTable, char* instructionTable);
        static void deleteInstruction(uint16_t deleteAddress);
        static void shiftInstructions(uint16_t firstAddress);
        static void printInstructions();

        static uint16_t endPointer_;
        static Uart uart_;

        static const uint8_t INSTRUCTION_SIZE_EEPROM = 8;
        static const uint8_t INSTRUCTION_SIZE_ARRAY = 5;
        static const uint8_t INITIAL_ADDRESS = 0;
        static const uint8_t SINGLE_CHAR_SIZE = 2;
        static const uint8_t DECREMENT_VALUE = 1;
    private:
        uint16_t findInsertionAddress(char* time);
        Eeprom(){}
};
#endif