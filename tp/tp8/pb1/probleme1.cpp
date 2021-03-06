/*
* File: probleme2.cpp
* Authors : Hee-Min Yang   Adam Halim
* Date : 21 septembre 2020
* Updated : 15 septembre 2020
* Description : Behaviour of the microprocessor follows the 
*               state diagram specified in the table below 
*               according to the instructions given for TP2 
*               problem 1 of the class INF1900. 
* Materials: 2 push buttons, 1 red LED, 1 green LED and 
*            1 Atmega324a 
_______________________________________________________
+--------------+----+----+--------------+--------+
| ETAT PRESENT | D3 | D2 | ETAT SUIVANT | SORTIE |
+--------------+----+----+--------------+--------+
| INIT         | 1  | X  | VERT0        | ETEINT |
+--------------+----+----+--------------+--------+
| INIT         | X  | 1  | ROUGE0       | ETEINT |
+--------------+----+----+--------------+--------+
| VERT0        | X  | 1  | ROUGE0       | VERT   |
+--------------+----+----+--------------+--------+
| ROUGE0       | 1  | X  | VERT1        | ROUGE  |
+--------------+----+----+--------------+--------+
| VERT1        | 1  | X  | INIT         | VERT   |
+--------------+----+----+--------------+--------+
| VERT1        | X  | 1  | ROUGE1       | VERT   |
+--------------+----+----+--------------+--------+
| ROUGE1       | X  | 1  | VERT1        | ROUGE  |
+--------------+----+----+--------------+--------+
 **/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../tp7/lib_dir/debug.h"

//! Fonction qui indique si le bouton spécifié est toujours appuyé 
//! après le délai de rebond.
//! \return True si le bouton D2 est appuyé pendant au moins 
//|         10 ms. Faux sinon.
bool pinEstAppuye(uint8_t pin){
    const double DELAI_REBOND = 10;

    if (PIND & (1 << pin)){
        _delay_ms(DELAI_REBOND);
        if (PIND & (1 << pin)){
              return true;      
        }
    }
    return false;
    
}

int main()
{
    DDRA = 0xff; // PORT A est en mode sortie
    DDRD = 0x00; // PORT D est en mode entreePortD

    //! Définition des états possibles 
    enum ETAT{INIT, VERT0, VERT1, ROUGE0, ROUGE1};

    //! Définition des sorties possibles (DEL)
    enum SORTIE{ETEINT, VERT, ROUGE};

    //! Initialisation de l'état initial du système et de 
    //! la dernière entrée.
    uint8_t etatPresent = INIT;
    uint8_t derniereEntreePortD = 0;

    // INITIALISE DEBUGGER
    Debug debug = Debug();

    //! Répétition du boucle for sert à constamment 
    //! vérifier l'état du système.
    for(;;)
    {
        uint8_t entreePortD = PIND;

        bool vientDePeserSurD2OuD3 = derniereEntreePortD == 0 && entreePortD != 0;

        //! À chaque boucle, on met à jour la lumière et 
        //| changeons l'état du système selon le diagramme d'état si:
        //!         1. On vient tout juste de peser sur un bouton 
        //!         2. La condition de transition d'état (selon le 
        //!            diagramme d'état) est satisfaite.
        switch(etatPresent)
        {
            case INIT:{
                #ifdef DEBUG
                char initMSG[7] = "INIT\n";
                debug.DEBUG_PRINT(initMSG, 7);
                #endif

                PORTA = ETEINT;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND2))
                    etatPresent = ROUGE0;
                else if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND3))
                    etatPresent = VERT0;
                }break;

            case VERT0:{
                #ifdef DEBUG
                char vert0MSG[8] = "vert0\n";
                debug.DEBUG_PRINT(vert0MSG, 8);
                #endif

                PORTA = VERT;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND2))
                    etatPresent = ROUGE0;
                }break;

            case ROUGE0:{
                #ifdef DEBUG
                char rouge0MSG[9] = "rouge0\n";
                debug.DEBUG_PRINT(rouge0MSG, 9);
                #endif

                PORTA = ROUGE;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND3))
                    etatPresent = VERT1;
                }break;

            case VERT1:{
                #ifdef DEBUG
                char vert1MSG[8] = "vert1\n";
                debug.DEBUG_PRINT(vert1MSG, 8);
                #endif

                PORTA = VERT;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND2))
                    etatPresent = ROUGE1;
                else if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND3))
                    etatPresent = INIT;
                }break;

            case ROUGE1:{
                #ifdef DEBUG
                char rouge1MSG[9] = "rouge1\n";
                debug.DEBUG_PRINT(rouge1MSG, 9);
                #endif

                PORTA = ROUGE;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND2))
                    etatPresent = VERT1;
                }
            }
        derniereEntreePortD = entreePortD;  
    } 
}
