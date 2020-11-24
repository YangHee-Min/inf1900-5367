#include "sonar.h"

Sonar::Sonar(volatile uint8_t* portPtr, uint8_t trigPin, uint8_t echoPin)
    :portPtr_(portPtr)
    ,trigPin_(trigPin)
    ,echoPin_(echoPin)
{
    initialisationISR();
}

void Sonar::initialisation(){
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli ();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA = 0xff; // PORT A est en mode sortie
    DDRD = 0x00; // PORT D est en mode entreePortD

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC00) | (1 << ISC01);
    // sei permet de recevoir à nouveau des interruptions.
    sei ();

}