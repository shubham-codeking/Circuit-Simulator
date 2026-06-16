#include "resistors.h"

Resistor::Resistor(double value){
    resistance = value;
}

double Resistor::getResistance(){
    return resistance;
}