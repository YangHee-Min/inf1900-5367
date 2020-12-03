#include "eeprom.h"

uint16_t Eeprom::endPointer_ = Eeprom::INITIAL_ADDRESS;
Uart Eeprom::uart_;

void Eeprom::addInstruction(char* timeTable, char* instructionTable){
    uint16_t insertionAddress = findInsertionAddress(timeTable);
    if(insertionAddress < endPointer_)
        shiftInstructionsDown(insertionAddress);

    saveInstruction(insertionAddress, timeTable, instructionTable);
}

void Eeprom::printInstructions(){
    if (endPointer_ > INITIAL_ADDRESS){
        for(uint16_t addressIterator = INITIAL_ADDRESS; addressIterator < endPointer_;){
            char timeTable[Time::TIME_SIZE];
            for(uint8_t i = 0; i < Time::TIME_SIZE - INCREMENT_VALUE; i++, addressIterator++){
                timeTable[i] = uart_.readByteEeprom(addressIterator);
            }
            uart_.print(timeTable, Time::TIME_SIZE - 1);
            uart_.print(" ", SINGLE_CHAR_SIZE);

            char instructionTable[INSTRUCTION_SIZE_ARRAY];
            for(uint8_t j = 0; j < INSTRUCTION_SIZE_ARRAY - INCREMENT_VALUE; j++, addressIterator++){
                char instruction = uart_.readByteEeprom(addressIterator);
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

void Eeprom::deleteInstruction(const char tensChar, const char unitChar){
    uint8_t indexToDelete = convertCharTo2Digit(tensChar, unitChar);
    uint8_t indexStartCopy = indexToDelete + INCREMENT_VALUE;
    uint16_t copyStartAddress = convertIndexToByte(indexStartCopy);
    shiftInstructionsUp(copyStartAddress);
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
    
    uart_.print("Action sauvegardée. Retour au menu principal...\n", 50);
}

uint16_t Eeprom::findInsertionAddress(char* time){
    // TODO
    return endPointer_;
}

uint8_t Eeprom::convertCharTo2Digit(const char tensChar, const char unitChar){
    return Time::getDigitFromChar(tensChar) * Time::TENS_FACTOR + Time::getDigitFromChar(unitChar);
}

uint16_t Eeprom::convertIndexToByte(uint8_t index){
    return (index - INCREMENT_VALUE) * INSTRUCTION_SIZE_EEPROM;
}
void Eeprom::shiftInstructionsDown(uint16_t startAddress){

}
void Eeprom::shiftInstructionsUp(uint16_t startAddress){
    if (startAddress < endPointer_){
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
         uart_.print("L'adresse insérée n'est pas valide. Retour au menu \n", 39);
    }
}

void Eeprom::shiftInstructionsDown(uint16_t startAddress){
    
}