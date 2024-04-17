#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using namespace std;

class Pipe;
/*!
 * @file Node.h
 * @brief Contains the declaration of the Node class.
 */
 /*!
  * @brief Class that represents a node in a graph.
  */
class Node {
    friend class Pipe;

protected:
    int id_; /*!< The unique identifier of the node. */
    string code_; /*!< The code of the node. */
    bool visited_{false}; /*!< Flag to indicate if the node has been visited. */
    bool processing_{false}; /*!< Flag to indicate if the node is being processed. */
    int indegree_{0}; /*!< The indegree of the node. */
    int num_{0}; /*!< The number of the node. */
    int low_{0}; /*!< The low value of the node. */
    vector<Pipe *> _adj; /*!< The outgoing pipes of the node. */
    vector<Pipe *> _incoming; /*!< The incoming pipes of the node. */
    Pipe *path{nullptr}; /*!< The path of the node. */

public:
    /*!
     * @brief Constructor for Node class.
     * @param id The unique identifier of the node.
     * @param cod The code of the node.
     */
    Node(int id, string cod);

    /*! @brief Destructor for Node class. */
    virtual ~Node();

    // Getters
    /*!
     * @brief Get the ID of the node.
     * @return The ID of the node.
     */
    int getID() const;
    /*!
     * @brief Get the code of the node.
     * @return The code of the node.
     */
    string getCode() const;
    /*!
     * @brief Check if the node has been visited.
     * @return True if the node has been visited, false otherwise.
     */
    bool isVisited() const;
    /*!
     * @brief Check if the node is being processed.
     * @return True if the node is being processed, false otherwise.
     */
    bool isProcessing() const;
    /*!
     * @brief Get the indegree of the node.
     * @return The indegree of the node.
     */
    int getIndegree() const;
    /*!
     * @brief Get the number of the node.
     * @return The number of the node.
     */
    int getNum() const;
    /*!
     * @brief Get the low value of the node.
     * @return The low value of the node.
     */
    int getLow() const;

    /*!
     * @brief Get the outgoing pipes of the node.
     * @return A constant reference to the vector of outgoing pipes.
     */
    [[nodiscard]] const vector<Pipe *> &getAdj() const;
    /*!
     * @brief Get the incoming pipes of the node.
     * @return A constant reference to the vector of incoming pipes.
     */
    [[nodiscard]] const vector<Pipe *> &getIncoming() const;
    /*!
     * @brief Get the path of the node.
     * @return A pointer to the path of the node.
     */
    [[nodiscard]] Pipe *getPath() const;


    //setters
    /*!
     * @brief Set the ID of the node.
     * @param newID
     */
    void setID(int newID);
    /*!
     * @brief Set the code of the node.
     * @param newCod
     */
    void setCod(string newCod);
    /*!
     * @brief Set the visited flag of the node.
     * @param visited
     */
    void setVisited(bool visited);
    /*!
     * @brief Set the processing flag of the node.
     * @param processing
     */
    void setIsProcessing(bool processing);
    /*!
     * @brief Set the indegree of the node.
     * @param newIndegree
     */
    void setIndegree(int newIndegree);
    /*!
     * @brief Set the number of the node.
     * @param num
     */
    void setNum(int num);
    /*!
     * @brief Set the low value of the node.
     * @param low
     */
    void setLow(int low);
    /*!
     * @brief Set the outgoing pipes of the node.
     * @param adj
     */
    void setAdj(const vector<Pipe *> &adj);

    /*!
         * @brief Check if two nodes are equal.
         * @param rhs The node to compare.
         * @return True if the nodes are equal, false otherwise.
         */
    bool operator==(const Node &rhs) const;

    /*!o
        * @brief Check if two nodes are not equal.
        * @param rhs The node to compare.
        * @return True if the nodes are not equal, false otherwise.
        */
    bool operator!=(const Node &rhs) const;

    /*!
     * @brief Add a pipe to the outgoing pipes of the node.
     * @param pipe
     */
    void addPipe(Pipe *pipe);
    /*!
     * @brief Set the path associated with the node.
     * @param pipe
     */
    void setPath(Pipe *newPath);
    /*!
     @brief Remove all outgoing pipes from the node.
     */
    void removeOutgoingPipes();
    /*!
     @brief Delete a specific edge (pipe) from the outgoing pipes of the node.
     @param pipe
     */
    void deleteEdge(Pipe * pipe);
    /*!
     * @brief Remove a pipe from the outgoing pipes of the node.
     * @param pipe
     * @return True if the pipe was removed successfully, false otherwise.
     */
    bool removeEdge(const string &in);
};


#endif
