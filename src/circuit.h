#include <unordered_map>
#include <string>
#include <memory>
#ifndef CIRCUIT_H
#define CIRCUIT_H
#include "shadowCircuit.h"
using namespace std;

class Node;
class Component;
class Circuit{
    private:
        string name;
        unordered_map<string, Node*> nodes;
        unordered_map<string, Component*> components;
    public:
        Circuit(const string &name);
        string getName() const;
        bool hasNode(const string &name);
        bool hasComponent(const string &name);
        void changeName(const string &rename);
        void addNode(const string &name);
        void addComponent(const string &type, const string &name, const string &node1, const string &node2, const string &value);
        void save();
        unique_ptr<ShadowCircuit> shadow() const;
        void deleteNode(const string &name);
        void deleteComponent(const string &name);
        void toggle(const string &name);
        bool hasPath(Node* start, Node* end);
};

#endif