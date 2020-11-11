#include "./fileReader.h"

FileReader::FileReader(Motor* leftMotorPtr, Motor* rightMotorPtr, Led* greenLedPtr, Led* redLedPtr):
    leftMotorPtr_(leftMotorPtr),
    rightMotorPtr_(rightMotorPtr),
    greenLedPtr_(greenLedPtr),
    redLedPtr_(redLedPtr){
}

void FileReader::readFile(volatile uint8_t& FourByFourLedPort, 
                            volatile uint8_t& ThreeByThreeLedPort){
    
    int right = 1;
    int left = -1;
    int duration_s = 2;

    uint16_t address = 0x0002;
    bool programIsRunning = true;
    int NORTH = 0;
    MatrixLedThreeByThree matrixLed = MatrixLedThreeByThree(NORTH);
    uint8_t decrementation = 0;
    uint8_t initLoopAddress = 0;

    for(;programIsRunning;address += 2){
        uint16_t instructionOperand = uart_.receiveWord(address);
        
        uint16_t instruction16Bits = instructionOperand >> 8;
        uint8_t instruction8Bits = instruction16Bits;

        uint16_t operand16Bits = instructionOperand & ~(0xff << 8);
        uint8_t operand8Bits = operand16Bits;
        
        int att_delay_ms;

        switch(instruction8Bits){
            case DBT:
                uart_.write("dbt", SIZE);
                greenLedPtr_->blink(duration_s);
                break;

            case ATT:
                uart_.write("att", SIZE);
                att_delay_ms = 25 * operand8Bits;
				_delay_ms(att_delay_ms);
                break;

			case DAL:
                uart_.write("dal", SIZE);
                if(operand8Bits >= 0 && operand8Bits <= 127){
                    greenLedPtr_->turnOn();
                    
                }
                else if(operand8Bits > 127 && operand8Bits <= 254){
                    redLedPtr_->turnOn();
                }
                break;

			case DET:
                uart_.write("det", SIZE);
				greenLedPtr_->turnOff();
                redLedPtr_->turnOff();
				break;

			case MON:
                uart_.write("mon", SIZE);
                FourByFourLedPort = operand8Bits;
                break;

            case MOF:
                uart_.write("mof", SIZE);
                FourByFourLedPort = Led::OFF;
                break;

            case MAR1:
            case MAR2:
                uart_.write("mar", SIZE);
                leftMotorPtr_->stop();
                rightMotorPtr_->stop();
				break;

			case MAV:
                uart_.write("mav", SIZE);
                leftMotorPtr_->adjustPWM(operand8Bits, Motor::FORWARD);
                rightMotorPtr_->adjustPWM(operand8Bits, Motor::FORWARD);
				break;

			case MRE:
                uart_.write("mre", SIZE);
               
                leftMotorPtr_->adjustPWM(operand8Bits, Motor::BACKWARD);
                rightMotorPtr_->adjustPWM(operand8Bits, Motor::BACKWARD);
				break;

			case TRD:  
                uart_.write("trd", SIZE);
                leftMotorPtr_->adjustPWM(TURNING_PWM, Motor::FORWARD);
                rightMotorPtr_->adjustPWM(TURNING_PWM, Motor::BACKWARD);
                
                leftMotorPtr_->delaySeconds(duration_s);
                rightMotorPtr_->delaySeconds(duration_s);

                leftMotorPtr_->stop();
                rightMotorPtr_->stop();

				ThreeByThreeLedPort = matrixLed.ledDirection(right);
				break;

			case TRG:  
                uart_.write("trg", SIZE);
                leftMotorPtr_->adjustPWM(TURNING_PWM, Motor::BACKWARD);
                rightMotorPtr_->adjustPWM(TURNING_PWM, Motor::FORWARD);

                leftMotorPtr_->delaySeconds(duration_s);
                rightMotorPtr_->delaySeconds(duration_s);

                leftMotorPtr_->stop();
                rightMotorPtr_->stop();
                
                ThreeByThreeLedPort = matrixLed.ledDirection(left);
                break;

            case DBC:
                uart_.write("dbc", SIZE);
				initLoopAddress = address;
				decrementation = operand8Bits;
				break;
                
			case FBC:
                uart_.write("fbc", SIZE);
                if (decrementation != 0){
                    address = initLoopAddress;
					decrementation--;
				}
				break;

			case FIN:
                uart_.write("fin", SIZE);
                programIsRunning = false;
                redLedPtr_->blink(duration_s);
        }       
    }
}
