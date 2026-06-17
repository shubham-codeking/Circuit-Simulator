#include <string>
#ifndef RESISTORS_H
#define RESISTORS_H

class Resistor{
    private:
        double resistance;
        string Rname;
    public:
        Resistor(string name, double value);
        double getResistance() const;
        string getName() const;
};

#endif