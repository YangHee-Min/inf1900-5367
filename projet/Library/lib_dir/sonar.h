#ifndef SONAR_H
#define SONAR_H

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"

class Sonar{
    public:
        Sonar();

        void initialisationISR();
        uint16_t obstacleDetection();

        static volatile bool detectedObject_;
        static volatile uint16_t lastDistance_;

        static const int CONVERT_US = 8;
        static const int CONVERT_CM = 58;
        static const uint16_t TRIG_FREQUENCY = 120;
        static const uint16_t TWO_METER_TICK_VALUE = 13278; 
    private:
        volatile uint8_t* portPtr_;
        uint8_t trigPin_;
        uint8_t echoPin_;
        Uart debug_;
          
};
#endif