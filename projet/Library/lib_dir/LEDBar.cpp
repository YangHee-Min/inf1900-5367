/**********************************
* File: LEDBar.cpp
* Authors: Adam Halim, Chun Yang Li, Hee-Min Yang, Jean Janssen
* Date: November 23 2020
* Updated: November 27 2020
* Description: Implementation of methods related to LEDBars.
***********************************/

#include "LEDBar.h"

LEDBar::LEDBar(uint8_t SHC,
        uint8_t STC, 
        uint8_t DS, 
        uint8_t MR, 
        uint8_t OE, 
        volatile uint8_t* portPtr)
        :LEDState_(0)
        ,SHC_(SHC)
        ,STC_(STC)
        ,DS_(DS)
        ,MR_(MR)
        ,OE_(OE)
        ,portPtr_(portPtr)
{
    DDRC |= (1 << SHC) | (1 << STC) | (1 << DS) | (1 << MR) | (1 << OE);
}


void LEDBar::displayState(){
    *portPtr_ |= (1 << MR_); /* Memory mode on */
    *portPtr_ &= ~(1 << OE_); /* Display mode on */
    for(uint8_t i = MAX_BIT_POSITION; i > MIN_BIT_POSITION; i--){
        if(LEDState_ & ( (uint32_t)1 << (i - 1))){
            *portPtr_ |= (1 << DS_); /* DS */
        }
        else{
            *portPtr_ &= ~(1 << DS_); /* DS */
        }

        *portPtr_ &= ~(1 << SHC_);
        *portPtr_ |= (1 << SHC_);
        *portPtr_ &= ~(1 << SHC_);
    }
    
    *portPtr_ &= ~(1 << STC_);
    
    *portPtr_ |= (1 << STC_); /* LATCH */
    
    *portPtr_ &= ~(1 << STC_);
}

void LEDBar::openDoor(uint8_t doorType){
    for(uint8_t i = MAX_LED_BAR_POSITION; i > MIN_BIT_POSITION; i--){
        
        LEDState_ &= ~((uint32_t)1 << ((MAX_LED_BAR_POSITION * doorType) + (i - 1)));
        displayState();
        _delay_ms(ANIMATION_DELAY_MS);
    }
}

void LEDBar::closeDoor(uint8_t doorType)
{
    for(uint8_t i = MIN_BIT_POSITION; i < MAX_LED_BAR_POSITION; i++)
    {
        LEDState_ |= ((uint32_t)1 << (MAX_LED_BAR_POSITION * doorType + i));
        displayState();
        _delay_ms(ANIMATION_DELAY_MS);
    }
}