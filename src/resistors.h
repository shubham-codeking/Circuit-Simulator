#ifndef RESISTORS_H
#define RESISTORS_H

class Resistor{
    private:
        double resistance;
    public:
        Resistor(double value);
        double getResistance() const;
};

#endif