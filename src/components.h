#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <iostream>
#include <string>
using namespace std;

class Node;

class Component
{
private:
    string name;
    Node* n1;
    Node* n2;
public:
    Component(string name);
    string getName() const;
    void connect(Node* n1, Node* n2);
};

#endif