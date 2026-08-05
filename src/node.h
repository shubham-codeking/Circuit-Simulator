#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>
#include <unordered_map>
#include "shadowCircuit.h"
using namespace std;
class Component;

class Node
{
private:
    string name;
    double potential;
    unordered_map<string, Component*> connections;
    ShadowNode* shadow = nullptr;
public:
    Node(const string &name);
    double getPotential() const;
    string getName() const;
    void setPotential(const double &potential);
    void createConnection(Component* component);
    void removeConnection(Component* component);
    int getDegree() const;
    vector<Component*> disconnectNode();
    void setShadow(ShadowNode* shadow);
    unordered_map<string, Component*> getConnections() const;
};
#endif