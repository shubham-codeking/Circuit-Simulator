#include <string>
#include "core/components.h"
#include "components/switch.h"

Switch::Switch(std::string name, SwitchState state): Component(name, "Switch"), state(state){}

SwitchState Switch::getState() const{
    return state;
}
std::string Switch::getValueString() const{
    return state == SwitchState::Closed ? "ON" : "OFF";
}

void Switch::toggleSwitch(){
    if(state == SwitchState::Open) state = SwitchState::Closed;
    else state = SwitchState::Open;
}
