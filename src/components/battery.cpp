#include <string>
#include "core/components.h"
#include "components/battery.h"

Battery::Battery(std::string name, double value): Component(name, "Battery"), emf(value){}

double Battery::getEMF() const{
    return emf;
}

std::string Battery::getValueString() const{
    return std::to_string(emf)+"V";
}