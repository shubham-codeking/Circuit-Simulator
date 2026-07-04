#include <unordered_map>
#include <string>
#include "circuit.h"
#include "components.h"
#include "node.h"
using namespace std;

Circuit::Circuit(const string &name):name(name){}

void Circuit::addNode(const string &name){}

void Circuit::addComponent(const string &expression){}

void Circuit::deleteComponent(const string &name){}

void Circuit::deleteNode(const string &name){}

void Circuit::saveCircuit(){}
