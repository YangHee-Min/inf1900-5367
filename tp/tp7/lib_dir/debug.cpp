#include "./debug.h"

Debug::Debug(){
    uart_ = Uart();
}

Debug::~Debug(){
}

void Debug::DEBUG_PRINT(const char debugMessage[], const unsigned int size){
    for ( unsigned int currentIndex = 0; currentIndex < size; currentIndex++ ) {
            uart_.transmission(currentIndex);
        }
}
