#include "menus.h"
#include <iostream>
using namespace std;

int mainMenu(){
    cout<<"======= Circuit Simulator ======="<<endl<<endl;
    cout<<"1. Ohm's Law Calculation\n";
    cout<<"2. Power Calculstion\n";
    cout<<"3. Combination Of Resistance\n";
    cout<<"4. Exit\n";
    int choice;
    cout<<"\nEnter your choice: ";
    cin>>choice;
    cout<<endl;
    return choice;
}

int ohmsLawMenu(){
    int choice;
    cout<<"======= Circuit Simulator ======="<<endl<<endl;
    cout<<"1. Calculate resistance"<<endl;
    cout<<"2. Calculate voltage"<<endl;
    cout<<"3. Calculate current"<<endl;
    cout<<"4. Return to main menu"<<endl;
    cout<<"\nEnter your choice: ";
    cin>>choice;
    cout<<endl;
    return choice;
}

int powerMenu(){
    int choice;
    cout<<"======= Circuit Simulator ======="<<endl<<endl;
    cout<<"1. Calculate via current & resistance"<<endl;
    cout<<"2. Calculate via current & voltage"<<endl;
    cout<<"3. Calculate via voltage & resistance"<<endl;
    cout<<"4. Return to main menu"<<endl;
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