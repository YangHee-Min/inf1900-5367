#include "../../Library/lib_dir/sonar.h"

int main(){
    DDRD |= (1 << PORTD1);
    Sonar sonar = Sonar();
    uint16_t distance = 0;
    for(;;){
        distance = sonar.obstaclesDetection();

        // 6634 is 1 meter
        const uint16_t TWO_METER_MARK = 13278;

        // Green
        if(distance >= TWO_METER_MARK){
            PORTD |= (1 << PORTD1);
            PORTD &= ~(1 << PORTD0);
        }
        // Red
        else if(distance < TWO_METER_MARK){
            PORTD |= (1 << PORTD0);
            PORTD &= ~(1 << PORTD1);
        }
    }
}//