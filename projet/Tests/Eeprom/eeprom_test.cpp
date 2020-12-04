#define SHIFT_DOWN 2
#include "../../Library/lib_dir/eeprom.h"

int main(){
    char time[5] = "1025";
    char time2[5] = "1222";
    char time3[5] = "2359";
    char inst[5] = "\0\0\0\0";
    Eeprom::addInstruction(time, inst);
    Eeprom::addInstruction(time2, inst);
    Eeprom::addInstruction(time3, inst);

    char startTime[5] = "1200";
    Eeprom::printInstructions();
    Eeprom::sortInstructionsTime(startTime);
    Eeprom::printInstructions();
    //Eeprom::cycleInstructionsDown();
    //Eeprom::shiftInstructionsDown(0);
}//a