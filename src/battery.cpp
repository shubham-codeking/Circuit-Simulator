#include <string>
#include "components.h"
#include "battery.h"
using namespace std;

Battery::Battery(string name, double value): Component(name), emf(value){}

double Battery::getEMF() const{
    return emf;
}