#include <iostream>
#include <vector>
using namespace std;

vector<double> inputResistance(){
    int n;
    cout<<"Enter number of resistors: ";
    cin>>n;
    cout<<endl;
    vector<double> resistors;
    double tempResistance;
    for(int i=1;i<=n;i++){
        cout<<"Enter resistance "<<i<<": ";
        cin>>tempResistance;
        if(tempResistance<=0){
            cout<<"\nResistance cannot be negative or zero."<<endl;
            return resistors = {};
        }
        resistors.push_back(tempResistance);
    }
    return resistors;
}

double seriesResistance(const vector<double> &resistors){
    double seriesSum=0;
    for(int i=0;i<resistors.size();i++){
        seriesSum += resistors[i];
    }
    return seriesSum;
}

double parallelResistance(const vector<double> &resistors){
    double parallelSum=0;
    for(int i=0;i<resistors.size();i++){
            parallelSum+=1/resistors[i];
    }
    if(parallelSum!=0){
        parallelSum = 1/parallelSum;
    }
    return parallelSum;
}