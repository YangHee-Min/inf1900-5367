#include "./fileReader.h"

FileReader::FileReader( Motor* leftMotorPtr, Motor* rightMotorPtr, 
                        Led* greenLedPtr, Led* redLedPtr, 
                        MatrixLedThreeByThree* threeByThreeLedPortPtr, 
                        MatrixLedFourByFour* fourByFourMatrixPtr):
    leftMotorPtr_(leftMotorPtr),
    rightMotorPtr_(rightMotorPtr),
    greenLedPtr_(greenLedPtr),
    redLedPtr_(redLedPtr),
    threeByThreeMatrixPtr_(threeByThreeLedPortPtr),
    fourByFourMatrixPtr_(fourByFourMatrixPtr){
}

void FileReader::readFile(){

    uart_.write("WE IN", 6);
    int duration_ms = 1500;

    uint16_t initialAddress = 0x0002;
    uint16_t address = initialAddress;

    bool programIsRunning = true;
    bool programHasStarted = false;

    uint8_t decrementation = 0;
    uint8_t initLoopAddress = 0;

    for(;programIsRunning;address += 2){
        uint8_t instruction = uart_.readByte(address);
        uint8_t operand = uart_.readByte(address+1);
        
        int att_delay_ms;
        
        if(instruction == DBT){
            uart_.write("dbt\n", MNEMONIC_SIZE);
            programHasStarted = true;
            greenLedPtr_->blink(duration_ms);
        }
        
        if(!programHasStarted)
            continue;

        switch(instruction){

            case ATT:
                uart_.write("att\n", MNEMONIC_SIZE);
                att_delay_ms = 25 * operand;
				_delay_ms(att_delay_ms);
                break;

			case DAL:
                uart_.write("dal\n", MNEMONIC_SIZE);
                if(operand >= 0 && operand <= 127){
                    greenLedPtr_->turnOn();
                    
                }
                else if(operand > 127 && operand <= 254){
                    redLedPtr_->turnOn();
                }
                break;

			case DET:
                uart_.write("det\n", MNEMONIC_SIZE);
				greenLedPtr_->turnOff();
                redLedPtr_->turnOff();
				break;

			case MON:
                uart_.write("mon\n", MNEMONIC_SIZE);
                fourByFourMatrixPtr_->changeLed(operand);
                break;

            case MOF:
                uart_.write("mof\n", MNEMONIC_SIZE);
                fourByFourMatrixPtr_->turnOff();
                break;

            case MAR1:
            case MAR2:
                uart_.write("mar\n", MNEMONIC_SIZE);
                leftMotorPtr_->stop();
                rightMotorPtr_->stop();
				break;

			case MAV:
                uart_.write("mav\n", MNEMONIC_SIZE);
                leftMotorPtr_->adjustPWM(operand, Motor::FORWARD);
                rightMotorPtr_->adjustPWM(operand, Motor::FORWARD);
				break;

			case MRE:
                uart_.write("mre\n", MNEMONIC_SIZE);
               
                leftMotorPtr_->adjustPWM(operand, Motor::BACKWARD);
                rightMotorPtr_->adjustPWM(operand, Motor::BACKWARD);
				break;

			case TRD:  
                uart_.write("trd\n", MNEMONIC_SIZE);
                threeByThreeMatrixPtr_->turnRight();

                leftMotorPtr_->adjustPWM(Motor::TURNING_PWM, Motor::FORWARD);
                rightMotorPtr_->adjustPWM(Motor::TURNING_PWM, Motor::BACKWARD);
                
                _delay_ms(duration_ms);

                leftMotorPtr_->stop();
                rightMotorPtr_->stop();
				
				break;

			case TRG:  
                uart_.write("trg\n", MNEMONIC_SIZE);
                threeByThreeMatrixPtr_->turnLeft();

                leftMotorPtr_->adjustPWM(Motor::TURNING_PWM, Motor::BACKWARD);
                rightMotorPtr_->adjustPWM(Motor::TURNING_PWM, Motor::FORWARD);

                _delay_ms(duration_ms);

                leftMotorPtr_->stop();
                rightMotorPtr_->stop();
                
                break;

            case DBC:
                uart_.write("dbc\n", MNEMONIC_SIZE);
				initLoopAddress = address;
				decrementation = operand;
				break;
                
			case FBC:
                uart_.write("fbc\n", MNEMONIC_SIZE);
                if (decrementation != 0){
                    address = initLoopAddress;
					decrementation--;
				}
				break;

			case FIN:
                uart_.write("fin\n", MNEMONIC_SIZE);
                programIsRunning = false;
                threeByThreeMatrixPtr_->turnOff();
                redLedPtr_->blink(duration_ms);
        }       
    }
}
