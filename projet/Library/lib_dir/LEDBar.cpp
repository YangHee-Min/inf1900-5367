#include "LEDBar.h"

void LEDBar::displayState()
{
PORTC3 = 1; /* Memory mode on */
PORTC4 = 0; /* Display mode on */
uint8_t currentBit;

for(uint8_t i = 0; i < 32; i++)
{
currentBit = LEDState_;
currentBit &= (1 << i);

if(currentBit == (1 << i))
    {
    PORTC2 = 1; /* DS */
    }
else
    {
    PORTC2 = 0; /* DS */
    }

PORTC0 = currentBit;
PORTC0 = 0; 

};

PORTC1 = 1; /* LATCH */

}

void LEDBar::openDoor(uint8_t doorType)
{

for(uint8_t i = 0; i <= 7; i++)
{
    LEDState_ &= ~(1 << (8*doorType+i));
    displayState();

}
}

void LEDBar::closeDoor(uint8_t doorType)
{

for(uint8_t i = 7; i <= 0; i--)
{
    LEDState_ |= (1 << (8*doorType+i));
    displayState();

}
}