#ifndef SHADOWCIRCUIT_H
#define SHADOWCIRCUIT_H
#include "resistors.h"
#include "node.h"
#include "components.h"
#include "circuit.h"

class ShadowNode : public Node{
    private:
        pair<Node*, Node*> originals;
    public:
        ShadowNode(Node* A, Node* B);
};

class ShadowResistor: public Component{
    private:
        double resistance;
        vector<Resistor*> originals;
    public:     
        ShadowResistor(string name, double value);
        double getValue() const;
        void setValue(const double &newVal);

};

class ShadowCircuit{
    public:
        ShadowCircuit();
        unordered_map<string, Node*> nodes;
        unordered_map<string, Component*> components;
        void addNode(const string &name);
        void addComponent(const string &type, const string &name, const string &node1, const string &node2, const string &value);
};

#endif