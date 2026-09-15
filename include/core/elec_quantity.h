#ifndef ELEC_QUANTITY_H
#define ELEC_QUANTITY_H
#include <vector>
#include <string>

class ElecQuantity{
    private:
        std::string qname;
        double qvalue;
        bool known;
        bool valid;
        std::string qunit;
        std::vector<std::string> tokenizer(const std::string &input);
        void validator(const std::vector<std::string> &tokenList);
    public:
        ElecQuantity(std::string name, std::string unit);
        double getValue() const;
        bool isKnown() const;
        bool isValid() const;
        void setValue(double value);
        void print();
        void input();
};

#endif