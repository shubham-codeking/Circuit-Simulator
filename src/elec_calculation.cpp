#include <iostream>
#include "elec_quantity.h"
using namespace std;

void elecCalculation(){
    ElecQuantity resistance("Resistance");
    ElecQuantity power("Power");
    ElecQuantity current("Current");
    ElecQuantity voltage("Voltage");
    cin.ignore();
    resistance.input();
    power.input();
    current.input();
    voltage.input();
    return;
}