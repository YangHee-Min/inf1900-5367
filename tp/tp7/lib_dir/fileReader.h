/**********************************
* File: fileReader.h
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 11 2020
* Updated: November 11 2020
* Description: Definition of methods related FileReader.
***********************************/

#ifndef FILEREADER_H
#define FILEREADER_H

#include "./uart.h"
#include "./led.h"
#include "./motor.h"
#include "./matrixLedThreeByThree.h"
#include "./matrixLedFourByFour.h"

class FileReader{
    public:
        // Constructor
        FileReader( Motor* leftMotorPtr, Motor* rightMotorPtr, 
                    Led* greenLedPtr, Led* redLedPtr, 
                    MatrixLedThreeByThree* threeByThreeMatrixPtr, 
                    MatrixLedFourByFour* fourByFourMatrixPtr);

        // Functions
        void readFileFromEeprom();
        void sendFileToEeprom();

    private:
        // Attributes
        Uart uart_;
        Motor* leftMotorPtr_;
        Motor* rightMotorPtr_;
        Led* greenLedPtr_;
        Led* redLedPtr_;
        MatrixLedThreeByThree* threeByThreeMatrixPtr_;
        MatrixLedFourByFour* fourByFourMatrixPtr_;

        // Constants
        static const int MNEMONIC_SIZE = 5;
        enum Mnemonics: uint8_t {   DBT = 0x01,
                                    ATT = 0x02,
                                    DAL = 0x44,
                                    DET = 0x45,
                                    MON = 0x18,
                                    MOF = 0x19,
                                    MAR1 = 0x60,
                                    MAR2 = 0x61,
                                    MAV = 0x62,
                                    MRE = 0x63,
                                    TRD = 0x64,
                                    TRG = 0x65,
                                    DBC = 0xc0,
                                    FBC = 0xc1,
                                    FIN = 0xff};
};
#endif
