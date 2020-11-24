#include <avr/io.h> 

class LEDBar {
public:

LEDBar(){LEDState_ = 0};

void openDoor(uint8_t doorType);
void closeDoor(uint8_t doorType);
void displayState();

private:

uint32_t LEDState_;

enum Doors
    {
    doorA = 0;
    doorB = 1;
    doorC = 2;
    doorD = 3;
    };

}