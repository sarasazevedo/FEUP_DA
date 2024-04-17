#include <stdexcept>
#include <algorithm>
#include "Network.h"
#include "Pipe.h"
#include "Node.h"
#include <queue>
#include <limits>

using namespace std;

/*!
 * @brief Class that represents the Edmonds-Karp algorithm to find the maximum flow in a network
 */
class Edmonskarp {
public:
    /*!
 * @brief Function used in Edmonds-Karp algorithm to test if a node is visited
 * @param q
 * @param pipe
 * @param dest
 * @param residual
 * @complexity O(1)
 */
    static void testAndVisit(queue<Node *> &q, Pipe *pipe, Node *dest, double residual);
/*!
 * @brief Function used in Edmonds-Karp algorithm to find an augmenting path implementing BFS
 * @param network
 * @param s
 * @param t
 * @param improvedBalance
 * @return true if there is an augmenting path and false otherwise
 * @complexity O(VE)
 */
    static bool findAugmentingPath(Network &network, Node *s, Node *t, bool improvedBalance);
/*!
 * @brief Function used in Edmonds-Karp algorithm to find the minimum residual between the source and the target
 * @param s
 * @param t
 * @return the minimum residual between the source and the target
 * @complexity O(V)
 */
    static double findMinResidualAlongPath(Node *s, Node *t);
/*!
 * @brief Function used in Edmonds-Karp algorithm to augment the flow along the path
 * @param s
 * @param t
 * @param f
 * @complexity O(V)
 */
    static void augmentFlowAlongPath(Node *s, Node *t, double f);
/*!
 * @brief Implements the Edmonds-Karp algorithm to find the maximum flow
 * @param network
 * @param sourceCode
 * @param targetCode
 * @complexity O(VE^2)
 * @param improvedBalance
 */
    static void edmondsKarp(Network &network, const std::string &sourceCode, const std::string &targetCode, bool improvedBalance) ;

    };


