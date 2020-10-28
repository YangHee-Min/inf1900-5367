#include <avr/io.h>
bool buttonIsPressed(uint8_t button, volatile uint8_t& pin);

void turnMotorPWM(double PWM, double frequency, 
    uint8_t direction, double duration, volatile uint8_t& pin);

void blinking(int del, uint8_t delay, volatile uint8_t& pin);

uint8_t convertPercentInPWM8BitTimer(uint8_t percentage);

void ajustPWM(uint8_t pourcentage, uint8_t ocrnx);

void initialisationUART (void);

void transmissionUART ( uint8_t donnee );
