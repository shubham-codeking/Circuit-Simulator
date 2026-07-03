#include <string>
#include "resistors.h"
#include <array>
using namespace std;

Resistor::Resistor(string name, double value): Component(name), resistance(value){}
Resistor::Resistor(string name): Component(name), resistance(0){}

double Resistor::getResistance() const{
    return resistance;
}
void Resistor::setResistance(double value){
    resistance=value;
}

Resistor Resistor::operator+(const Resistor &other) const{
    double value;
    value = this->getResistance()+other.getResistance();
    Resistor Req("Equivalent",value);
    return Req;
}
Resistor Resistor::operator|(const Resistor &other) const{
    double value;
    value = 1/((1/this->getResistance())+(1/other.getResistance()));
    Resistor Req("Equivalent",value);
    return Req;
}