#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>
#include <unordered_map>

class Component;
class Node
{
private:
    std::string name;
    double potential;
    std::unordered_map<std::string, Component*> connections;
public:
    Node(const std::string &name);
    double getPotential() const;
    std::string getName() const;
    void setPotential(const double &potential);
    void createConnection(Component* component);
    void removeConnection(Component* component);
    int getDegree() const;
    std::vector<Component*> disconnectNode();
    std::unordered_map<std::string, Component*> getConnections() const;
};
#endif