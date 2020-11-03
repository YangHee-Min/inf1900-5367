//Nom de l'auteur: Jean Janssen, Chun Yang Li
//Description du programme: Ce programme permet de changer le couleur du DEL bicolore par rapport à l'intensité de la lumière détectée.

#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

const uint8_t DELAY = 1;                                // Constante pour le fonctionnement du PWN.
const uint8_t INTENSITE_FORTE = 0x8E;                   // Les intervalles de tension sont de [2,4; 2,8], [2,8; 3,2] et [3,2; 3,6] volt. 
const uint8_t INTENSITE_FAIBLE = 0xA3;                  // Puisque la tension ne va pas plus que 3,6v et plus bas que 2,4v, nous avons déterminé 2,8 et 3,2 comme bornes qui se traduisent en 0x8E et 0xA3 sur une base de 255 plutôt que 5v. 

int main(){
    DDRA = 0x00;
    DDRB = 0xff;
    uint8_t myPin = PINA0;
    for(;;){
        can c;
        uint16_t valeur10Bits;                          // La variable de 16 bits qui contient les 10 bits du can.
        valeur10Bits = c.lecture(myPin);
        valeur10Bits = valeur10Bits >> 2;
        uint8_t valeur8Bits = valeur10Bits;

        if(valeur8Bits <= INTENSITE_FORTE){                            // Etat = ROUGE
            PORTB = 1 << PORTB1;                            
        }
        if(valeur8Bits <= INTENSITE_FAIBLE && valeur8Bits > INTENSITE_FORTE){      // Etat = AMBRE
            _delay_ms(DELAY);                                                      // On obtient la couleur ambre en alternant rapidement la couleur rouge et verte 
            PORTB = 1 << PORTB1;
            _delay_ms(DELAY);
            PORTB = 1 << PORTB0;
        }
        if(valeur8Bits > INTENSITE_FAIBLE){                              // Etat = VERT
            PORTB = 1 << PORTB0;
        }
    }
    return 0;
}