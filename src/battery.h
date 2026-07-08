#ifndef BATTERY_H
#define BATTERY_H
#include <string>
#include "components.h"
using namespace std;

class Battery: public Component{
    private:
        double emf;
    public:
        Battery(string name, double value);
        string getValueString() const;
        double getEMF() const;
};

#endif