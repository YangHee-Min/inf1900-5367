#include "../../Library/lib_dir/LEDBar.h"

int main(){
    // DDRC = 0xff;
    // DDRD = 0xff;
    LEDBar bar = LEDBar(PORTC0, PORTC1, PORTC2, PORTC3, PORTC4, &PORTC);
    Uart debug;

    debug.print("start", 6);
    // bar.openDoor(0);
    // // bar.closeDoor(0);
    // bar.LEDState_ = 0xFFFFFFFF;
    // bar.displayState();
    // debug.print("end", 4);
    
    for(int i = 0; i < 4; i++){
        bar.closeDoor(i);
        debug.print("close A\n", 9);

        bar.openDoor(i);
        debug.print("open A\n", 8);
    }
        // bar.closeDoor(0);
        // debug.DEBUG_PRINT("close A\n", 9);

        // bar.openDoor(0);
        // debug.DEBUG_PRINT("open A\n", 8);

        // bar.closeDoor(1);
        // debug.DEBUG_PRINT("close", 6);

        // bar.openDoor(1);
        // debug.DEBUG_PRINT("open", 5);
        

        // bar.closeDoor(2);
        // debug.DEBUG_PRINT("close", 6);

        // bar.openDoor(2);
        // debug.DEBUG_PRINT("open", 5);

        // bar.closeDoor(3);
        // debug.DEBUG_PRINT("close", 6);

        // bar.openDoor(3);
        // debug.DEBUG_PRINT("open", 5);

//a

}
