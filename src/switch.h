#ifndef SWITCH_H
#define SWITCH_H
#include <string>
#include "components.h"

enum class SwitchState{Open,Closed};
class Switch: public Component{
    private:
        SwitchState state;
    public:
        Switch(string name, SwitchState state);
        SwitchState getState() const;
        void toggleSwitch();
};

#endif