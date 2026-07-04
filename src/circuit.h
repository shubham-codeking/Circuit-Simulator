#include <unordered_map>
#include <string>
#ifndef CIRCUIT_H
#define CIRCUIT_H
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
        void addNode(const string &name);
        void addComponent(const string &expression);
        void saveCircuit();
        void deleteNode(const string &name);
        void deleteComponent(const string &name);
};

#endif