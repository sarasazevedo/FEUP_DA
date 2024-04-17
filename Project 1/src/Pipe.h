#ifndef PROJECT_1_ATWSM_PIPES_H
#define PROJECT_1_ATWSM_PIPES_H

#include <iostream>
#include "Node.h"

using namespace std;

class Node;
/*!
 * @brief Class representing a pipe connecting two nodes.
 */
class Pipe {
    friend class Node;

private:
    Node *src; /*!< Pointer to the source node of the pipe. */
    Node *dest; /*!< Pointer to the destination node of the pipe. */
    int capacity_; /*!< The capacity of the pipe. */
    int flow_{0}; /*!< The flow of the pipe. */

public:
    /*!
     * @brief Constructor for Pipe class.
     * @param src Pointer to the source node of the pipe.
     * @param dest Pointer to the destination node of the pipe.
     * @param capacity The capacity of the pipe.
     */
    Pipe(Node *src, Node *dest, int capacity);
    /*!
     * @brief Get the source node of the pipe.
     * @return Pointer to the source node.
     */
    Node *getSrc() const;
    /*!
     * @brief Get the destination node of the pipe.
     * @return Pointer to the destination node.
     */
    Node *getDest() const;
    /*!
     * @brief Get the capacity of the pipe.
     * @return The capacity of the pipe.
     */
    int getCapacity() const;
    /*!
     * @brief Get the flow of the pipe.
     * @return The current flow of the pipe.
     */
    int getFlow() const;

    /* Setters */
    /*!
     * @brief Set the source node of the pipe.
     * @param newNode
     */
    void setSrc(Node *newNode);
    /*!
     * @brief Set the destination node of the pipe.
     * @param newNode
     */
    void setDest(Node *newNode);
    /*!
     * @brief Set the capacity of the pipe.
     * @param newCapacity
     */
    void setCapacity(int newCapacity);
    /*!
     * @brief Set the flow through the pipe.
     * @param newFlow
     */
    void setFlow(int newFlow);
};

#endif //PROJECT_1_ATWSM_PIPES_H
