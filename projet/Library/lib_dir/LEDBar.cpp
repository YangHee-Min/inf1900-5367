#include "LEDBar.h"
#include "debug.h"


void LEDBar::displayState(){
    uint8_t currentBit;
    Debug debug = Debug();
    //debug.DEBUG_PRINT("lol\n",5);
    for(uint8_t i = 32; i > 0; i--){
        currentBit = LEDState_ & (1<<(i-1));
        if(currentBit){
            PORTC |= (1 << PORTC2); /* DS */
            //debug.DEBUG_PRINT("1\n",3);
        }
        else{
            PORTC &= ~(1 << PORTC2); /* DS */
            //debug.DEBUG_PRINT("0\n",3);
        }

        PORTC |= (1 << PORTC0);
        PORTC &= ~(1 << PORTC0); 
        //1
    };

    PORTC |= (1 <<PORTC1); /* LATCH */
    PORTC &= ~(1 <<PORTC1);
    //debug.DEBUG_PRINT("latch\n",7);
    _delay_ms(1000);
}

void LEDBar::openDoor(uint8_t doorType){
PORTC |= (1 << PORTC3); /* Memory mode on */
PORTC |= (1 << PORTC4); /* Display mode on */
Debug debug = Debug();
for(uint8_t i = 8; i > 0; i--)
{
     
    //LEDState_ &= ~(1 << (8*doorType+(i-1)));
    LEDState_ = 0b0011100;
    debug.transmission(LEDState_);
    debug.transmission(0xFF);
    displayState();
    _delay_ms(5000);
    
    

}
}

void LEDBar::closeDoor(uint8_t doorType)
{
PORTC |= (1 << PORTC3); /* Memory mode on */
PORTC &= ~(1 << PORTC4); /* Display mode on */
for(uint8_t i = 0; i < 8; i++)
{
    
    LEDState_ |= (1 << (8*doorType+i));
    displayState();
    

}
}