#include "utilities.h"
#include <iostream>
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