#ifndef RESISTORS_H
#define RESISTORS_H

#include <string>
#include "core/components.h"

class Resistor: public Component{
    private:
        double resistance;
    public:
        Resistor(std::string name, double value, const std::string& type = "Resistor");
        Resistor(std::string name);
        double getResistance() const;
        std::string getValueString() const;
        void setResistance(double value);
        Resistor operator+(const Resistor &other) const;
        Resistor operator|(const Resistor &other) const;
};

#endif