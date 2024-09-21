#include "Graph.h"

Graph::~Graph() = default;

Vertex * Graph::findVertex(const int &id) const {
    auto it = vertexSet.find(id);
    if (it != vertexSet.end()) return it->second;
    return nullptr;
}

bool Graph::addVertex(Vertex *node) {
    if (findVertex(node->getId()) != nullptr) return false;
    vertexSet[node->getId()] = node;
    return true;
}

bool Graph::addBidirectionalEdge(const int &source, const int &dest, double w) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    v2->addEdge(v1, w);
    return true;
}

int Graph::getNumVertex() const {
    return (int)vertexSet.size();
}

unordered_map<int, Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

void Graph::setVertexSet(const unordered_map<int, Vertex *> &set) {
    this->vertexSet = set;
}