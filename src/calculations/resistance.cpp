#include <iostream>
#include <vector>
#include <string>
#include "components/resistors.h"
#include "utilities/utilities.h"
#include <map>
#include <stack>

static Resistor postfixCalculation(const std::vector<std::string> &postfixTokens, const std::map<std::string,Resistor> &Resistors){
    Resistor netResistance("netResistance");
    std::stack<Resistor> stc;
    for(std::string token: postfixTokens){
        if(isOperand(token)){
            if(Resistors.contains(token)){
                stc.push(Resistors.at(token));
            }
            else{
                std::cout<<"\nResistor not found\n\n";
                netResistance.setResistance(0);
                return netResistance;
            }
        }
        else{
            Resistor R1 = stc.top();
            stc.pop();
            Resistor R2 = stc.top();
            stc.pop();
            if(token=="||") netResistance = R1 | R2;
            else if(token=="+") netResistance = R1 + R2;
            stc.push(netResistance);
        }
    }
    netResistance = stc.top();
    return netResistance;
}

std::vector<Resistor> inputResistance(){
    int n;
    std::cout<<"Enter number of resistors: ";
    std::cin>>n;
    std::cout<<'\n';
    std::vector<Resistor> resistors;
    double tempResistance;
    for(int i=1;i<=n;i++){
        std::cout<<"Enter resistance "<<i<<": ";
        std::cin>>tempResistance;
        if(tempResistance<=0){
            std::cout<<"\nResistance cannot be negative or zero.\n";
            return resistors = {};
        }
        std::string name = "R"+std::to_string(i);
        resistors.push_back(Resistor(name,tempResistance));
    }
    return resistors;
}

Resistor seriesResistance(const std::vector<Resistor> &resistors){
    double seriesSum=0;
    for(int i=0;i<resistors.size();i++){
        seriesSum += resistors[i].getResistance();
    }
    return Resistor("Rs", seriesSum);
}

Resistor parallelResistance(const std::vector<Resistor> &resistors){
    double parallelSum=0;
    for(int i=0;i<resistors.size();i++){
            parallelSum+=1/resistors[i].getResistance();
    }
    if(parallelSum!=0){
        parallelSum = 1/parallelSum;
    }
    return Resistor("Rp", parallelSum);
}

void resistanceCalculation(const int &choice){
    std::vector<Resistor> resistors;
    Resistor netResistance("Net_R");
    switch(choice){
        case 1:{
            resistors=inputResistance();
            netResistance=seriesResistance(resistors);
            break;
        }
        case 2:{
            resistors=inputResistance();
            netResistance=parallelResistance(resistors);
            break;
        }
        case 3:{
            resistors=inputResistance();
            std::map<std::string,Resistor> resistorMap;
            for(Resistor R: resistors){
                resistorMap.insert({R.getName(),R});
            }
            std::string expression;
            std::cout<<"\nEnter expression: \n";
            std::cin.ignore();
            std::getline(std::cin,expression);
            std::vector<std::string> tokens;
            if(expressionValidator(expression)){
                tokens = tokenizer(expression);
            }
            if(!tokens.empty()){
                if(tokenValidator(tokens)){
                    tokens = infixToPostfix(tokens);
                    netResistance = postfixCalculation(tokens, resistorMap);
                    break;
                }
                else{
                    std::cout<<"\nInvalid input\n\n";
                    return;
                }
            }
            else{
                std::cout<<"\nInvalid input\n\n";
                return;
            }
        }
        case 4:{
            return;
        }
        default:{
            std::cout<<"Enter valid option!!\n\n";
            return;
        }
    }
    std::cout<<"\nNet resistance = "<<netResistance.getResistance()<<"\n\n";
}
