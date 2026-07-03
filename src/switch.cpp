#include <string>
#include "components.h"
#include "switch.h"

Switch::Switch(string name, SwitchState state): Component(name), state(state){}

SwitchState Switch::getState() const{
    return state;
}

void Switch::toggleSwitch(){
    if(state == SwitchState::Open){
    state = SwitchState::Closed;
    }
    else{
    state = SwitchState::Open;
    }
}
