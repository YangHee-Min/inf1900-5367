#include "./debug.h"

Debug::Debug(){
    uart_ = Uart();
}

Debug::~Debug(){
}

void Debug::DEBUG_PRINT(const char debugMessage[], const unsigned int size){
    uart_.write(debugMessage, size);
}
