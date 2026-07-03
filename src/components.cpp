#include <iostream>
#include <string>
#include "components.h"
#include "node.h"
using namespace std;

Component::Component(string name): name(name) {}

string Component::getName() const{
    return name;
}

void Component::connect(Node* n1, Node* n2){
    this->n1=n1;
    this->n2=n2;
    n1->createConnection(this);
    n2->createConnection(this);
}