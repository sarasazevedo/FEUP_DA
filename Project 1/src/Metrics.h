#pragma once


#include <cmath>
#include <vector>
#include <limits>

#include "Network.h"

/*!
 * @brief Struct that represents the metrics calculated from the network.
 */
struct Metrics {
    double average; /*!< The average difference between capacity and flow of pipes in the network. */
    double variance; /*!< The variance of the difference between capacity and flow of pipes in the network. */
    double maxDifference; /*!< The maximum difference between capacity and flow of pipes in the network. */
    /*!
     * @brief Function to calculate the metrics of the network.
     * @param network
     */
    void calculateMetrics(Network &network) {
        std::vector<Pipe *> pipes = network.getPipes();
        int n = pipes.size();
        double sum = 0.0;
        double sumSq = 0.0;
        maxDifference = -std::numeric_limits<double>::max();

        for (Pipe *pipe: pipes) {
            double difference = pipe->getCapacity() - pipe->getFlow();
            sum += difference;
            sumSq += difference * difference;
            maxDifference = std::max(maxDifference, difference);
        }

        average = sum / n;
        variance = (sumSq / n) - (average * average);
    }
};
