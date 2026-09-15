#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <unordered_map>
#include <string>
#include <memory>

class Node;
class Component;
class Circuit{
    private:
        std::string name;
        std::unordered_map<std::string, Node*> nodes;
        std::unordered_map<std::string, Component*> components;
    public:
        Circuit(const std::string &name);
        std::string getName() const;
        bool hasNode(const std::string &name);
        bool hasComponent(const std::string &name);
        void changeName(const std::string &rename);
        void addNode(const std::string &name);
        void addComponent(
            const std::string &type, 
            const std::string &name, 
            const std::string &node1, 
            const std::string &node2, 
            const std::string &value
        );
        void save();
        void deleteNode(const std::string &name);
        void deleteComponent(const std::string &name);
        void toggle(const std::string &name);
        bool hasPath(Node* start, Node* end);
};

#endif