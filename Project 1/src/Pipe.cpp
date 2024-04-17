#include "Pipe.h"

Pipe::Pipe(Node *src, Node *dest, int capacity) : src(src), dest(dest), capacity_(capacity) {
}

Node *Pipe::getSrc() const { return src; }
Node *Pipe::getDest() const { return dest; }
int Pipe::getCapacity() const { return capacity_; }
int Pipe::getFlow() const { return flow_; }

void Pipe::setSrc(Node *newNode) { src = newNode; }
void Pipe::setDest(Node *newNode) { dest = newNode; }
void Pipe::setCapacity(int newCapacity) { capacity_ = newCapacity; }
void Pipe::setFlow(int newFlow) { flow_ = newFlow; }
