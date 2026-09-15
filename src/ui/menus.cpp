#include "ui/menus.h"
#include <iostream>

int mainMenu(){
    std::cout<<"======= Circuit Simulator =======\n\n";
    std::cout<<"1. Electrical Calculation\n";
    std::cout<<"2. Combination Of Resistance\n";
    std::cout<<"3. Exit\n";
    int choice;
    std::cout<<"\nEnter your choice: ";
    std::cin>>choice;
    std::cout<<'\n';
    return choice;
}

int resistanceMenu(){
    int choice;
    std::cout<<"======= Circuit Simulator =======\n\n";
    std::cout<<"1. Calculate series resistance\n";
    std::cout<<"2. Calculate parallel resistance\n";
    std::cout<<"3. Calculate resistance of a circuit expression\n";
    std::cout<<"4. Return to main menu\n";
    std::cout<<"\nEnter your choice: ";
    std::cin>>choice;
    std::cout<<'\n';
    return choice; 
}

int saveMenu(){
    int choice;
    std::cout<<"You have a circuit save with the same name\n";
    std::cout<<"1. Overwrite the file.\n";
    std::cout<<"2. Rename this circuit.\n";
    std::cout<<"3. Return to previous menu.\n";
    std::cout<<"\nEnter your choice: ";
    std::cin>>choice;
    std::cout<<'\n';
    return choice;
}