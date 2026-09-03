#include "circuitOptimizer.h"
#include <queue>
#include <set>
#include <algorithm>
#include <map>
#include <unordered_set>
#include "shadowCircuit.h"
using namespace std;

struct pathInfo{
    unordered_map<Node*, int> distance;
    unordered_map<Node*, Node*> parentNode;
    unordered_map<Node*,Component*> viaComponent;
};

pathInfo bfs(Node* root){
    pathInfo path;
    path.distance[root] = 0;
    queue<Node*> que;
    que.push(root);
    while (!que.empty()){
        Node* now = que.front();
        que.pop();
        for(auto & [name, comp]: now->getConnections()){
            Node* next = comp->getOtherNode(now);
            if(!path.distance.count(next)){
                path.distance[next] = path.distance[now]+1;
                path.parentNode[next] = now;
                path.viaComponent[next] = comp;
                que.push(next);
            }
        }
    }
    return path;
}

struct Path {
    vector<Node*> nodes;
    vector<Component*> components;
};


Path tracePath(const pathInfo& info, Node* target, Node* src) {
    Path path;
    Node* cur = target;
    while(cur != src){
        path.nodes.push_back(cur);
        path.components.push_back(info.viaComponent.at(cur));
        cur = info.parentNode.at(cur);
    }
    path.nodes.push_back(src);
    reverse(path.nodes.begin(), path.nodes.end());
    reverse(path.components.begin(), path.components.end());
    return path;
}

struct HortonCandidate {
    set<Component*> comps;
    int weight;
};


bool pathsAreDisjoint(const Path& a, const Path& b, Node* root){
    unordered_set<Node*> nodesA;
    for (Node* node: a.nodes) {
        if(node!=root) nodesA.insert(node);
    }
    for (Node* node: b.nodes) {
        if (node!=root && nodesA.contains(node)) return false;
    }
    return true;
}


vector<HortonCandidate> generateCandidates(ShadowCircuit* circuit){
    unordered_map<Node*, pathInfo> trees;
    for (auto& [name, node] : circuit->currentNodes){
        trees[node] = bfs(node);
    }
    map<set<Component*>, int> unique;
    for (auto& [rootName, root] : circuit->currentNodes){
        const pathInfo& info = trees[root];
        for (auto& [componentName, component]: circuit->currentComponents){
            Node* n1 = circuit->currentNodes.at(component->getNodes()[0]);
            Node* n2 = circuit->currentNodes.at(component->getNodes()[1]);
            if (!info.distance.contains(n1) || !info.distance.contains(n2)) continue;
            Path path1 = tracePath(info, n1, root);
            Path path2 = tracePath(info, n2, root);
            if (!pathsAreDisjoint(path1, path2, root)) continue;
            set<Component*> cycle;
            for (Component* c: path1.components) {
                cycle.insert(c);
            }
            for (Component* c: path2.components) {
                cycle.insert(c);
            }
            cycle.insert(component);
            size_t cycleNodes = path1.nodes.size() + path2.nodes.size() - 1;
            if (cycle.size() != cycleNodes) continue;
            int weight = static_cast<int>(cycle.size());
            unique[cycle] = weight;
        }
    }
    vector<HortonCandidate> candidates;
    for (auto& [components, weight]: unique) {
        HortonCandidate candidate;
        candidate.comps = components;
        candidate.weight = weight;
        candidates.push_back(candidate);
    }
    sort(candidates.begin(), candidates.end(),[](const HortonCandidate& a, const HortonCandidate& b){
            return a.weight < b.weight;
        }
    );
    return candidates;
}
