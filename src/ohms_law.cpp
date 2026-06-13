#include <ohms_law.h>

double calcResistance(double voltage, double current){
    return (voltage/current);
}

double calcCurrent(double voltage, double resistance){
    return (voltage/resistance);
}

double calcVoltage(double current, double resistance){
    return (current*resistance);
}

