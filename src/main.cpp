#include <iostream>
#include "calculations/resistance.h"
#include "ui/menus.h"
#include "calculations/elec_calculation.h"

void run(){
    int choice;
    while (true){
        choice = mainMenu();
        switch (choice){
        case 1:
            elecCalculation();
            break;
        case 2:
            choice = resistanceMenu();
            resistanceCalculation(choice);
            break;
        case 3:
            return;
        default:
            std::cout<<"Enter valid option!!\n\n";
            break;
        }
    }
}

int main(){
    run();
    return 0;
}