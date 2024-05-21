#include "Vertex.h"
#include "Edge.h"


Vertex::Vertex(int id): id(id) {}

int Vertex::getId() const {
    return this->id;
}

std::unordered_map<int, Edge *> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

bool Vertex::isProcessing() const {
    return this->processing;
}

double Vertex::getDist() const {
    return this->dist;
}

Edge *Vertex::getPath() const {
    return this->path;
}

double Vertex::getLatitude() const{
    return this->latitude;
}

double Vertex::getLongitude() const{
    return this->longitude;
}

void Vertex::setId(int id) {
    this->id = id;
}

void Vertex::setVisited(bool visited) {
    this->visited = visited;
}

void Vertex::setProcesssing(bool processing) {
    this->processing = processing;
}

void Vertex::setDist(double dist) {
    this->dist = dist;
}

double Vertex::getMinDist() const {
    return minDist;
}
void Vertex::setMinDist(double minDist){
    this->minDist = minDist;
}
Vertex* Vertex::getPrev() const {
    return prev;
}

void Vertex::setPrev(Vertex* prev) {
    this->prev = prev;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

void Vertex::setLatitude(double latitude) {
    this->latitude = latitude;
}

void Vertex::setLongitude(double longitude) {
    this->longitude = longitude;
}

Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(d, w);
    adj[d->getId()] = newEdge;
    return newEdge;
}

Vertex::Vertex(int id, double lat, double lon): id(id), latitude(lat), longitude(lon) {}

Edge *Vertex::findEdge(int i) {
    auto it = adj.find(i);
    if (it != adj.end()) return it->second;
    return nullptr;
}
