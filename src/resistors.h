#include <string>
#ifndef RESISTORS_H
#define RESISTORS_H
using namespace std;

class Resistor{
    private:
        double resistance;
        string Rname;
    public:
        Resistor(string name, double value);
        double getResistance() const;
        void setResistance(double value);
        string getName() const;
        Resistor operator+(const Resistor &other) const;
        Resistor operator|(const Resistor &other) const;
};

#endif