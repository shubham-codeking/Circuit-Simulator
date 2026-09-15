#ifndef BATTERY_H
#define BATTERY_H

#include <string>
#include "core/components.h"


class Battery: public Component{
    private:
        double emf;
    public:
        Battery(std::string name, double value);
        std::string getValueString() const;
        double getEMF() const;
};

#endif