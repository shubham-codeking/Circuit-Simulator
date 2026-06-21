#include <string>
#include "resistors.h"
using namespace std;

Resistor::Resistor(string name, double value){
    resistance = value;
    Rname = name;
}
double Resistor::getResistance() const{
    return resistance;
}
void Resistor::setResistance(double value){
    resistance=value;
}
string Resistor::getName() const{
    return Rname;
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