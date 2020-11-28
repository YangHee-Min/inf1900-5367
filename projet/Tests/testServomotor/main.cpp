#include "../../Library/lib_dir/servomotor.h"
int main(){
    DDRA = 0xff;
    _delay_ms(1000);
    Servomotor servomotor(PORTA6, &PORTA);
    //servomotor.transmissionServomotorPWM(180);
    
   for(double i = 0; i <= 180; i+=45){
    servomotor.transmissionServomotorPWM(i);
    _delay_ms(10000);
    }
    for(double i = 180; i >= 0; i-=45){
    servomotor.transmissionServomotorPWM(i);
    _delay_ms(10000);
    }
   servomotor.transmissionServomotorPWM(0);
  /*
    _delay_ms(500);
    double angle = 0;
    double pwmDuration = (angle/(double)90 + (double)2);
    PORTA |= (1 << PORTA6);
    _delay_ms(pwmDuration);
    PORTA &= ~(1 << PORTA6);
    */
    
//7
}