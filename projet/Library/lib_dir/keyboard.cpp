/**********************************
* File: keyboard.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 29 2020
* Updated: December 1 2020
* Description: Implementation of methods related to keyboard.
***********************************/

#include "keyboard.h"

//! Constructor by parameters of Keyboard 
//! \param  portPtr     Pointer to the port (PORTX) on the atmega 
//!                     to which clock is connected
//! \param  pinPtr      Pointer to the port (PINX) on the atmega 
//!                     to which clock is connected
//! \param  demuxS1     S1 pin of demultiplexer
//! \param  demuxS0     S0 pin of demultiplexer
//! \param  muxS1       S1 pin of multiplexer
//! \param  muxS0       S0 pin of multiplexer
//! \param  inputPin    Y pin of multiplexer 
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
    DDRA |=  (1 << demuxS1_) | (1 << demuxS0_) |(1 << muxS1_) |(1 << muxS0_);
    DDRA &= ~(1 << inputPin_);
}

//! Function acting as debouncer for button when 
//! keyboard button is pressed.
//! \param      button  pin linked to button
//! \param      pinx    port linked to keyboard 
//!                     (PINA, PINB, etc)
//! \return     true if button is pressed for 
//!             DEBOUNCE_DELAY. False if not.
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

//! Function to assert that char pressed by user 
//! is only being returned once.
//! \return     char value pressed by user.
char Keyboard::readKey(){
    char returnValue = readKeyboard();
    while(*pinPtr_ & (1 << inputPin_)){}
    uart_.transmission(returnValue);
    return returnValue;
}

//! Function to read the key inputted by the user.
//! \return     char value of key pressed by user
char Keyboard::readKeyboard(){

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




