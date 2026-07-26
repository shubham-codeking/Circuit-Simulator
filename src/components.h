#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <vector>
#include <string>
using namespace std;

class Node;
enum class ConnectionStatus{Disconnected, Connected};
class Component
{
private:
    string name;
    string type;
    Node* n1;
    Node* n2;
    ConnectionStatus status;

public:
    Component(string name, string type);
    string getName() const;
    string getType() const;
    virtual string getValueString() const;
    Node* getOtherNode(Node* current) const;
    vector<string> getNodes() const;
    void connect(Node* n1, Node* n2);
    void disconnect();
    bool isConnected() const;
};

#endif