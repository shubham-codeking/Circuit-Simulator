#include "power.h"

double calcPowerVR(const double &voltage, const double &resistance){
    return (voltage*voltage/resistance);
}
double calcPowerVI(const double &voltage, const double &current){
    return (voltage*current);
}
double calcPowerIR(const double &current, const double &resistance){
    return (current*current*resistance);
}