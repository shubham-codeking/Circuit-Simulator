#include <string>
#include <array>
#include "components.h"
#ifndef RESISTORS_H
#define RESISTORS_H
using namespace std;

class Resistor: public Component{
    private:
        double resistance;
    public:
        Resistor(string name, double value, const string& type = "Resistor");
        Resistor(string name);
        double getResistance() const;
        string getValueString() const;
        void setResistance(double value);
        Resistor operator+(const Resistor &other) const;
        Resistor operator|(const Resistor &other) const;
};

#endif