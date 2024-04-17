//
// Created by yves on 31-03-2024.
//

#include "Network.h"


Node *Network::findVertex(const string &code) const {
    if (nodeSet.find(code) == nodeSet.end()) {
        return nullptr;
    }
    return nodeSet.at(code);
}

bool Network::addVertex(Node *node) {
    if (findVertex(node->getCode()) != nullptr) {
        return false;
    }
    nodeSet[node->getCode()] = node;
    return true;
}

bool Network::removeVertex(const std::string &code) {
    Node *node = findVertex(code);
    if (node == nullptr) {
        return false;
    }
    node->removeOutgoingPipes();
    for (auto u: nodeSet) {
        u.second->removeEdge(node->getCode());
    }
    nodeSet.erase(code);
    delete node;
    return true;
}

bool Network::removeEdge(const string &source, const string &dest) {
    Node * srcVertex = findVertex(source);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

bool Network::addEdge(const string &src, const string &dest, const double capacity) {
    auto source = findVertex(src);
    auto destination = findVertex(dest);
    if (source == nullptr || destination == nullptr) {
        return false;
    }
    auto pipe = new Pipe(source, destination, capacity);
    source->addPipe(pipe);
    pipeSet_.push_back(pipe);
    return true;
}

int Network::getNumVertex() const {
    return nodeSet.size();
}

unordered_map<string, Node *> Network::getNodeSet() const {
    return nodeSet;
}

vector<Pipe *> Network::getPipes() const {
    return pipeSet_;
}
