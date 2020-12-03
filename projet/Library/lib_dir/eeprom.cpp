#include "eeprom.h"

uint16_t Eeprom::endPointer_ = Eeprom::INITIAL_ADDRESS;
Uart Eeprom::uart_;

void Eeprom::saveInstruction(uint16_t startAddress, 
                                char* time, 
                                char* machineInstruction){
    const uint8_t DECREMENT_VALUE = 1;
    uint16_t address = startAddress;

    for (uint8_t i = 0; i < Time::TIME_SIZE - DECREMENT_VALUE; i++){
        uart_.saveByteEeprom(address + i, time[i]);
    }
    address += Time::TIME_SIZE - DECREMENT_VALUE;
    
    for (uint8_t j = 0; j < INSTRUCTION_SIZE - DECREMENT_VALUE; j++){
        uart_.saveByteEeprom(address + j, machineInstruction[j]);
    }
    address += INSTRUCTION_SIZE - DECREMENT_VALUE;
    if(startAddress == endPointer_)
        endPointer_ = address;
    
    uart_.print("Action sauvegardée. Retour au menu principal...\n", 6);
}

void Eeprom::printInstructions(){
    if (endPointer_ > INITIAL_ADDRESS){
        for(uint16_t addressIterator = INITIAL_ADDRESS; addressIterator < endPointer_;){
            char timeTable[Time::TIME_SIZE];
            for(uint8_t i = 0; i < Time::TIME_SIZE - DECREMENT_VALUE; i++, addressIterator++){
                timeTable[i] = uart_.readByteEeprom(addressIterator);
            }
            uart_.print(timeTable, Time::TIME_SIZE - 1);
            uart_.print(" ", SINGLE_CHAR_SIZE);

            char instructionTable[INSTRUCTION_SIZE];
            for(uint8_t j = 0; j < INSTRUCTION_SIZE - DECREMENT_VALUE; j++, addressIterator++){
                char instruction = uart_.readByteEeprom(addressIterator);
                if(instruction != 'X')
                    instructionTable[j] = instruction;
                else{
                    instructionTable[j] = '\0';
                }
            }
            uart_.print(instructionTable, INSTRUCTION_SIZE - 1);
            uart_.print("\n", SINGLE_CHAR_SIZE);
        }
    }
    else {
        uart_.print("Il n’y a aucune action programmée. Retour au menu principal...\n", 67);
    }
}

void Eeprom::deleteInstruction(uint16_t deleteAddress){
    if (deleteAddress < endPointer_){
            uint8_t addressIterator = deleteAddress;
            for(uint8_t i = 0; i < INSTRUCTION_SIZE_EEPROM; i++, addressIterator++){
                char instruction = uart.readByteEeprom(addressIterator);
                uart.saveByteEeprom((uint16_t) (addressIterator - ADDRESS_SIZE), (uint8_t) instruction);
            }   
        }
        address -= ADDRESS_SIZE;
    }
    else{
         uart_.print("L'adresse insérée n'est pas valide. Retour au menu \n", 39);
    }
}
