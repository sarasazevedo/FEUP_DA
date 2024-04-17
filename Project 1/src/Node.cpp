#include "Node.h"
#include "Pipe.h"
using namespace std;


Node::Node(int id, string cod): id_(id), code_(move(cod)) {
}

Node::~Node() {
    for (Pipe *pipe: _adj) { delete pipe; }
}

// Getters
int Node::getID() const { return id_; }
string Node::getCode() const { return code_; }
bool Node::isVisited() const { return visited_; }
bool Node::isProcessing() const { return processing_; }
int Node::getIndegree() const { return indegree_; }
int Node::getNum() const { return num_; }
int Node::getLow() const { return low_; }
const vector<Pipe *> &Node::getAdj() const { return _adj; }

const vector<Pipe *> &Node::getIncoming() const { return _incoming; }

Pipe *Node::getPath() const { return path; }


//setters

void Node::setID(const int newID) { id_ = newID; }
void Node::setCod(std::string newCod) { code_ = move(newCod); }
void Node::setVisited(const bool visited) { visited_ = visited; }
void Node::setIsProcessing(const bool processing) { processing_ = processing; }
void Node::setIndegree(const int newIndegree) { indegree_ = newIndegree; }
void Node::setNum(const int num) { num_ = num; }
void Node::setLow(const int low) { low_ = low; }
void Node::setAdj(const std::vector<Pipe *> &adj) { _adj = adj; }
void Node::setPath(Pipe *newPath) { path = newPath; }

void Node::removeOutgoingPipes() {
    auto it = _adj.begin();
    while (it != _adj.end()) {
        Pipe *edge = *it;
        it = _adj.erase(it);
        deleteEdge(edge);
    }
}

void Node::deleteEdge(Pipe *pipe) {
    Node *dest = pipe->getDest();
    // Remove the corresponding edge from the _incoming list
    auto it = dest->_incoming.begin();
    while (it != dest->_incoming.end()) {
        if ((*it)->getSrc()->getCode() == code_) {
            it = dest->_incoming.erase(it);
        }
        else {
            ++it;
        }
    }
    delete pipe;
}

bool Node::removeEdge(const string &in) {
    bool removedEdge = false;
    auto it = _adj.begin();
    while (it != _adj.end()) {
        Pipe *pipe = *it;
        Node *dest = pipe->getDest();
        if (dest->getCode() == in) {
            it = _adj.erase(it);
            deleteEdge(pipe);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            ++it;
        }
    }
    return removedEdge;
}



bool Node::operator!=(const Node &rhs) const { return id_ != rhs.id_ || code_ != rhs.code_; }
bool Node::operator==(const Node &rhs) const { return id_ == rhs.id_ && code_ == rhs.code_; }

void Node::addPipe(Pipe *pipe) {
    _adj.push_back(pipe);
    pipe->getDest()->indegree_++;
    pipe->getDest()->_incoming.push_back(pipe);
}
