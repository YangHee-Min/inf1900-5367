/**********************************
* File: fileReader.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 11 2020
* Updated: November 11 2020
* Description: Implementation of methods related FileReader.
***********************************/

#include "./fileReader.h"

//! Constructor of class FileReader
//! \param leftMotorPtr             Pointer to left motor
//! \param rightMotorPtr            Pointer to right motor
//! \param greenLedPtr              Pointer to the green LED
//! \param redLedPtr                Pointer to the red LED
//! \param threeByThreeMatrixPtr    Pointer to the 3D matrix
//! \param fourByFourMatrixPtr      Pointer to the 4D matrix
FileReader::FileReader( Motor* leftMotorPtr, Motor* rightMotorPtr, 
                        Led* greenLedPtr, Led* redLedPtr, 
                        MatrixLedThreeByThree* threeByThreeMatrixPtr, 
                        MatrixLedFourByFour* fourByFourMatrixPtr):
    leftMotorPtr_(leftMotorPtr),
    rightMotorPtr_(rightMotorPtr),
    greenLedPtr_(greenLedPtr),
    redLedPtr_(redLedPtr),
    threeByThreeMatrixPtr_(threeByThreeMatrixPtr),
    fourByFourMatrixPtr_(fourByFourMatrixPtr){
}

//! Function that reads the eeprom and executes the instructions.
void FileReader::readFileFromEeprom(){
    int duration_ms = 1500;

    uint16_t initialAddress = 0x0002;
    uint16_t address = initialAddress;

    bool programIsRunning = true;
    bool programHasStarted = false;

    uint8_t decrementation = 0;
    uint8_t initLoopAddress = 0;

    for(;programIsRunning;address += 2){
        uint8_t instruction = uart_.readByteEeprom(address);
        uint8_t operand = uart_.readByteEeprom(address+1);
        
        int att_delay_ms;
        
        if(instruction == DBT){
            uart_.print("dbt\n", MNEMONIC_SIZE);
            programHasStarted = true;
            greenLedPtr_->blink(duration_ms);
        }
        
        if(!programHasStarted)
            continue;

        switch(instruction){

            case ATT:
                uart_.print("att\n", MNEMONIC_SIZE);
                att_delay_ms = 25 * operand;
				_delay_ms(att_delay_ms);
                break;

			case DAL:
                uart_.print("dal\n", MNEMONIC_SIZE);
                if(operand >= 0 && operand <= 127){
                    greenLedPtr_->turnOn();
                    
                }
                else if(operand > 127 && operand <= 254){
                    redLedPtr_->turnOn();
                }
                break;

			case DET:
                uart_.print("det\n", MNEMONIC_SIZE);
				greenLedPtr_->turnOff();
                redLedPtr_->turnOff();
				break;

			case MON:
                uart_.print("mon\n", MNEMONIC_SIZE);
                fourByFourMatrixPtr_->changeLed(operand);
                break;

            case MOF:
                uart_.print("mof\n", MNEMONIC_SIZE);
                fourByFourMatrixPtr_->turnOff();
                break;

            case MAR1:
            case MAR2:
                uart_.print("mar\n", MNEMONIC_SIZE);
                leftMotorPtr_->stop();
                rightMotorPtr_->stop();
				break;

			case MAV:
                uart_.print("mav\n", MNEMONIC_SIZE);
                leftMotorPtr_->adjustPWM(operand, Motor::FORWARD);
                rightMotorPtr_->adjustPWM(operand, Motor::FORWARD);
				break;

			case MRE:
                uart_.print("mre\n", MNEMONIC_SIZE);
               
                leftMotorPtr_->adjustPWM(operand, Motor::BACKWARD);
                rightMotorPtr_->adjustPWM(operand, Motor::BACKWARD);
				break;

			case TRD:  
                uart_.print("trd\n", MNEMONIC_SIZE);
                threeByThreeMatrixPtr_->turnRight();

                leftMotorPtr_->adjustPWM(Motor::TURNING_PWM, Motor::FORWARD);
                rightMotorPtr_->adjustPWM(Motor::TURNING_PWM, Motor::BACKWARD);
                
                _delay_ms(duration_ms);

                leftMotorPtr_->stop();
                rightMotorPtr_->stop();
				
				break;

			case TRG:  
                uart_.print("trg\n", MNEMONIC_SIZE);
                threeByThreeMatrixPtr_->turnLeft();

                leftMotorPtr_->adjustPWM(Motor::TURNING_PWM, Motor::BACKWARD);
                rightMotorPtr_->adjustPWM(Motor::TURNING_PWM, Motor::FORWARD);

                _delay_ms(duration_ms);

                leftMotorPtr_->stop();
                rightMotorPtr_->stop();
                
                break;

            case DBC:
                uart_.print("dbc\n", MNEMONIC_SIZE);
				initLoopAddress = address;
				decrementation = operand;
				break;
                
			case FBC:
                uart_.print("fbc\n", MNEMONIC_SIZE);
                if (decrementation != 0){
                    address = initLoopAddress;
					decrementation--;
				}
				break;

			case FIN:
                uart_.print("fin\n", MNEMONIC_SIZE);
                programIsRunning = false;
                threeByThreeMatrixPtr_->turnOff();
                redLedPtr_->blink(duration_ms);
        }       
    }
}

//! Function that sends file from USART to the eeprom.
void FileReader::sendFileToEeprom(){
    uart_.print("Starting transmission from USART to EEPROM...\n", 46);
    uart_.print("Please send the eeprom data by RS232\n", 38);
    for(;;){
        uint8_t currentUsartByte = uart_.sendUsartToEeprom();
        if(currentUsartByte == FIN)
            break;

        uart_.sendUsartToEeprom();
    }
    uart_.print("Sent all to eeprom. Now starting program...\n", 45);
}
