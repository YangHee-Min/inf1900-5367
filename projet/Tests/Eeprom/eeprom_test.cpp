#define SHIFT_DOWN 2
#include "../../Library/lib_dir/eeprom.h"

int main(){
    char time[5] = "2222";
    char time2[5] = "3333";
    char time3[5] = "4444";
    char inst[5] = "\0\0\0\0";
    Eeprom::addInstruction(time, inst);
    Eeprom::addInstruction(time2, inst);
    Eeprom::addInstruction(time3, inst);

    Eeprom::shiftInstructionsDown(0);
}//