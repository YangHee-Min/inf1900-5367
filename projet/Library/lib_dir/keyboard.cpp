#include "keyboard.h"

Keyboard::Keyboard(volatile uint8_t *portPtr,
                volatile uint8_t* pinPtr,
                uint8_t demuxS1, 
                uint8_t demuxS0, 
                uint8_t muxS1, 
                uint8_t muxS0,
                uint8_t inputPin)
    :portPtr_(portPtr)
    ,pinPtr_(pinPtr)
    ,demuxS1_(demuxS1)
    ,demuxS0_(demuxS0)
    ,muxS1_(muxS1)
    ,muxS0_(muxS0)
    ,inputPin_(inputPin)
{
}

bool Keyboard::buttonIsPressed(uint8_t button, volatile uint8_t& pinx){
    const double DEBOUNCE_DELAY = 10;
    _delay_ms(INPUT_DELAY);
    if (pinx & (1 << button)){
        _delay_ms(DEBOUNCE_DELAY);
        if (pinx & (1 << button)){
              return true;      
        }
    }
    return false;
}

char Keyboard::readKey(){

    for (currentScoutedKeyValue_ = KEY_0 ;; currentScoutedKeyValue_++){
        if(currentScoutedKeyValue_ >= PAST_END_OF_ENUM){
            currentScoutedKeyValue_ = 0;
        }

        switch(currentScoutedKeyValue_){
            case KEY_0:
                *portPtr_ &= ~((1 << demuxS1_) | (1 << demuxS0_));
                *portPtr_ &= ~((1 << muxS1_) | (1 << muxS0_));
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return '0';
                }
                break;

            case KEY_4:
                *portPtr_ &= ~( (1 << demuxS1_) | (1 << demuxS0_) | (1 << muxS1_));
                *portPtr_ |= (1 << muxS0_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return '4';
                }
                break;

            case KEY_8:
                *portPtr_ &= ~( (1 << demuxS1_) | (1 << demuxS0_) | (1 << muxS0_) );   
                *portPtr_ |= (1 << muxS1_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return '8';
                }
                break;

            case KEY_C:
                *portPtr_ &= ~( (1 << demuxS1_) | (1 << demuxS0_)); 
                *portPtr_ |= (1 << muxS1_) | (1 << muxS0_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return 'C';
                }
                break;
                            
            case KEY_1:
                *portPtr_ &= ~( (1 << demuxS1_) | (1 << muxS1_) | (1 << muxS0_) ); 
                *portPtr_ |= (1 << demuxS0_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return '1';
                }
                break;
                
            case KEY_5:
                *portPtr_ &= ~( (1 << demuxS1_) | (1 << muxS1_)); 
                *portPtr_ |= (1 << demuxS0_) | (1 << muxS0_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return '5';
                }
                break;

            case KEY_9:
                *portPtr_ &= ~( (1 << demuxS1_) | (1 << muxS0_));
                *portPtr_ |= (1 << demuxS0_) | (1 << muxS1_);
                if(buttonIsPressed(inputPin_, PINA)){
                    return '9';
                }
                break;

            case KEY_D:
                *portPtr_ &= ~( (1 << demuxS1_));
                *portPtr_ |= (1 << demuxS0_) | (1 << muxS1_) | (1 << muxS0_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return 'D';
                }
                break;

            case KEY_2:
                *portPtr_ &= ~( (1 << demuxS0_) | (1 << muxS1_));
                *portPtr_ &= ~(1 << muxS0_);
                *portPtr_ |= (1 << demuxS1_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return '2';
                }
                break;  

            case KEY_6:
                *portPtr_ &= ~( (1 << demuxS0_) | (1 << muxS1_));
                *portPtr_ |= (1 << demuxS1_) | (1 << muxS0_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return '6';
                }
                break;

            case KEY_A:
                *portPtr_ &= ~((1 << demuxS0_) | (1 << muxS0_) );   
                *portPtr_ |= (1 << demuxS1_) | (1 << muxS1_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return 'A';
                }
                break;

            case KEY_E:
                *portPtr_ &= ~(1 << demuxS0_); 
                *portPtr_ |=  (1 << demuxS1_) | (1 << muxS1_) | (1 << muxS0_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return 'E';
                }
                break;

            case KEY_3:
                *portPtr_ &= ~((1 << muxS1_) | (1 << muxS0_));
                *portPtr_ |= (1 << demuxS1_) | (1 << demuxS0_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return '3';
                }
                break;

            case KEY_7:
                *portPtr_ &= ~(1 << muxS1_); 
                *portPtr_ |= (1 << demuxS1_) | (1 << demuxS0_) | (1 << muxS0_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return '7';
                }
                break;

            case KEY_B:
                *portPtr_ &= ~(1 << muxS0_); 
                *portPtr_ |= (1 << demuxS1_) | (1 << demuxS0_) | (1 << muxS1_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return 'B';
                }
                break;
                
            case KEY_F:
                *portPtr_ |= (1 << demuxS1_) | (1 << demuxS0_) | (1 << muxS1_) | (1 << muxS0_);
                if(buttonIsPressed(inputPin_, *pinPtr_)){
                    return 'F';
                }
                break;           
        }
    }
}



