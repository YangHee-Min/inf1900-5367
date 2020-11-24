#include "../../Library/lib_dir/LEDBar.h"

int main()
{
DDRC = 0xff;
DDRD = 0xff;

//PORTC |= (1 << PORTC0);
LEDBar bar = LEDBar();
bar.closeDoor(0);

}