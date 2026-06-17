#ifndef OHMS_LAW_H
#define OHMS_LAW_H

double calcCurrent(double voltage, double resistance);
double calcVoltage(double current, double resistance);
double calcResistance(double voltage, double current);
void ohmsLawCalculation(const int &choice);

#endif