#include <string>
#include "components.h"
#include "battery.h"
using namespace std;

Battery::Battery(string name, double value): Component(name, "Battery"), emf(value){}

double Battery::getEMF() const{
    return emf;
}

string Battery::getValueString() const{
    return to_string(emf)+"V";
}