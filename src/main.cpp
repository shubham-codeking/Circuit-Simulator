#include <iostream>
#include "ohms_law.h"
using namespace std;

bool zeroDivisionCheck(const double &quantity){
    if (quantity==0){
        cout<<"\nCan't be zero!"<<endl<<endl;
        return true;
    }
    else{
        return false;
    }
}


int menu(){
    int choice;
    cout<<"===== Circuit Simulator ====="<<endl;
    cout<<"1. Calculate resistance"<<endl;
    cout<<"2. Calculate voltage"<<endl;
    cout<<"3. Calculate current"<<endl;
    cout<<"4. Exit"<<endl;
    cout<<"\nEnter your choice: ";
    cin>>choice;
    return choice;
}


void run(){
    double current, voltage, resistance;
    int choice;
    
    while (true){
        choice = menu();
        switch (choice)
        {
        case 1:
            cout<<"Voltage: ";
            cin>>voltage;
            cout<<"Current: ";
            cin>>current;
            if(zeroDivisionCheck(current)){
                break;
            }
            resistance=calcResistance(voltage, current);
            cout<<endl<<"Resistance = "<<resistance<<endl<<endl;
            break;
        case 2:
            cout<<"Current: ";
            cin>>current;
            cout<<"Resistance: ";
            cin>>resistance;
            voltage=calcVoltage(current, resistance);
            cout<<endl<<"Voltage = "<<voltage<<endl<<endl;
            break;
        case 3:
            cout<<"Voltage: ";
            cin>>voltage;
            cout<<"Resistance: ";
            cin>>resistance;
            if(zeroDivisionCheck(resistance)){
                break;
            }
            current=calcCurrent(voltage, resistance);
            cout<<endl<<"Current = "<<current<<endl<<endl;
            break;
        case 4:
            return;
        default:
            cout<<"Enter valid option!!"<<endl<<endl;
        }
    }
}


int main(){
    run();
    return 0;
}