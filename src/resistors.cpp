#include "resistors.h"

Resistor::Resistor(double value){
    resistance = value;
}
double Resistor::getResistance() const{
    return resistance;
}