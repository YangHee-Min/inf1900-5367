#define SHIFT_DOWN 2
#include "../../Library/lib_dir/eeprom.h"

int main(){
    char time[5] = "2343";
    char inst[5] = "A1XX";
    char time2[5] = "9911";
    char inst2[5] = "F219";
    Eeprom::addInstruction(time, inst);
    Eeprom::addInstruction(time, inst);
    Eeprom::addInstruction(time, inst);
    Eeprom::addInstruction(time, inst);
    Eeprom::addInstruction(time2, inst2);
    Eeprom::addInstruction(time2, inst2);

    #if SHIFT_DOWN == 0
    Eeprom::shiftInstructionsUp(32);
    Eeprom::shiftInstructionsUp(24);
    //Eeprom::shiftInstructionsUp(7); 
    #elif SHIFT_DOWN == 1
    Eeprom::shiftInstructionsDown(32);//
    Eeprom::uart_.transmission(Eeprom::endPointer_ + '0');

    #endif
}//