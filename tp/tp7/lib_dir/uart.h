/**********************************
* Fichier: uart.h
* Auteurs: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: 3 novembre 2020
* Mis à jour: 1 novembre 2020
* Description: Définit et implémente les méthodes liées avec UART et RS232
***********************************/

#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <avr/eeprom.h> 

class Uart{
    public:
        Uart();
        void transmission(uint8_t info);
    private:
        void initialisation();
};
#endif /*UART_H*/