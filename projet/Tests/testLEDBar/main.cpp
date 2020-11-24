#include "../../Library/lib_dir/LEDBar.h"

int main()
{
DDRC = 0xff;
DDRD = 0xff;
LEDBar bar = LEDBar();
//PORTC |= (1 << PORTC0);
//PORTC |= (1<<PORTC4);
bar.closeDoor(0);
bar.closeDoor(1);
//bar.openDoor(0);
//11

}
