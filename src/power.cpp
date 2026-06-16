#include <iostream>
#include "utilities.h"
#include "power.h"
#include "resistors.h"
using namespace std;

double calcPowerVR(const double &voltage, const double &resistance){
    return (voltage*voltage/resistance);
}
double calcPowerVI(const double &voltage, const double &current){
    return (voltage*current);
}
double calcPowerIR(const double &current, const double &resistance){
    return (current*current*resistance);
}
void powerCalculation(const int &choice){
    double power, current, voltage, resistance;
    switch(choice){
        case 1:{
            cout<<"Current: ";
            cin>>current;
            cout<<"Resistance: ";
            cin>>resistance;
            if (zeroDivisionCheck(resistance)){
                return;
            }
            Resistor R(resistance);
            power = calcPowerIR(current, R.getResistance());
            break;
        }
        case 2:{
            cout<<"Current: ";
            cin>>current;
            cout<<"Voltage: ";
            cin>>voltage;
            power = calcPowerVI(voltage, current);
            break;
        }
        case 3:{
            cout<<"Voltage: ";
            cin>>voltage;
            cout<<"Resistance: ";
            cin>>resistance;
            if (zeroDivisionCheck(resistance)){
                return;
            }
            Resistor R(resistance);
            power = calcPowerVR(voltage, R.getResistance());
            break;
        }
        case 4:{
            return;
        }
        default:{
            cout<<"Enter valid option!!\n\n";
            return;
        }
    }
    cout<<"\nPower = "<<power<<endl<<endl;
    return;
}