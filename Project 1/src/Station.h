#ifndef PROJECT_1_ATWSM_STATION_H
#define PROJECT_1_ATWSM_STATION_H

#include "Node.h"
using namespace std;

/*!
 * @briefClass representing a station in a transportation network.
 */
class Station final : public Node {
public:
    //Constructor
    /*!
     * @brief Constructor for Station class.
     * @param id
     * @param code 
     */
    Station(int id, string code) : Node(id, code){
    }

};

#endif //PROJECT_1_ATWSM_STATION_H
