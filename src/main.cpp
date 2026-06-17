#include <iostream>
#include <vector>
#include <string>
#include "resistors.h"
#include "resistance.h"
#include "ohms_law.h"
#include "menus.h"
#include "power.h"
#include "utilities.h"
using namespace std;

void run(){
    int choice;
    while (true){
        choice = mainMenu();
        switch (choice){
        case 1:
            choice = ohmsLawMenu();
            ohmsLawCalculation(choice);
            break;
        case 2:
            choice = powerMenu();
            powerCalculation(choice);
            break;
        case 3:
            choice = resistanceMenu();
            resistanceCalculation(choice);
            break;
        case 4:
            return;
        default:
            cout<<"Enter valid option!!"<<endl<<endl;
            break;
        }
    }
}

int main(){
    run();
    return 0;
}