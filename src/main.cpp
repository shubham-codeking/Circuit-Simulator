#include <iostream>
#include <vector>
#include <string>
#include "resistors.h"
#include "resistance.h"
#include "menus.h"
#include "utilities.h"
#include "elec_calculation.h"
using namespace std;

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
            cout<<"Enter valid option!!"<<endl<<endl;
            break;
        }
    }
}

int main(){
    run();
    return 0;
}