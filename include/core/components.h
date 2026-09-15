#ifndef COMPONENTS_H
#define COMPONENTS_H
#include <vector>
#include <string>

class Node;
enum class ConnectionStatus{Disconnected, Connected};
class Component
{
private:
    std::string name;
    std::string type;
    Node* n1;
    Node* n2;
    ConnectionStatus status;

public:
    Component(std::string name, std::string type);
    virtual ~Component() = default;
    std::string getName() const;
    std::string getType() const;
    virtual std::string getValueString() const = 0;
    Node* getOtherNode(Node* current) const;
    std::vector<std::string> getNodes() const;
    void connect(Node* n1, Node* n2);
    void disconnect();
    bool isConnected() const;
};

#endif