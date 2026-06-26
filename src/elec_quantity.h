#ifndef ELEC_QUANTITY_H
#define ELEC_QUANTITY_H
#include <string>
using namespace std;

class ElecQuantity{
    private:
        string qname;
        double qvalue;
        bool known;
        bool valid;
    public:
        ElecQuantity(string name);
        double getValue() const;
        bool isKnown() const;
        bool isValid() const;
        void setValue(double value);
        void input();
};

#endif