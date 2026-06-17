#include <iostream>
#include <vector>
#include <string>
#include "resistors.h"
using namespace std;

vector<Resistor> inputResistance(){
    int n;
    cout<<"Enter number of resistors: ";
    cin>>n;
    cout<<endl;
    vector<Resistor> resistors;
    double tempResistance;
    for(int i=1;i<=n;i++){
        cout<<"Enter resistance "<<i<<": ";
        cin>>tempResistance;
        if(tempResistance<=0){
            cout<<"\nResistance cannot be negative or zero."<<endl;
            return resistors = {};
        }
        string name = "R"+char(i);
        resistors.push_back(Resistor(name,tempResistance));
    }
    return resistors;
}

Resistor seriesResistance(const vector<Resistor> &resistors){
    double seriesSum=0;
    for(int i=0;i<resistors.size();i++){
        seriesSum += resistors[i].getResistance();
    }
    return Resistor("Rs", seriesSum);
}

Resistor parallelResistance(const vector<Resistor> &resistors){
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
    vector<Resistor> resistors;
    Resistor netResistance("Net_R",0);
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
            return;
        }
        default:{
            cout<<"Enter valid option!!"<<endl<<endl;
            return;
        }
    }
    cout<<"\nNet resistance = "<<netResistance.getResistance()<<endl<<endl;
}
