#include "circuitOptimizer.h"

void optimize(ShadowCircuit* circuit){
    bool changed = true;
    while(changed){
        changed = false;
        changed |= seriesOptimizer(circuit);
        changed |= parallelOptimizer(circuit);
    }
}

static void findSeriesOriginals(Component* comp, double &value,  vector<Resistor*> &originals){
    if(comp->getType()=="Resistor"){
        Resistor* res = static_cast<Resistor*>(comp);
        value += res->getResistance();
        originals.push_back(res);
    }
    else if(comp->getType()=="ShadowResistor"){
        ShadowResistor* res = static_cast<ShadowResistor*>(comp);
        value += res->getResistance();
        originals.insert(originals.end(), res->originals.begin(), res->originals.end());
    }
}
 
static bool seriesOptimizer(ShadowCircuit* currentCircuit){
    bool changed = false;
    vector<Node*> toDelete;
    for(const auto& [name, node]: currentCircuit->currentNodes){
        if(node->getDegree()==2){
            const auto& [name1, comp1] = *node->getConnections().begin();
            const auto& [name2, comp2] = *next(node->getConnections().begin());
            if((comp1->getType()=="Resistor"||comp1->getType()=="ShadowResistor") &&
                (comp2->getType()=="Resistor"||comp2->getType()=="ShadowResistor")){
                toDelete.push_back(node);
                double value = 0;
                vector<Resistor*> originals;
                findSeriesOriginals(comp1, value, originals);
                findSeriesOriginals(comp2, value, originals);
                ShadowResistor* newRes = new ShadowResistor(currentCircuit->generateShadowName(), value, originals);
                currentCircuit->currentComponents.insert({newRes->getName() , newRes});
                newRes->connect(comp1->getOtherNode(node), comp2->getOtherNode(node));
                comp1->disconnect();
                currentCircuit->currentComponents.erase(name1);
                comp2->disconnect();
                currentCircuit->currentComponents.erase(name2);
                changed = true;
                break;
            }
        }
    }
    for(auto& it: toDelete){
        currentCircuit->currentNodes.erase(it->getName());
    }
    return changed;
}

static bool parallelOptimizer(ShadowCircuit* currentCircuit){
    bool changed = false;
    for(const auto& [name, node]: currentCircuit->currentNodes){
        unordered_map<Node*,vector<Resistor*>> groups;
        for(const auto& [Cname, comp]: node->getConnections()){
            if(comp->getType()=="Resistor" || comp->getType()=="ShadowResistor"){
                Resistor* res = static_cast<Resistor*>(comp);
                groups[comp->getOtherNode(node)].push_back(res);
            }
        }
        for(const auto& [otherNode, resistors]: groups){
            if(resistors.size()>=2){
                double value = 0;
                for(const auto& resistor: resistors){
                    value != 0 ? value = 1.0/((1.0/value)+(1.0/resistor->getResistance())) : value = resistor->getResistance();
                    resistor->disconnect();
                    currentCircuit->currentComponents.erase(resistor->getName());
                }
                ShadowResistor* parallel = new ShadowResistor(currentCircuit->generateShadowName(), value, resistors);
                parallel->connect(node, otherNode);
                currentCircuit->currentComponents.insert({parallel->getName(), parallel});
                changed = true;
            }
        }
        if(changed){break;}
    }
    return changed;
}
