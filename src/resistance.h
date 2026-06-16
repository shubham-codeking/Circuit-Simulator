#include <vector>
#include "resistors.h"
using namespace std;

vector<Resistor> inputResistance();
Resistor seriesResistance(const vector<Resistor> &resistors);
Resistor parallelResistance(const vector<Resistor> &resistors);