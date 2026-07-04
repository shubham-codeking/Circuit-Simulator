#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <iostream>
#include <string>
using namespace std;

class Node;
enum class ConnectionStatus{Disconnected, Connected};
class Component
{
private:
    string name;
    Node* n1;
    Node* n2;
    ConnectionStatus status;

public:
    Component(string name);
    string getName() const;
    void connect(Node* n1, Node* n2);
    void disconnect();
    bool isConnected() const;
};

#endif