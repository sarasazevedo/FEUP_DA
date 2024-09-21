#include "Edge.h"
Edge::Edge(Vertex *dest, double w): dest(dest), weight(w) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

void Edge::setDest(Vertex *dest) {
    this->dest = dest;
}

void Edge::setWeight(double weight) {
    this->weight = weight;
}