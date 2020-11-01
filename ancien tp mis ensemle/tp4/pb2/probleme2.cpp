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
#define DELAI_REBOND 10
#define DELAI_DEBUT 10000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

enum SORTIE{ETEINT, VERT, ROUGE};

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

void initialisation ( void ) {
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

ISR ( TIMER1_COMPA_vect ) {
    minuterieExpiree = 1;
}


ISR ( INT0_vect ) {
    boutonPoussoir = 1;
    // anti-rebond
    // _delay_ms(DELAI_REBOND);
    if (!(PIND & (1 << PIND2)))
         boutonPoussoir = 0;
}

void partirMinuterie ( uint16_t duree ) {
    minuterieExpiree = 0;
    // mode CTC du timer 1 avec horloge divisée par 1024
    // interruption après la durée spécifiée
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A = 0;
    TCCR1B |= (1 << CS10) | (1 << CS12) | (1 << WGM12);
    TCCR1C = 0;
    TIMSK1 |= (1 << OCIE1A);
}

void clignote(int del){
    PORTA = del;
    _delay_ms(100);
    PORTA = ETEINT;
}


int main(){
    initialisation();
    cli();
    _delay_ms(DELAI_DEBUT);
    clignote(ROUGE);
    sei();
    const uint16_t NOMBRE_CYCLES = 7813;
    partirMinuterie(NOMBRE_CYCLES);
    do {
            // attendre qu'une des deux variables soit modifiée
            // par une ou l'autre des interruptions.
    } while ( minuterieExpiree == 0 && boutonPoussoir == 0 );

    // Une interruption s'est produite. Arrêter toute
    // forme d'interruption. Une seule réponse suffit.
    cli ();
    // Verifier la réponse
    if(minuterieExpiree){ //&& boutonPoussoir){
        while(true){
            PORTA = ROUGE;
        }
    }
    else if(!minuterieExpiree && boutonPoussoir){ //&& boutonPoussoir){
        while(true){
            PORTA = VERT;
        }
    }
}
