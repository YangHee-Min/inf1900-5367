#include "sonar.h"
#include "clock.h"
#include "keyboard.h"
#include "uart.h"


void displayMenu(){
    Uart uart = Uart();
    uart.print("1.Définir l'heure de départ\n", 29)
    uart.print("2.Définir l'état d'un dispositif")
}