#ifndef PROJECT_1_ATWSM_INTERFACE_H
#define PROJECT_1_ATWSM_INTERFACE_H


#include "WaterSupplyManager.h"

/*!
 * @brief Class that represents the interface to interact with the user.
 */
class Interface {
public:
    /*!
     * @brief Displays the data set menu to the user.
     * @return The selected option from the menu.
     */
    static int displayDataSetMenu();
    /*!
     * @brief Displays the main menu to the user.
     * @return The selected option from the menu.
     */
    static int displayMainMenu();
    /*!
     * @brief Displays the basic metrics menu to the user.
     * @return The selected option from the menu.
     */
    static int displayBasicMetricsMenu();
    /*!
     * @brief Executes the basic metrics menu.
     */
    /*static*/ void basicMetricsMenu();
    /*!
     * @brief Displays the line failure menu to the user.
     * @return The selected option from the menu.
     */
    static int displayLineFailureMenu();
    /*!
     * @brief Executes the line failure menu.
     */
    /*static*/ void lineFailureMenu();

    /*!
     * @brief Executes the interface.
     */
    /*static*/ void run();
    /*!
     * @brief Displays the option flow.
     */
    void DisplayOptionFlow();
    /*!
     * @brief Displays the option to display the flow of a specific city.
     */
    void displayFlowSpecificCity();
    /*!
     * @brief Displays the option to display the flow of all cities.
     */
    void displayFlowAllCities();

private:
    /*static*/ WaterSupplyManager _waterSupplyManager; /*!< Water supply manager instance used by the interface */
};

#endif //PROJECT_1_ATWSM_INTERFACE_H
