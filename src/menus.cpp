#include "menus.h"
#include <iostream>
#include <array>
using namespace std;

int mainMenu(){
    cout<<"======= Circuit Simulator ======="<<endl<<endl;
    cout<<"1. Electrical Calculation\n";
    cout<<"2. Combination Of Resistance\n";
    cout<<"3. Exit\n";
    int choice;
    cout<<"\nEnter your choice: ";
    cin>>choice;
    cout<<endl;
    return choice;
}

int resistanceMenu(){
    int choice;
    cout<<"======= Circuit Simulator ======="<<endl<<endl;
    cout<<"1. Calculate series resistance"<<endl;
    cout<<"2. Calculate parallel resistance"<<endl;
    cout<<"3. Calculate resistance of a circuit expression"<<endl;
    cout<<"4. Return to main menu"<<endl;
    cout<<"\nEnter your choice: ";
    cin>>choice;
    cout<<endl;
    return choice; 
}

int saveMenu(){
    int choice;
    cout<<"You have a circuit save with the same name\n";
    cout<<"1. Overwrite the file.\n";
    cout<<"2. Rename this circuit.\n";
    cout<<"3. Return to previous menu.\n";
    cout<<"\nEnter your choice: ";
    cin>>choice;
    cout<<endl;
    return choice;
}