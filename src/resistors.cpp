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
string Resistor::getName() const{
    return Rname;
}