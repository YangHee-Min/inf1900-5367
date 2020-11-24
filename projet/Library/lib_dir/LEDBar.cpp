#include "LEDBar.h"

void LEDBar::displayState()
{
PORTC |= (1 << PORTC3); /* Memory mode on */
PORTC |= (1 << PORTC4); /* Display mode on */
uint8_t currentBit;

for(uint8_t i = 0; i < 32; i++)
{
currentBit = LEDState_;
currentBit &= (1 << i);

if(currentBit == (1 << i))
    {
    PORTC |= (1 << PORTC2); /* DS */
    }
else
    {
    PORTC &= ~(1 << PORTC2); /* DS */
    }

PORTC |= (1 << PORTC0);
PORTC &= ~(1 << PORTC0); 

};

PORTC |= (1 <<PORTC1); /* LATCH */

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