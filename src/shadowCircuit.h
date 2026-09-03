#ifndef SHADOWCIRCUIT_H
#define SHADOWCIRCUIT_H
#include "resistors.h"
#include "node.h"
#include "components.h"
#include "circuit.h"

enum class ShadowType{
    series,
    parallel
};
class ShadowNode : public Node{
    private:
        pair<Node*, Node*> originals;
    public:
        ShadowNode(const string &name, Node* A, Node* B);
};

class ShadowResistor: public Resistor{
    public:
        vector<Resistor*> originals;
        ShadowType type;
        ShadowResistor(string name, double value, vector<Resistor*> originals, ShadowType type);
};

class ShadowCircuit{
    private:
        int counter = 0;
    public:
        ShadowCircuit();
        string generateShadowName();
        unordered_map<string, Node*> currentNodes;
        unordered_map<string, Component*> currentComponents;
        void addNode(const string &name);
        void addComponent(const string &type, const string &name, const string &node1, const string &node2, const string &value);
};

#endif