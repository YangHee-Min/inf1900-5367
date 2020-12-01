#include "sonar.h"
#include "clock.h"
#include "keyboard.h"
#include "uart.h"
#include "servomotor.h"
#include "LEDBar.h"
#include <avr/io.h>

void keyboardPortInit(){

}

void displayMenu(){
    Uart uart = Uart();
    uart.print("1- Définir l'heure de départ\n", 32);
    uart.print("2- Définir l'état d'un dispositif\n", 37);
    uart.print("3- Afficher les actions programmées\n", 38);
    uart.print("4- Programmer une action\n", 26); 
    uart.print("5- Supprimer une action programmée\n", 37)
    uart.print("6- Démarrer la simulation\n", 27);
}

bool validateTimeInput(char time[5]){
    // Assuming time format is "HHMM"
    if(time[0] > '2')
        return false;
    
    if(time[1] )
}

void option1(Keyboard &keyboard){
    Clock clock = Clock(PORTD, PORTD4, PORTD6, PORTA0);
    uart.print("Entrez l’heure et les minutes de départ de la simulation. HHMM\n", 67);
    char time[5];
    char decadeHours = keyboard.readKey();
    char unitHours = keyboard.readKey();
    char decadeMinutes = = keyboard.readKey();
    char unitMinutes = keyboard.readKey();
    char time[5] = {decadeHours, uintHours, decadeMinutes, unitMinutes};
    clock.setTime(time[5]);
}

void option2(LedBar& ledbar, Keyboard &keyboard){
    uart.print("Entrez l’identifiant d’un dispositif suivi de sa valeur de configuration. (A|B|C|D)(0|1) ou (E|F)(000-180)\n", 112);
    char deviceLetter = keyboard.readKey();
    
    switch(deviceLetter){
        case 'A':
        case 'B':
        case 'C':
        case 'D':
            char configurationValue = keyboard.readKey();
            int gateValue = deviceLetter - 'A';
            if(configurationValue == 1){
                ledbar.closeDoor(gateValue);
            }
            if(configurationValue == 0){
                ledbar.opDoor(gateValue);
            }
            ledbar.openDoor
            break;
        case 'E':
        case 'F':
            char configurationValue1 = keyboard.readKey();
            char configurationValue2 = keyboard.readKey();
            char configurationValue3 = keyboard.readKey();

    }
    
}

void option3(){
    uart.print("Entrez l’heure et les minutes de départ de la simulation. HHMM\n", );
    
    
}
void option4(){
    uart.print("Entrez une action à programmer\n", 33);
    char deviceLetter = keyboard.readKey();
    
    switch(deviceLetter){
        case 'A':
        case 'B':
        case 'C':
        case 'D':
            
        case 'E':
        case 'F':
    }
    
}
void option5(){
    uart.print("Entrez le numéro d’une action à supprimer\n", 47);
    char d = keyboard.readKey();
    
}
void option6(){
    uart.print("Option simulation choisie. Début de la simulation...\n", 55);
    
}
int main(){
    
    keyboardPortInit();
    Keyboard keyboard = Keyboard()

    for(;;){

        displayMenu();
        char optionKey = keyboard.readKey();
        
        switch(optionKey){
            case '1':
                option1(keyboard);
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            default:
                uart.print("Option invalide. Retour au menu principal...\n", 45);

        }
    }
}


