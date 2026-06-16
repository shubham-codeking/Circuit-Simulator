#include <iostream>
#include <vector>
#include "resistors.h"
#include "resistance.h"
#include "ohms_law.h"
#include "menus.h"
#include "power.h"
using namespace std;

bool zeroDivisionCheck(const double &quantity){
    if (quantity==0){
        cout<<"\nCan't divide by zero!"<<endl<<endl;
        return true;
    }
    else{
        return false;
    }
}

void ohmsLawCalculation(const int &choice){
    double current, voltage, resistance;
    switch (choice)
    {
    case 1:
        cout<<"Voltage: ";
        cin>>voltage;
        cout<<"Current: ";
        cin>>current;
        if(zeroDivisionCheck(current)){
            break;
        }
        resistance=calcResistance(voltage, current);
        cout<<endl<<"Resistance = "<<resistance<<endl<<endl;
        break;
    case 2:
        cout<<"Current: ";
        cin>>current;
        cout<<"Resistance: ";
        cin>>resistance;
        voltage=calcVoltage(current, resistance);
        cout<<endl<<"Voltage = "<<voltage<<endl<<endl;
        break;
    case 3:
        cout<<"Voltage: ";
        cin>>voltage;
        cout<<"Resistance: ";
        cin>>resistance;
        if(zeroDivisionCheck(resistance)){
            break;
        }
        current=calcCurrent(voltage, resistance);
        cout<<endl<<"Current = "<<current<<endl<<endl;
        break;
    case 4:
        return;
    default:
        cout<<"Enter valid option!!"<<endl<<endl;
    }
}

void powerCalculation(const int &choice){
    double power, current, voltage, resistance;
    switch(choice)
    {
    case 1:
        cout<<"Current: ";
        cin>>current;
        cout<<"Resistance: ";
        cin>>resistance;
        power = calcPowerIR(current, resistance);
        break;
    case 2:
        cout<<"Current: ";
        cin>>current;
        cout<<"Voltage: ";
        cin>>voltage;
        power = calcPowerVI(voltage, current);
        break;
    case 3:
        cout<<"Voltage: ";
        cin>>voltage;
        cout<<"Resistance: ";
        cin>>resistance;
        if (zeroDivisionCheck(resistance)){
            return;
        }
        power = calcPowerVR(voltage, resistance);
        break;
    case 4:
        return;
    default:
        cout<<"Enter valid option!!\n\n";
        return;
    }
    cout<<"\nPower = "<<power<<endl<<endl;
    return;
}

void resistanceCalculation(const int &choice){
    vector<double> resistors;
    double netResistance;
    switch(choice){
        case 1:
            resistors=inputResistance();
            netResistance=seriesResistance(resistors);
            break;
        case 2:
            resistors=inputResistance();
            netResistance=parallelResistance(resistors);
            break;
        case 3:
            return;
        default:
            cout<<"Enter valid option!!"<<endl<<endl;
            return;
    }
    cout<<"\nNet resistance = "<<netResistance<<endl<<endl;
}

void run(){
    int choice;
    while (true){
        choice = mainMenu();
        switch (choice)
        {
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