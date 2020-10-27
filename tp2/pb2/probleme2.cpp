/*
* Fichier: probleme2.cpp
* Auteurs : Hee-Min Yang   Adam Halim
* Date : 21 septembre 2020
* Mis à jour : 15 septembre 2020
* Description : Comportement du microprocesseur 
                selon le tableau à états décrit ci-dessous
                selon les consignes du TP2 problème 1 du cours 
                INF1900.
* Matériaux: 2 boutons-poussoirs, 1 DEL rouge, 1 DEL vert et 
             un microcontroleur atmega324pa.
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
            case INIT:
                PORTA = ETEINT;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND2))
                    etatPresent = ROUGE0;
                else if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND3))
                    etatPresent = VERT0;
                break;

            case VERT0:
                PORTA = VERT;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND2))
                    etatPresent = ROUGE0;
                break;

            case ROUGE0:
                PORTA = ROUGE;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND3))
                    etatPresent = VERT1;
                break;

            case VERT1:
                PORTA = VERT;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND2))
                    etatPresent = ROUGE1;
                else if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND3))
                    etatPresent = INIT;
                break;

            case ROUGE1:
                PORTA = ROUGE;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND2))
                    etatPresent = VERT1;
        }
        derniereEntreePortD = entreePortD;  
    } 
}
