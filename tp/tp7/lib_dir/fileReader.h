#ifndef FILEREADER_H
#define FILEREADER_H

#include "./uart.h"
#include "./led.h"
#include "./motor.h"
#include "./matrixLedThreeByThree.h"

class FileReader{
    public:
        FileReader(Motor* leftMotorPtr, Motor* rightMotorPtr, Led* greenLedPtr, Led* redLedPtr);

        void readFile(volatile uint8_t& FourByFourLedPort, volatile uint8_t& ThreeByThreeLedPort);
    private:
        Uart uart_;
        Motor* leftMotorPtr_;
        Motor* rightMotorPtr_;
        Led* greenLedPtr_;
        Led* redLedPtr_;
                       
        static const int SIZE = 4;
        
        static const uint8_t TURNING_PWM = 128;
        static const uint8_t DBT = 0x01;
        static const uint8_t ATT = 0x02;
        static const uint8_t DAL = 0x44;
        static const uint8_t DET = 0x45;
        static const uint8_t MON = 0x18;
        static const uint8_t MOF = 0x19;
        static const uint8_t MAR1 = 0x60;
        static const uint8_t MAR2 = 0x61;
        static const uint8_t MAV = 0x62;
        static const uint8_t MRE = 0x63;
        static const uint8_t TRD = 0x64;
        static const uint8_t TRG = 0x65;
        static const uint8_t DBC = 0xc0;
        static const uint8_t FBC = 0xc1;
        static const uint8_t FIN = 0xff;
};
#endif