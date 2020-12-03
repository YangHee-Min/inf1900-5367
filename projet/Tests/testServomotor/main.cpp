#define CLASS 1
#include "../../Library/lib_dir/servomotor.h"
int main(){
    _delay_ms(1000);
    Servomotor servomotor(PORTA7, &PORTA);
    //servomotor.transmissionServomotorPWM(180);
  #if CLASS == 1
  servomotor.changeAngle(0);
  _delay_ms(1000);
  for(double i = 0; i <= 180; i+=45){
    servomotor.changeAngle(i);
    _delay_ms(500);
    }
  for(double i = 180; i >= 0; i-=45){
    servomotor.changeAngle(i);
    _delay_ms(100);
    }
  #endif
  #if CLASS == 0
  uint8_t angle = 180;
  const double ANGLE_TO_MS_FACTOR = 1.1/180;
  const double MINIMUM_MS_VALUE = 0.9;
  double pwmDuration = angle * ANGLE_TO_MS_FACTOR + MINIMUM_MS_VALUE;
  double time = 1.9;
  PORTA |= (1 << PORTA6);
  _delay_ms(pwmDuration);
  PORTA &= ~(1 << PORTA6);
  #endif
    
//
}