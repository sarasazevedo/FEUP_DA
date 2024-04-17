#ifndef PROJECT_1_ATWSM_CITY_H
#define PROJECT_1_ATWSM_CITY_H

#include "Node.h"
using namespace std;

class City final : public Node {
public:
    /*!
     * @brief Constructor for City class.
     * @param city
     * @param id
     * @param code
     * @param demand
     * @param population
     */
    City(const string &city, const int id, const string &code, const int demand, const int population): Node(id, code),
        city_(city),
        demand_(demand),
        population_(population) {
    }
    /*!
     * @brief Get the name of the city.
     * @return city_
     */
    string getCity() const { return city_; }
    /*!
     * @brief Get the demand of the city.
     * @return demand_
     */
    int getDemand() const { return demand_; }
    /*!
     * @brief Get the population of the city.
     * @return population_
     */
    int getPopulation() const { return population_; }
    /*!
     * @brief Set the name of the city.
     * @param newCity
     */
    void setCity(const string &newCity) { city_ = newCity; }
    /*!
     * @brief Set the demand of the city.
     * @param newDemand
     */
    void setDemand(const int newDemand) { demand_ = newDemand; }
    /*!
     * @brief Set the population of the city.
     * @param newPopulation
     */
    void setPopulation(const int newPopulation) { population_ = newPopulation; }

private:
    string city_; /*!< Name of the city */
    int demand_; /*!< Demand of the city */
    int population_; /*!< Population of the city */
};

#endif //PROJECT_1_ATWSM_CITY_H
