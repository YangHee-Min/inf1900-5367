#include "./fileReader.h"

FileReader::FileReader():rightWheel_(&OCR1B), leftWheel_(&OCR1B){
}

void FileReader::readFile(uint8_t ledPinGreen, uint8_t ledPinRed, 
                            volatile uint8_t& BicolorLedPort, 
                            uint8_t directionPinLeft,
                            uint8_t directionPinRight, 
                            volatile uint8_t& FourByFourLedPort, 
                            volatile uint8_t& ThreeByThreeLedPort){
    
    uint16_t address = 0x0002;

    bool programIsRunning = true;

    uint8_t decrementation = 0;
    uint8_t initLoopAddress = 0;

    for(;programIsRunning;address += 2){
        uint16_t instructionOperand = uart_.receiveWord((const uint16_t*) address);
        
        uint16_t instruction16Bits = instructionOperand >> 8;
        uint8_t instruction8Bits = instruction16Bits;

        uint16_t operand16Bits = instructionOperand & ~(0xff << 8);
        uint8_t operand8Bits = operand16Bits;
        
        int att_delay_ms;

        switch(instruction8Bits){
            case DBT:
                uart_.write("dbt", SIZE);

                Led::blink(ledPinGreen, ledPinRed, duration_s, BicolorLedPort);
                break;

            case ATT:
                uart_.write("att", SIZE);
                att_delay_ms = 25 * operand8Bits;
				_delay_ms(att_delay_ms);
                break;

			case DAL:
                uart_.write("dal", SIZE);
                if(operand8Bits >= 0 && operand8Bits <= 127){
                    Led::turnOn(ledPinGreen, ledPinRed, BicolorLedPort);
                    
                }
                else if(operand8Bits > 127 && operand8Bits <= 254){
                    Led::turnOn(ledPinRed, ledPinGreen, BicolorLedPort);
                }
                break;

			case DET:
                uart_.write("det", SIZE);
				Led::turnOff(ledPinGreen, BicolorLedPort);
                Led::turnOff(ledPinRed, BicolorLedPort);
				break;

			case MON:
                uart_.write("mon", SIZE);
                FourByFourLedPort = operand8Bits;
                break;

            case MOF:
                uart_.write("mof", SIZE);
                FourByFourLedPort = OFF;
                break;

            case MAR1:
                uart_.write("mar", SIZE);
                motor_.adjustPWM(OFF, directionPinLeft, FORWARD, (*leftWheel_));
                motor_.adjustPWM(OFF, directionPinRight, FORWARD, (*rightWheel_));
                ThreeByThreeLedPort = NOT_MOVING;
                break;

            case MAR2:
                uart_.write("mar", SIZE);
                motor_.adjustPWM(OFF, directionPinLeft, FORWARD, (*leftWheel_));
                motor_.adjustPWM(OFF, directionPinRight, FORWARD, (*rightWheel_));
				ThreeByThreeLedPort = NOT_MOVING;
				break;

			case MAV:
                uart_.write("mav", SIZE);
                motor_.adjustPWM(operand8Bits, directionPinLeft, FORWARD, (*leftWheel_));
                motor_.adjustPWM(operand8Bits, directionPinRight, FORWARD, (*rightWheel_));
				ThreeByThreeLedPort = MOVING_FORWARD;
				break;

			case MRE:
                uart_.write("mre", SIZE);
               
                motor_.adjustPWM(operand8Bits, directionPinLeft, BACKWARD, (*leftWheel_));
                motor_.adjustPWM(operand8Bits, directionPinRight, BACKWARD, (*rightWheel_));
				ThreeByThreeLedPort = MOVING_BACKWARD;
				break;

			case TRD:  
                uart_.write("trd", SIZE);
                motor_.adjustPWM(TURNING_PWM, directionPinLeft, FORWARD,  (*leftWheel_));
                motor_.adjustPWM(TURNING_PWM, directionPinRight, BACKWARD, (*rightWheel_));
				ThreeByThreeLedPort = TURNING_RIGHT;
				break;

			case TRG:  
                uart_.write("trg", SIZE);
                motor_.adjustPWM(TURNING_PWM, directionPinLeft, BACKWARD, (*leftWheel_));
                motor_.adjustPWM(TURNING_PWM, directionPinRight, FORWARD, (*rightWheel_));
                ThreeByThreeLedPort = TURNING_LEFT;
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
                Led::blink(ledPinRed, ledPinGreen, duration_s, BicolorLedPort);
        }       
    }
}
