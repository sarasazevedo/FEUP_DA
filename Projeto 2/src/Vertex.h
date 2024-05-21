#ifndef PROJECT2_RAOSUD_VERTEX_H
#define PROJECT2_RAOSUD_VERTEX_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <unordered_map>
#include "Edge.h"
using namespace std;

class Edge;

/*!
 * @class Vertex
 * @brief Represents a vertex in a graph.
 */
class Vertex {
    friend class Edge;

public:
    /*!
     * @brief Constructs a Vertex with a given identifier.
     * @param id The identifier of the vertex.
     */
    explicit Vertex(int id);

    /*!
     * @brief Constructs a Vertex with a given identifier, latitude, and longitude.
     * @param id The identifier of the vertex.
     * @param lat The latitude of the vertex.
     * @param lon The longitude of the vertex.
     */
    Vertex(int id, double lat, double lon);

    /*!
     * @brief Gets the identifier of the vertex.
     * @return The identifier of the vertex.
     */
    int getId() const;

    /*!
     * @brief Gets the adjacency list of the vertex.
     * @return A vector of edges representing the adjacency list.
     */
    std::unordered_map<int, Edge *> getAdj() const;

    /*!
     * @brief Checks if the vertex has been visited.
     * @return True if the vertex has been visited, false otherwise.
     */
    bool isVisited() const;

    /*!
     * @brief Checks if the vertex is currently being processed.
     * @return True if the vertex is being processed, false otherwise.
     */
    bool isProcessing() const;

    /*!
     * @brief Gets the minimum distance to this vertex.
     * @return The minimum distance to this vertex.
     */
    double getMinDist() const;

    /*!
     * @brief Sets the minimum distance to this vertex.
     * @param minDist The minimum distance to set.
     */
    void setMinDist(double minDist);

    /*!
     * @brief Gets the previous vertex in the shortest path.
     * @return The previous vertex in the shortest path.
     */
    Vertex* getPrev() const;

    /*!
     * @brief Sets the previous vertex in the shortest path.
     * @param prev The previous vertex to set.
     */
    void setPrev(Vertex* prev);

    /*!
     * @brief Gets the distance to this vertex.
     * @return The distance to this vertex.
     */
    double getDist() const;

    /*!
     * @brief Gets the edge leading to this vertex in the shortest path.
     * @return The edge leading to this vertex.
     */
    Edge *getPath() const;

    /*!
     * @brief Gets the incoming edges to this vertex.
     * @return A vector of incoming edges.
     */
    vector<Edge *> getIncoming() const;

    /*!
     * @brief Gets the latitude of the vertex.
     * @return The latitude of the vertex.
     */
    double getLatitude() const;

    /*!
     * @brief Gets the longitude of the vertex.
     * @return The longitude of the vertex.
     */
    double getLongitude() const;

    /*!
     * @brief Sets the identifier of the vertex.
     * @param info The identifier to set.
     */
    void setId(int info);

    /*!
     * @brief Sets the visited status of the vertex.
     * @param visited The visited status to set.
     */
    void setVisited(bool visited);

    /*!
     * @brief Sets the processing status of the vertex.
     * @param processing The processing status to set.
     */
    void setProcesssing(bool processing);

    /**
     * @brief Sets the distance to this vertex.
     * @param dist The distance to set.
     */
    void setDist(double dist);

    /*!
     * @brief Sets the edge leading to this vertex in the shortest path.
     * @param path The edge to set.
     */
    void setPath(Edge *path);

    /*!
     * @brief Sets the latitude of the vertex.
     * @param latitude The latitude to set.
     */
    void setLatitude(double latitude);

    /*!
     * @brief Sets the longitude of the vertex.
     * @param longitude The longitude to set.
     */
    void setLongitude(double longitude);

    /*!
     * @brief Adds an edge from this vertex to a destination vertex with a given weight.
     * @param dest The destination vertex.
     * @param w The weight of the edge.
     * @return The created edge.
     */
    Edge * addEdge(Vertex *dest, double w);

    /*!
     * @brief Finds the edge with the given destination vertex ID.
     * @param i The ID of the destination vertex.
     * @return A pointer to the edge if found, nullptr otherwise.
     */

    Edge *findEdge(int i);

protected:
    /*!
     * @brief The identifier of the vertex.
     */
    int id;
    /*!
     * @brief The latitude of the vertex.
     */
    double latitude;
    /*!
     * @brief The longitude of the vertex.
     */
    double longitude;
    /*!
     * @brief The adjacency list of edges.
     */
    std::unordered_map<int, Edge *> adj;
    /*!
     * @brief The visited status of the vertex.
     */
    bool visited = false;
    /*!
     * @brief The minimum distance to this vertex.
     */
    double minDist;
    /*!
     * @brief The previous vertex in the shortest path.
     */
    Vertex* prev;
    /*!
     * @brief The processing status of the vertex.
     */
    bool processing = false;
    /*!
     * @brief The distance to this vertex.
     */
    double dist = 0;
    /*!
     * @brief The edge leading to this vertex in the shortest path.
     */
    Edge *path = nullptr;
};

#endif
