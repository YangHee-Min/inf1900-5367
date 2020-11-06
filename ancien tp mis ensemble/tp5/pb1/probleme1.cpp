#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>

void initialisation(){
    // 2400 bauds.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // Lets UART0 do transmission and reception
    UCSR0B = (1<<RXEN0) | (1<<TXEN0);
    // Format of frames : 8 bits, 1 stop bit, none parity
    UCSR0C = (1 << USBS0) | (3<<UCSZ00);
}
void transmission(uint8_t data){
    while (!(UCSR0A & (1<<UDRE0))){};
    UDR0 = data;
}

void write(uint8_t instruction, uint8_t operand, uint16_t address){
    uint16_t instruction16Bits = instruction;
    uint16_t operand16Bits = operand;
    uint16_t instructionOperand = ((instruction16Bits << 8) | (operand16Bits));
    eeprom_write_block((const uint8_t*) &instructionOperand, (void*)address, sizeof(instructionOperand));
    transmission(instruction);
    transmission(operand);
    
}




int main()
{


  DDRA = 0xFF; //PORTA en sorite
  uint8_t LED = 0;
  initialisation();
  uint8_t instruction = 42;
  uint8_t operand = 41;
  write(instruction, operand); 
  if(eeprom_read_byte((uint8_t*)0x0000) == instruction){
            LED = 1;
        }
        else{
            LED = 2;
          
        }
  
  PORTA = LED;
}


/*
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
  */