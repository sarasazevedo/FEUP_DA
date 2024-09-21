#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
#include <iomanip>
#include <unordered_set>
#include <chrono>
#include "RoutingManager.h"
using namespace std;

RoutingManager::RoutingManager() {
    network = Graph();
}

void RoutingManager::readExtraFullyConnectedGraph(unsigned int nodeNumber) {
    std::string line;
    std::ifstream edgesFile;
    std::ifstream nodesFile;

    edgesFile.open("../dataset/Extra_Fully_Connected_Graphs/edges_" + std::to_string(nodeNumber) + ".csv");
    nodesFile.open("../dataset/Extra_Fully_Connected_Graphs/nodes.csv");

    if (!edgesFile.is_open() || !nodesFile.is_open()) {
        cout << "Error: Could not open file" << endl;
        return;
    }

    getline(nodesFile, line);
    int i = 0;
    while (getline(nodesFile, line) && i < nodeNumber) {
        std::stringstream lineStream(line);
        string id, x, y;
        if (std::getline(lineStream, id, ',') && getline(lineStream, x, ',') && getline(lineStream, y)) {
            if (y.back() == '\r') y.pop_back(); // Remove last character (which is a '\r' character)
            auto *node = new Vertex(stoi(id), stod(x), stod(y));
            network.addVertex(node);
        }
        i++;
    }

    while (getline(edgesFile, line)) {
        std::stringstream lineStream(line);
        string src, dest, distance;
        if (getline(lineStream, src, ',') && getline(lineStream, dest, ',') && getline(lineStream, distance)) {
            if (distance.back() == '\r') distance.pop_back(); // Remove last character (which is a '\r' character)
            network.addBidirectionalEdge(stoi(src), stoi(dest), stod(distance));
        }
    }


}

void RoutingManager::readRealWorldGraph(string folderName) {
    std::string line;
    std::ifstream edgesFile;
    std::ifstream nodesFile;

    edgesFile.open("../dataset/Real-world Graphs/" + folderName + "/edges.csv");
    nodesFile.open("../dataset/Real-world Graphs/" + folderName + "/nodes.csv");

    if (!edgesFile.is_open() || !nodesFile.is_open()) {
        cout << "Error: Could not open file" << endl;
        return;
    }
    getline(edgesFile, line);
    getline(nodesFile, line);
    while (getline(nodesFile, line)) {
        std::stringstream lineStream(line);
        string id, x, y;
        if (std::getline(lineStream, id, ',') && getline(lineStream, x, ',') && getline(lineStream, y)) {
            if (y.back() == '\r') y.pop_back(); // Remove last character (which is a '\r' character)
            auto *node = new Vertex(stoi(id), stod(x), stod(y));
            network.addVertex(node);
        }
    }

    while (getline(edgesFile, line)) {
        std::stringstream lineStream(line);
        string src, dest, distance;
        if (getline(lineStream, src, ',') && getline(lineStream, dest, ',') && getline(lineStream, distance)) {
            if (distance.back() == '\r') distance.pop_back(); // Remove last character (which is a '\r' character)
            network.addBidirectionalEdge(stoi(src), stoi(dest), stod(distance));
        }
    }
}

void RoutingManager::readToyGraph(string fileName) {
    std::string line;
    std::ifstream edgesFile;

    edgesFile.open("../dataset/Toy-Graphs/" + fileName);

    if (!edgesFile.is_open()) {
        cout << "Error: Could not open file" << endl;
        return;
    }
    getline(edgesFile, line);

    while (getline(edgesFile, line)) {
        std::stringstream lineStream(line);
        string src, dest, distance;
        if (getline(lineStream, src, ',') && getline(lineStream, dest, ',') && getline(lineStream, distance)) {
            if (distance.back() == '\r') distance.pop_back(); // Remove last character (which is a '\r' character)
            // check first if the vertices exist, if not create them
            if (network.findVertex(stoi(src)) == nullptr) {
                auto *node = new Vertex(stoi(src));
                network.addVertex(node);
            }
            if (network.findVertex(stoi(dest)) == nullptr) {
                auto *node = new Vertex(stoi(dest));
                network.addVertex(node);
            }
            network.addBidirectionalEdge(stoi(src), stoi(dest), stod(distance));
        }
    }

}

//4.1
// Backtracking algorithm function to find the path
void RoutingManager::backtrackingAux(vector<vector<int>>& paths, unordered_map<int, Vertex*>& vertexSet, int currPos, int count, double cost, double &totalDist, vector<int>& path) {
    auto edges = vertexSet[currPos]->getAdj(); // Get the edges of the current vertex

    if (cost > totalDist) {
        return;
    }

    // Check if all the vertices have been visited
    if (count == vertexSet.size()) {
        Edge* e = vertexSet[currPos]->findEdge(0);
            if (e != nullptr) {
                double newWeight = cost + e->getWeight();
                if (newWeight < totalDist) {
                    totalDist = newWeight;
                    path = paths[currPos];
                    path.push_back(0);
                }
                return;
            }
        }

    // Explore adjacent vertices recursively
    for (auto p : edges) {
        auto e = p.second;
        int id = e->getDest()->getId();
        if (!vertexSet[id]->isVisited()) {
            vertexSet[id]->setVisited(true); // Mark the vertex as visited
            paths[id] = paths[currPos]; // Update the current path with the adjacent vertex
            paths[id].push_back(id);
            backtrackingAux(paths, vertexSet, id, count + 1, cost + e->getWeight(), totalDist, path); // Recursive call
            vertexSet[id]->setVisited(false);  // Mark the vertex as not visited after the recursive call
        }
    }
}

// Main function to execute the algorithm and print the results
void RoutingManager::backtracking() {
    unordered_map<int, Vertex*> vertexSet = network.getVertexSet(); // Get the vertex set
    vector<vector<int>> paths; // Vector to store the paths

    //  Mark all as not visited
    for (auto& i : vertexSet) {
        i.second->setVisited(false);
    }

    // Mark the first vertex as visited
    vertexSet[0]->setVisited(true);

    // Variables to track the path
    vector<int> path;
    double totalDist = numeric_limits<double>::infinity(); // Initialize totalDist to a large value
    paths.resize(vertexSet.size());
    paths[0].push_back(0);

    // Start time
    auto start = chrono::high_resolution_clock::now();
    // Execute the algorithm
    backtrackingAux(paths, vertexSet, 0, 1, 0.0, totalDist, path);
    // End time
    auto end = chrono::high_resolution_clock::now();

    // Calculate the execution time in seconds
    double duration = std::chrono::duration<double>(end - start).count();

    // Print the results
    cout << "\nPath: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if ((i + 1) % 10 == 0 && i != path.size() - 1) {
            cout << '\n';
        } else if (i != path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << path[0] << endl;
    cout << "\nTotal Distance: " << totalDist << std::endl;
    cout << "Execution Time: " << duration << " seconds" << endl;
}

//4.2
// Convert degrees to radians
double RoutingManager::degreesToRadians(double degree) {
    return degree * M_PI / 180.0;
}

// Calculate the Haversine distance between
double RoutingManager::haversineDistance(double latitude1, double longitude1, double latitude2, double longitude2) {
    const double earth_radius = 6371000.0;
    // Convert latitude and longitude to radians
    double rad_lat1 = degreesToRadians(latitude1);
    double rad_lon1 = degreesToRadians(longitude1);
    double rad_lat2 = degreesToRadians(latitude2);
    double rad_lon2 = degreesToRadians(longitude2);

    // Calculate differences in latitude and longitude
    double delta_lat = rad_lat2 - rad_lat1;
    double delta_lon = rad_lon2 - rad_lon1;

    // Haversine formula
    double a = sin(delta_lat / 2) * sin(delta_lat / 2) +
               cos(rad_lat1) * cos(rad_lat2) * sin(delta_lon / 2) * sin(delta_lon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = earth_radius * c;

    return distance;
}

double RoutingManager::calculateDistance(Vertex* v1, Vertex* v2) {
    Edge* edge = v1->findEdge(v2->getId());
    if (edge != nullptr) {
        return edge->getWeight();
    }
    // Calculate Haversine distance if no direct edge exists and add it to the graph
    auto dist =  haversineDistance(v1->getLatitude(), v1->getLongitude(), v2->getLatitude(), v2->getLongitude());
    network.addBidirectionalEdge(v1->getId(), v2->getId(), dist);
    return dist;
}

vector<vector<Edge>> RoutingManager::calculatePrims() {
    unordered_map<int, Vertex*> vertices = network.getVertexSet(); // Get the vertex set

    // Add all missing edges to the graph since it is not connected, using haversine distance
    // Get the vertex set from the network
    unordered_map<int, Vertex*> vertexSet = network.getVertexSet();

    // Initialize auxiliary data for Prims algorithm
    for (auto& v : vertices) {
        v.second->setMinDist(numeric_limits<double>::infinity());
        v.second->setPrev(nullptr);
        v.second->setVisited(false);
    }

    Vertex* startVertex = vertices[0];
    startVertex->setMinDist(0.0);

    // Initialize priority queue for vertices based on their minimum distances
    priority_queue<pair<double, Vertex*>, vector<pair<double, Vertex*>>, greater<pair<double, Vertex*>>> priorityQueue;
    priorityQueue.push({0.0, startVertex});
    int count = 0;
    // Process vertices in the priority queue
    while (!priorityQueue.empty()) {
        Vertex* currentVertex = priorityQueue.top().second;
        double dist = priorityQueue.top().first;
        priorityQueue.pop();
        if (currentVertex->isVisited()) {
            continue;
        }
        currentVertex->setVisited(true);

        // Add adjacent vertices to the priority queue
        // Need to iterate through all vertices because graph is connected
        cout << "Current Vertex count: " << count << endl;
        count++;
        for (auto& pair: vertices) {
            Vertex* adjVertex = pair.second;
            if (adjVertex == currentVertex) {
                continue;
            }
            double distToAdj = calculateDistance(currentVertex, adjVertex);

            if (!adjVertex->isVisited() && distToAdj < adjVertex->getMinDist()) {
                adjVertex->setMinDist(distToAdj);
                adjVertex->setPrev(currentVertex);
                priorityQueue.push({distToAdj, adjVertex});
            }
        }

    }

    // Too inefficient to just use original graph for preorder traversal, too many edges
    vector<vector<Edge>> mst (vertices.size());

    for (auto& v : vertices) {
        if (v.second->getPrev() != nullptr) {
            int v_id = v.second->getPrev()->getId();
            double weight = v.second->getMinDist();
            mst[v_id].emplace_back(v.second, weight);
            mst[v.second->getId()].emplace_back(v.second->getPrev(), weight);
        }
    }
    return mst;
}

void RoutingManager::dfsTour(const vector<vector<Edge>> &mst, int node, vector<bool> &visited, vector<int> &path) {
    visited[node] = true;
    path.push_back(node);

    vector<Edge> children = mst[node];

    for (const Edge &edge : children) {
        if (!visited[edge.getDest()->getId()]) {
            dfsTour(mst, edge.getDest()->getId(), visited, path);
        }
    }
}

void RoutingManager::TriangularApproximation() {
    auto start = chrono::high_resolution_clock::now();
    auto vertices = calculatePrims();

    int startVertexId = 0;
    vector<int> tour;
    vector<bool> visited(network.getNumVertex(), 0);

    dfsTour(vertices, startVertexId, visited, tour);

    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double>(end - start).count();

    // Print the results
    double totalDist = 0;
    for (int i = 0; i < tour.size(); i++){
        totalDist += calculateDistance(network.getVertexSet()[tour[i]], network.getVertexSet()[tour[(i + 1) % tour.size()]]);
    }

    int brk = 0;
    cout << "Path: ";
    for (int i = 0; i < tour.size(); i++) {

        cout << tour[i];
        if (brk == 10) {
            cout << '\n';
            brk = 0;
        }
        if (i != tour.size() -1) {
            cout << " -> ";
        }
        else cout << tour[0];
        brk++;
    }
    cout << "\nTotal Distance: " << fixed << std::setprecision(2) << totalDist << endl;
    cout << "\nExecution Time: " << duration << " seconds" << endl;
}

vector<vector<Edge>> RoutingManager::greedyModifiedPrimST() {
    unordered_map<int, Vertex*> vertexSet = network.getVertexSet();

    // Initialization (same as before)
    for (auto& v : vertexSet) {
        v.second->setMinDist(numeric_limits<double>::infinity());
        v.second->setPrev(nullptr);
        v.second->setVisited(false);
    }

    Vertex* startVertex = vertexSet[0];
    startVertex->setMinDist(0.0);

    vector<vector<Edge>> mst(vertexSet.size());
    int numVisited = 0;
    Vertex* currentVertex = startVertex;
    while (numVisited < vertexSet.size()) {
        currentVertex->setVisited(true);
        numVisited++;

        double minDist = numeric_limits<double>::infinity();
        Vertex* nextVertex = nullptr;
        for (const auto& edgePair : currentVertex->getAdj()) {
            Vertex* neighbor = edgePair.second->getDest();
            if (!neighbor->isVisited() && edgePair.second->getWeight() < minDist) {
                minDist = edgePair.second->getWeight();
                nextVertex = neighbor;
            }
        }

        // If a neighbor was found, add the edge to MST and update distances
        if (nextVertex != nullptr) {
            nextVertex->setMinDist(minDist);
            nextVertex->setPrev(currentVertex);
            mst[currentVertex->getId()].emplace_back(nextVertex, minDist);
            mst[nextVertex->getId()].emplace_back(currentVertex, minDist);
            currentVertex = nextVertex; // Move to the closest neighbor
        } else {
            // If no unvisited neighbors, find another unvisited vertex to start from
            for (const auto& v : vertexSet) {
                if (!v.second->isVisited()) {
                    currentVertex = v.second;
                    break;
                }
            }
        }
    }

    return mst;
}

void RoutingManager::Faster2ApproximationTSP() {
    auto start = chrono::high_resolution_clock::now();

    unordered_map<int, Vertex*> vertexSet = network.getVertexSet();

    // 1. Modified Prim's Algorithm (Faster, but potentially less optimal MST)
    vector<vector<Edge>> mst = greedyModifiedPrimST(); // Implementation below

    // 2. Depth-First Search for Preorder Traversal (Same as before)
    int startVertexId = 0; // Assuming node 0 is the starting point
    vector<int> tour;
    vector<bool> visited(network.getNumVertex(), false);
    dfsTour(mst, startVertexId, visited, tour);


    auto end = chrono::high_resolution_clock::now();
    double duration = chrono::duration<double>(end - start).count();

    // Print the results
    double totalDist = 0;
    for (int i = 0; i < tour.size(); i++){
        totalDist += calculateDistance(network.getVertexSet()[tour[i]], network.getVertexSet()[tour[(i + 1) % tour.size()]]);
    }

    int brk = 0;
    for (int i = 0; i < tour.size(); i++) {
        cout << tour[i];
        if (brk == 10) {
            cout << '\n';
            brk = 0;
        }
        if (i != tour.size()) {
            cout << " -> ";
        }
        brk++;
    }
    cout << tour[0];
    cout << "\nTotal Distance: " << fixed << std::setprecision(2) << totalDist << endl;
    cout << "Execution Time: " << duration << " seconds" << endl;
}