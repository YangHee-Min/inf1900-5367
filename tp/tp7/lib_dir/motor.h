/**********************************
* Fichier: motor.h
* Auteurs: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: 3 novembre 2020
* Mis à jour: 1 novembre 2020
* Description: Définit et implémente les méthodes liées avec le moteur.
***********************************/

#ifndef MOTOR_H
#define MOTOR_H

#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>

class Motor {
public:

    static void turnMotorPWM(double PWM, double frequency, uint8_t direction, double duration, volatile uint8_t& port);
    static uint8_t convertPercentInPWM8BitTimer(uint8_t percentage);
    static void adjustPWM(uint8_t percentage, uint8_t ocrnx);
};

#endif /*MOTOR_H*/
