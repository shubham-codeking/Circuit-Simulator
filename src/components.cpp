#include <vector>
#include <string>
#include "components.h"
#include "node.h"
using namespace std;

Component::Component(string name, string type):
    name(name),
    type(type), 
    n1(nullptr), 
    n2(nullptr), 
    status(ConnectionStatus::Disconnected){}

string Component::getName() const{
    return name;
}

string Component::getType() const{
    return type;
}

vector<string> Component::getNodes() const{
    if(this->isConnected()){
        return {n1->getName(),n2->getName()};
    }
    else{
        return {};
    }
}

void Component::connect(Node* n1, Node* n2){
    this->n1=n1;
    this->n2=n2;
    n1->createConnection(this);
    n2->createConnection(this);
    status=ConnectionStatus::Connected;
}

void Component::disconnect(){
    if(status==ConnectionStatus::Disconnected){
        return;
    }
    status=ConnectionStatus::Disconnected;
    n1->removeConnection(this);
    n2->removeConnection(this);
}

bool Component::isConnected() const{
    return status==ConnectionStatus::Connected;
}