#include "string.h"
#include "./uart.h"

class Debug{
public:
    Debug();
    ~Debug();
    void DEBUG_PRINT(const char debugMessage[], const unsigned int size);
private:
    Uart uart_;
};