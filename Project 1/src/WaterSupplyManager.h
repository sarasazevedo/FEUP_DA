#ifndef PROJECT_1_ATWSM_WATERSUPPLYMANAGER_H
#define PROJECT_1_ATWSM_WATERSUPPLYMANAGER_H


#include <string>

#include "Edmonskarp.h"
#include "Network.h"

/*!
 * @file WaterSupplyManager.h
 * @brief Class responsible for managing water supply operations.
 *
 * This class handles various operations related to water supply management, including reading data files,
 * performing flow calculations, optimizing flow capacities, and assessing network capabilities.
 */
class WaterSupplyManager {
    /*static*/
    Network _waterNetwork; /*!< The water network managed by the WaterSupplyManager. */
    Edmonskarp _edmondsKarp; /*!< The Edmonds-Karp algorithm used for flow calculations. */

public:
    /*!
    * @brief Function responsible for reading the data files
    * Complexity: O(n), n is the number of lines
    */
    void readCSV(bool isLarge);
    /*!
    * @brief Runs the Edmonds-Karp algorithm to find maximum flow.
    * This function calculates the maximum flow in the water network using the Edmonds-Karp algorithm.
    * @param copyNetwork
    * @param improvedBalance
    * @complexity O(VE^2), where V is the number of vertices and E is the number of edges in the network.
    */
    void runEdmondsKarp(Network copyNetwork, bool improvedBalance);
    /*!
    * @brief Calculates the maximum flow from a source city to a destination city.
    * This function calculates the maximum flow from a specified source city to a destination city
    * using the Edmonds-Karp algorithm.
    * @param destCity
    * @complexity O(VE^2), where V is the number of vertices and E is the number of edges in the network.
    */
    void maxFlow(const std::string &destCity);
    /*!
    * @brief Checks if the network can meet water needs.
    * This function assesses whether the water network can meet the water needs of all cities.
    */
    void canNetworkMeetWaterNeeds();
    /*!
    * @brief Minimizes differences in flow capacity within the water network.
    * This function minimizes differences in flow capacity within the water network to optimize water distribution.
    */
    void minimizeDifferencesFlowCapacity();
    /*!
    * @brief Determines cities affected by the removal of a node.
    * This function determines the cities affected by the removal of a specified node (city) from the network.
    * @param src
    */
    void citiesAffectedByNodeRemoval(const std::string &src);
    /*!
    * @brief Determines cities affected by the removal of a pipe.
    * This function determines the cities affected by the removal of a specified pipe (edge) from the network.
    * @param src
    * @param dest
    */
    void citiesAffectedByPipeRemoval(const string & src, const string & dest);
};


#endif //PROJECT_1_ATWSM_WATERSUPPLYMANAGER_H
