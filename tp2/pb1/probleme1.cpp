/*
* Fichier: probleme1.cpp
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
* Table des états:
* +--------------+----+----+--------------+--------+
* | ETAT PRESENT | D2 | D3 | ETAT SUIVANT | SORTIE |
* +--------------+----+----+--------------+--------+
* | INIT         | X  | 1  | VERT0        | ETEINT |
* +--------------+----+----+--------------+--------+
* | VERT0        | 1  | X  | VERT1        | VERT   |
* +--------------+----+----+--------------+--------+
* | VERT1        | 1  | X  | VERT2        | VERT   |
* +--------------+----+----+--------------+--------+
* | VERT2        | 1  | X  | ROUGE0       | VERT   |
* +--------------+----+----+--------------+--------+
* | ROUGE0       | X  | X  | INIT         | ROUGE  |
* +--------------+----+----+--------------+--------+
*/

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
    enum Etat{INIT, VERT0, VERT1, VERT2, ROUGE0};

    //! Définition des sorties possibles (DEL)
    enum Sortie{ETEINT, VERT, ROUGE};

    //! Initialisation de l'état initial du système et de 
    //! la dernière entrée
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
        switch(etatPresent){
            case INIT:
                PORTA = ETEINT;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND3))
                    etatPresent = VERT0;
                break;
            case VERT0:
                PORTA = VERT;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND2))
                    etatPresent = VERT1;
                break;
            case VERT1:
                PORTA = VERT;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND2))
                    etatPresent = VERT2;
                break;
            case VERT2:
                PORTA = VERT;
                if(vientDePeserSurD2OuD3 && pinEstAppuye(PIND2))
                    etatPresent = ROUGE0;
                break;
            case ROUGE0:
                PORTA = ROUGE;
                etatPresent = INIT;
                const double DELAI_ETAT_ROUGE_MS = 1000;
                _delay_ms(DELAI_ETAT_ROUGE_MS);
        }            
        derniereEntreePortD = entreePortD;   
    }
}

