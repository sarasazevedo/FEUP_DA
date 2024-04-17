#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <unordered_map>

#include "Pipe.h"
#include "Node.h"

using namespace std;
/*!
 * @brief Class that represents the network of pipes, nodes and cities.
 */
class Network {
public:
    /*!
     *@brief Finds a vertex (node) in the network by its code.
     * @param code
     * @return A pointer to the found node, or nullptr if not found.
     */
    Node *findVertex(const string &code) const;
    /*!
     * @brief Adds a vertex (node) to the network.
     * @param node
     * @return True if the node was added successfully, false otherwise.
     */
    bool addVertex(Node *node);
    /*!
     * @brief Removes a vertex (node) from the network by its code.
     * @param code
     * @return True if the node was removed successfully, false otherwise.
     */
    bool removeVertex(const std::string &code);
    /*!
     * @brief Adds an edge (pipe) between two nodes in the network.
     * @param src
     * @param dest
     * @param capacity
     * @return True if the edge was added successfully, false otherwise.
     */
    bool addEdge(const string &src, const string &dest, double capacity);
    /*!
     * @brief Removes an edge (pipe) between two nodes in the network.
     * @param source
     * @param dest
     * @return True if the edge was removed successfully, false otherwise.
     */
    bool removeEdge(const string &source, const string &dest);
    /*!
     * @brief Gets the number of vertices (nodes) in the network.
     * @return The number of vertices in the network.
     */
    int getNumVertex() const;
    /*!
     * @brief Gets the set of nodes in the network.
     * @return The set of nodes in the network.
     */
    unordered_map<string, Node *> getNodeSet() const;
    /*!
     * @brief Gets the set of pipes in the network.
     * @return The set of pipes in the network.
     */
    vector<Pipe *> getPipes() const;

private:
    unordered_map<string, Node *> nodeSet; /*!< Set of nodes in the network */
    vector<Pipe *> pipeSet_; /*!< Set of pipes in the network */
};


#endif //NETWORK_H
