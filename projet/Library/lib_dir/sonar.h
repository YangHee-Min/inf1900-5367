/**********************************
* File: sonar.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 22 2020
* Updated: December 7 2020
* Description: Definition of methods related to sonar.
***********************************/

#ifndef SONAR_H
#define SONAR_H

#include <avr/io.h>



class Sonar{
    public:
        // Constructor
        Sonar();

        // Functions
        void initialisationISR();
        uint16_t obstacleDetection();

        // Attributes
        static volatile bool detectedObject_;
        static volatile uint16_t lastDistance_;

        // Constants
        static const int CONVERT_US = 8;
        static const int CONVERT_CM = 58;
        static const uint16_t TRIG_FREQUENCY = 120;
        static const uint16_t TWO_METER_TICK_VALUE = 13278; 
    private:
        //Attributes
        volatile uint8_t* portPtr_;
        uint8_t trigPin_;
        uint8_t echoPin_;
          
};
#endif