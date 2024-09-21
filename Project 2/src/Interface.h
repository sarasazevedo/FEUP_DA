#ifndef PROJECT2_RAOSUD_INTERFACE_H
#define PROJECT2_RAOSUD_INTERFACE_H

#include "RoutingManager.h"
#include "Graph.h"
#include "Edge.h"

/*!
 * @class Interface
 * @brief Handles the user interface and interactions for the routing application.
 */
class Interface {
public:
    /*!
     * @brief Displays the menu for selecting the dataset.
     * @return The user's choice from the dataset menu.
     */
    static int displayDataSetMenu();
    /*!
     * @brief Displays the menu for selecting the statement of work.
     * @return The user's choice from the graph type menu.
     */
    static int displayStatementOfWork();
    /*!
    * @brief Displays and handles the menu for selecting toy graphs.
     */
    /*static*/ void menuToyGraphs();
    /*!
     * @brief Displays and handles the menu for selecting real world graphs.
     */
    /*static*/ void menuRealWorldGraphs();
    /*!
     * @brief Displays and handles the menu for selecting extra fully connected graphs.
     */
    /*static*/ void menuExtraFullyConnectedGraphs();
    /*!
     * @brief Runs the main interface loop.
     */
    /*static*/ void run();
private:
    /*!
     * Manages the routing and graph operations.
     */
    RoutingManager manager;

};
#endif
