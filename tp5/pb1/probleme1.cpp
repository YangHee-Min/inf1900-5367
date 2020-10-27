#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__

#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

int main()
{
  DDRA = 0xFF; //PORTA en sorite

  uint8_t stringOfData[94] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
  stringOfData[92] = 0x00;
  eeprom_write_block((const uint8_t*) &stringOfData, (void*)0x0000, sizeof(stringOfData));

  uint8_t LED = 0;
  uint16_t address = 0x0000;
  for(uint8_t i = 0; i < sizeof(stringOfData)/sizeof(stringOfData[0]); i++, address++){
        if(eeprom_read_byte((uint8_t*)address) == stringOfData[i]){
            LED = 1;
        }
        else{
            LED = 2;
            break;
        }
  }
  PORTA = LED;
}