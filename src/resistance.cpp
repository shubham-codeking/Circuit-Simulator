#include <iostream>
#include <vector>
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
        resistors.push_back(Resistor(tempResistance));
    }
    return resistors;
}

Resistor seriesResistance(const vector<Resistor> &resistors){
    double seriesSum=0;
    for(int i=0;i<resistors.size();i++){
        seriesSum += resistors[i].getResistance();
    }
    return Resistor(seriesSum);
}

Resistor parallelResistance(const vector<Resistor> &resistors){
    double parallelSum=0;
    for(int i=0;i<resistors.size();i++){
            parallelSum+=1/resistors[i].getResistance();
    }
    if(parallelSum!=0){
        parallelSum = 1/parallelSum;
    }
    return Resistor(parallelSum);
}