#ifndef PROJECT2_RAOSUD_ROUTINGMANAGER_H
#define PROJECT2_RAOSUD_ROUTINGMANAGER_H

#include <string>
#include <vector>
#include "Graph.h"

/*!
 * RoutingManager class
 */
class RoutingManager {
public:
    /*!
     * Constructor
     */
    RoutingManager();

    /*!
     * Read extra fully connected graph
     * @param nodeNumber The number of nodes in the graph.
     * Time Complexity: O(n^2), where n is the number of nodes.
     */
    void readExtraFullyConnectedGraph(unsigned int nodeNumber);

    /*!
     * Read real world graph
     * @param folderName The name of the folder containing graph files.
     * Time Complexity: O(n + m), where n is the number of vertices and m is the number of edges in the graph.
     */
    void readRealWorldGraph(string folderName);

    /*!
     * Read toy graph
     * @param fileName The name of the file containing the toy graph.
     * Time Complexity: O(m), where m is the number of edges in the graph.
     */
    void readToyGraph(string fileName);

    /*!
     * Recursive auxiliary function for the backtracking algorithm.
     * This function is called recursively to explore all possible paths
     * in the graph using backtracking. It finds the shortest path starting
     * from the current position (vertex) and updates the total distance and
     * the corresponding path accordingly.
     * @param paths Vector of vectors storing the paths explored.
     * @param vertexSet The set of vertices in the graph.
     * @param currPos The current position (vertex) in the traversal.
     * @param count The number of vertices visited so far.
     * @param cost The accumulated cost (distance) of the current path.
     * @param totalDist The total distance of the shortest path found.
     * @param path Vector representing the current path being explored.
     * Time Complexity: O(n!), where n is the number of vertices.
     */
    void backtrackingAux(vector<vector<int>> &paths, unordered_map<int, Vertex *> &vertexSet, int currPos, int count,
                         double cost, double &totalDist, vector<int> &path);

    /*!
     * Executes the backtracking TSP algorithm.
     * Time Complexity: O(n!), where n is the number of vertices.
     */
    void backtracking();

    /*!
     * Converts degrees to radians.
     * @param degree The angle in degrees.
     * @return The angle converted to radians.
     * Time Complexity: O(1).
     */
    double degreesToRadians(double degree);

    /*!
     * Calculates the Haversine distance between two points on Earth.
     * This function computes the great-circle distance between two points
     * on the Earth's surface using the Haversine formula.
     * @param latitude1 Latitude of the first point in degrees.
     * @param longitude1 Longitude of the first point in degrees.
     * @param latitude2 Latitude of the second point in degrees.
     * @param longitude2 Longitude of the second point in degrees.
     * @return The distance between the two points in kilometers.
     * Time Complexity: O(1).
     */
    double haversineDistance(double latitude1, double longitude1, double latitude2, double longitude2);

    /*!
     * Calculate the distance between two vertices in the graph.
     * This function calculates the distance between two vertices in the graph.
     * If there exists a direct edge between the two vertices, the weight of
     * that edge is returned. Otherwise, the Haversine distance between the
     * geographical coordinates of the vertices is calculated.
     * @param v1 Pointer to the first vertex.
     * @param v2 Pointer to the second vertex.
     * @return The distance between the two vertices.
     * Time Complexity: O(1) if direct edge exists, otherwise O(1) for Haversine calculation.
     */
    double calculateDistance(Vertex *v1, Vertex *v2);

    /*!
     * Perform triangular approximation algorithm to find minimum spanning tree.
     * This function applies the triangular approximation algorithm to find a minimum
     * spanning tree (MST) in the graph. It uses Prims algorithm with a priority queue
     * to efficiently select edges that form the MST. If the weight of an edge is not
     * explicitly given, the function calculates the distance between vertices using the
     * Haversine formula. The total distance of the MST and the execution time are printed
     * as output.
     * Time Complexity: O(E log V), where E is the number of edges and V is the number of vertices.
     */
    void TriangularApproximation();

    /*!
     * Calculates the Minimum Spanning Tree (MST) of the network using Prim's algorithm.
     * This function initializes all vertices, sets the starting vertex, and processes vertices
     * using a priority queue based on their minimum distances. It adds the shortest edges to
     * the MST until all vertices are visited.
     * @return A vector of vectors of Edges representing the MST of the network.
     * Time Complexity: O(E log V), where E is the number of edges and V is the number of vertices.
     */
    vector<vector<Edge>> calculatePrims();

    /*!
     * Performs a Depth-First Search (DFS) to generate a tour from the MST.
     * This function recursively visits all vertices starting from a given node and records the path
     * in the order they are visited. The path represents a preorder traversal of the MST.
     * @param mst The Minimum Spanning Tree represented as a vector of vectors of Edges.
     * @param node The starting node for the DFS.
     * @param visited A vector indicating whether each vertex has been visited.
     * @param path The path of nodes visited during the DFS.
     * Time Complexity: O(V + E), where V is the number of vertices and E is the number of edges.
     */
    void dfsTour(const vector<vector<Edge>> &mst, int node, vector<bool> &visited, vector<int> &path);

    /*!
     * Calculates a 2-approximation of the Traveling Salesman Problem (TSP) tour using a faster method.
     * This function first computes the MST using a modified Prim's algorithm, then performs a DFS to get a
     * preorder traversal of the MST, which serves as the TSP tour. It then calculates and prints the total
     * distance and execution time.
     * Time Complexity: O(E log V + V), where E is the number of edges and V is the number of vertices.
     */
    void Faster2ApproximationTSP();

private:
    /*!
     * The graph representing the network.
     */
    Graph network;
    /*!
     * Calculates the MST using a greedy modified version of Prim's algorithm.
     * This function initializes all vertices and processes them in a greedy manner, always moving to the
     * closest unvisited neighbor until all vertices are visited. It aims to improve execution speed at
     * the potential cost of optimality.
     * @return A vector of vectors of Edges representing the MST of the network.
     * Time Complexity: O(V^2), where V is the number of vertices.
     */
    vector<vector<Edge>> greedyModifiedPrimST();

};

#endif