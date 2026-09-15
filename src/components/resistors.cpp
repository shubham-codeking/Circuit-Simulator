#include <string>
#include "components/resistors.h"

Resistor::Resistor(std::string name, double value, const std::string& type): Component(name, type), resistance(value){}
Resistor::Resistor(std::string name): Component(name, "Resistor"), resistance(0){}

double Resistor::getResistance() const{
    return resistance;
}
void Resistor::setResistance(double value){
    resistance=value;
}

std::string Resistor::getValueString() const{
    return std::to_string(resistance)+"ohm";
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