#ifndef FILEREADER_H
#define FILEREADER_H

#include "./uart.h"
#include "./led.h"
#include "./motor.h"

class FileReader{
    public:
        FileReader();
        void readFile(uint8_t ledPinGreen, uint8_t ledPinRed, 
                            volatile uint8_t& BicolorLedPort, 
                            uint8_t directionPinLeft,
                            uint8_t directionPinRight, 
                            volatile uint8_t& FourByFourLedPort, 
                            volatile uint8_t& ThreeByThreeLedPort);
    private:
        Uart uart_;
        Motor motor_;

        int duration_s = 2;

        const uint8_t NOT_MOVING = 0b00100101;
        const uint8_t MOVING_FORWARD = 0b01000101;
        const uint8_t MOVING_BACKWARD = 0b00010101;
        const uint8_t TURNING_RIGHT = 0b00100011;
        const uint8_t TURNING_LEFT = 0b00100110;

        const int SIZE = 4;
        
        const uint8_t TURNING_PWM = 128;
        volatile uint16_t* rightWheel_;
        volatile uint16_t* leftWheel_;
        const uint8_t FORWARD = 0x01;
        const uint8_t BACKWARD = 0x00;
        static const uint8_t OFF = 0x00;
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