#include <iostream>
#include <cmath>
#include "elec_quantity.h"
#include "utilities.h"
using namespace std;

static bool ifDoubleEqual(double a, double b){
    return fabs(a-b)<1e-9;
}

void elecCalculation(){
    ElecQuantity resistance("Resistance","ohm");
    ElecQuantity power("Power","W");
    ElecQuantity current("Current","A");
    ElecQuantity voltage("Voltage","V");
    array<ElecQuantity*,4> quantities = {&resistance, &power, &current, &voltage};
    cin.ignore();
    int knownCount = 0;
    cout<<"======= Circuit Simulator =======\n\n";
    for(ElecQuantity *q : quantities){
        q->input();
        if(!q->isValid()){
            return;
        }
        if(q->isKnown()){
            knownCount++;
            if(zeroDivisionCheck(q->getValue())){
                return;
            }
        }
    }
    if(knownCount<2){
        cout<<"\nNot enough data!!\n\n";
        return;
    }
    else if(knownCount==2){
        if(resistance.isKnown()&&power.isKnown()){
            current.setValue(sqrt(power.getValue()/resistance.getValue()));
            voltage.setValue(power.getValue()/current.getValue());
        }
        else if (resistance.isKnown()&&current.isKnown()){
            voltage.setValue(current.getValue()*resistance.getValue());
            power.setValue(voltage.getValue()*current.getValue());
        }
        else if (resistance.isKnown()&&voltage.isKnown()){
            current.setValue(voltage.getValue()/resistance.getValue());
            power.setValue(voltage.getValue()*current.getValue());
        }
        else if (current.isKnown()&&voltage.isKnown()){
            power.setValue(voltage.getValue()*current.getValue());
            resistance.setValue(voltage.getValue()/current.getValue());
        }
        else if (current.isKnown()&&power.isKnown()){
            voltage.setValue(power.getValue()/current.getValue());
            resistance.setValue(voltage.getValue()/current.getValue());
        }
        else if (voltage.isKnown()&&power.isKnown()){
            current.setValue(power.getValue()/voltage.getValue());
            resistance.setValue(voltage.getValue()/current.getValue());
        }
    }
    else if(knownCount==3){
        if(!voltage.isKnown()&&ifDoubleEqual(resistance.getValue()*current.getValue(),power.getValue()/current.getValue())){
            voltage.setValue(resistance.getValue()*current.getValue());
        }
        else if(!current.isKnown()&&ifDoubleEqual(voltage.getValue()/resistance.getValue(),power.getValue()/voltage.getValue())){
            current.setValue(voltage.getValue()/resistance.getValue());
        }
        else if(!power.isKnown()&&ifDoubleEqual(voltage.getValue()*current.getValue(),current.getValue()*current.getValue()*resistance.getValue())){
            power.setValue(voltage.getValue()*current.getValue());
        }
        else if(!resistance.isKnown()&&ifDoubleEqual(voltage.getValue()/current.getValue(),(voltage.getValue()*voltage.getValue())/power.getValue())){
            resistance.setValue(voltage.getValue()/current.getValue());
        }
        else{
            cout<<"\nInconsistent Input\n\n";
            return;
        }
    }
    cout<<endl;
    for(ElecQuantity *q: quantities){
        q->print();
    }
    cout<<endl;
}