#include "./debug.h"

Debug::Debug(){
    uart_ = std::make_unique<Uart>(Uart());
}

Debug::Debug(Uart uart){
    uart_ = std::make_unique<Uart>(&uart);
}

Debug::DEBUG_PRINT(const std::string message){
    std::for_each(&message.begin(), &message.end(), uart_->transmission);
}

