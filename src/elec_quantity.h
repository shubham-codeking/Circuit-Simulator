#ifndef ELEC_QUANTITY_H
#define ELEC_QUANTITY_H
#include <vector>
#include <string>
using namespace std;

class ElecQuantity{
    private:
        string qname;
        double qvalue;
        bool known;
        bool valid;
        string qunit;
        vector<string> tokenizer(const string &input);
        void validator(const vector<string> &tokenList);
    public:
        ElecQuantity(string name, string unit);
        double getValue() const;
        bool isKnown() const;
        bool isValid() const;
        void setValue(double value);
        void print();
        void input();
};

#endif