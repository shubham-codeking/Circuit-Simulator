#ifndef SWITCH_H
#define SWITCH_H
#include <string>
#include "core/components.h"

enum class SwitchState{Open,Closed};
class Switch: public Component{
    private:
        SwitchState state;
    public:
        Switch(std::string name, SwitchState state);
        std::string getValueString() const;
        SwitchState getState() const;
        void toggleSwitch();
};

#endif