#ifndef PROJECT2_RAOSUD_GRAPH_H
#define PROJECT2_RAOSUD_GRAPH_H

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include "Edge.h"
#include "Vertex.h"

/*!
 * @class Graph
 * @brief Represents a graph consisting of vertices and edges.
 */
class Graph {
public:
    /*!
     * @brief Destructor for the Graph class.
     */
    ~Graph();
    /*!
     * @brief Finds a vertex in the graph.
     * @param id The id of the vertex to find.
     * @return A pointer to the vertex if found, nullptr otherwise.
     */
    Vertex *findVertex(const int &id) const;
    /*!
     * @brief Adds a vertex to the graph.
     * @param node The vertex to add.
     * @return True if the vertex was added, false otherwise.
     */
    bool addVertex(Vertex *node);
    /*!
     * @brief Adds a bidirectional edge between two vertices in the graph.
     * @param source The source vertex id.
     * @param dest The destination vertex id.
     * @param w The weight of the edge.
     * @return True if the edge was added, false otherwise.
     */
    bool addBidirectionalEdge(const int &source, const int &dest, double w);
    /*!
     * @brief Gets the number of vertices in the graph.
     * @return The number of vertices in the graph.
     */
    int getNumVertex() const;
    /*!
     * @brief Gets the set of vertices in the graph.
     * @return An unordered map of vertices in the graph.
     */
    unordered_map<int, Vertex *> getVertexSet() const;
    /*!
    * @brief Sets the set of vertices in the graph.
     * @param set An unordered map of vertices to set in the graph.
     */
    void setVertexSet(const unordered_map<int, Vertex *> &set);
protected:
    /*!
     * @brief The set of vertices in the graph.
     */
    unordered_map<int, Vertex *> vertexSet;
};

#endif
