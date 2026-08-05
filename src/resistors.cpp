#include <string>
#include "resistors.h"
#include <array>
using namespace std;

Resistor::Resistor(string name, double value, const string& type = "Resistor"): Component(name, type), resistance(value){}
Resistor::Resistor(string name): Component(name, "Resistor"), resistance(0){}

double Resistor::getResistance() const{
    return resistance;
}
void Resistor::setResistance(double value){
    resistance=value;
}

string Resistor::getValueString() const{
    return to_string(resistance)+"ohm";
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