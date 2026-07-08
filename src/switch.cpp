#include <string>
#include "components.h"
#include "switch.h"

Switch::Switch(string name, SwitchState state): Component(name, "Switch"), state(state){}

SwitchState Switch::getState() const{
    return state;
}

string Switch::getValueString() const{
    return state == SwitchState::Closed ? "ON" : "OFF";
}

void Switch::toggleSwitch(){
    if(state == SwitchState::Open){
    state = SwitchState::Closed;
    }
    else{
    state = SwitchState::Open;
    }
}
