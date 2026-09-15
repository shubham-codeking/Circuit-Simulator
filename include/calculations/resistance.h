#ifndef RESISTANCE_H
#define RESISTANCE_H

#include <vector>
#include "components/resistors.h"

std::vector<Resistor> inputResistance();
Resistor seriesResistance(const std::vector<Resistor> &resistors);
Resistor parallelResistance(const std::vector<Resistor> &resistors);
void resistanceCalculation(const int &choice);

#endif