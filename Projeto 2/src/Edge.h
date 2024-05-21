#ifndef PROJECT2_RAOSUD_EDGE_H
#define PROJECT2_RAOSUD_EDGE_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "Vertex.h"
using namespace std;

class Vertex;

/*!
 * Edge class
 */
class Edge {
    /*!
     * Allows the Vertex class to access private members of Edge.
     */
    friend class Vertex;
public:
    /*!
     * Constructs a new Edge object.
     * @param dest
     * @param w
     */
    Edge(Vertex *dest, double w);
    /*!
     * Gets the destination vertex.
     * @return
     */
    Vertex * getDest() const;
    /*!
     * Gets the weight of the edge.
     * @return
     */
    double getWeight() const;
    /*!
     * Sets the destination vertex.
     * @param dest
     */
    void setDest(Vertex *dest);
    /*!
     * Sets the weight of the edge.
     * @param weight
     */
    void setWeight(double weight);
protected:
    /*!
     * The destination vertex.
     */
    Vertex *dest;
    /*!
     * The weight of the edge.
     */
    double weight;
};

#endif
