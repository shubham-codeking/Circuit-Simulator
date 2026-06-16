#include <iostream>
#include "utilities.h"
#include "ohms_law.h"
#include "resistors.h"
using namespace std;

double calcResistance(double voltage, double current){
    return (voltage/current);
}

double calcCurrent(double voltage, double resistance){
    return (voltage/resistance);
}

double calcVoltage(double current, double resistance){
    return (current*resistance);
}

void ohmsLawCalculation(const int &choice){
    double current, voltage, resistance;
    switch (choice)
    {
    case 1:{
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
    }
    case 2:{
        cout<<"Current: ";
        cin>>current;
        cout<<"Resistance: ";
        cin>>resistance;
        if(zeroDivisionCheck(resistance)){
            break;
        }
        Resistor R(resistance);
        voltage=calcVoltage(current, R.getResistance());
        cout<<endl<<"Voltage = "<<voltage<<endl<<endl;
        break;
    }
    case 3:{
        cout<<"Voltage: ";
        cin>>voltage;
        cout<<"Resistance: ";
        cin>>resistance;
        if(zeroDivisionCheck(resistance)){
            break;
        }
        Resistor R(resistance);
        current=calcCurrent(voltage, R.getResistance());
        cout<<endl<<"Current = "<<current<<endl<<endl;
        break;
    }
    case 4:{
        return;
    }
    default:{
        cout<<"Enter valid option!!"<<endl<<endl;
    }
}
}