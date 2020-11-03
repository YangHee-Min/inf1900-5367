#include <string>
#include <algorithm>
#include <memory>
#include "./uart.h"

class Debug{

public:
    Debug();
    Debug(Uart uart);
    void DEBUG_PRINT(const std::string debugMessage);
    //void DEBUG_PRINT(const int number);
private:
    std::unique_ptr<Uart> uart_;
};