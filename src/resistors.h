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
        string getName() const;
};

#endif