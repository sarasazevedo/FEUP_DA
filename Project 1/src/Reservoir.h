#ifndef PROJECT_1_ATWSM_RESERVOIR_H
#define PROJECT_1_ATWSM_RESERVOIR_H


using namespace std;

/*!
 * @brief Class representing a reservoir within the network.
 */
class Reservoir final : public Node {
public:
    /*!
     * @brief Constructor for the Reservoir class.
     * @param reservoir
     * @param municipality
     * @param id
     * @param code
     * @param maxDelivery
     */
    Reservoir(const string &reservoir, const string &municipality, const int id, const string &code,
              const int maxDelivery) : Node(id, code),
                                       reservoir_(reservoir),
                                       municipality_(municipality),
                                       maxDelivery_(maxDelivery) {
    }

    /*!
     *brief Get the name of the reservoir.
     * @return The name of the reservoir.
     */
    string getReservoir() const { return reservoir_; }
    /*!
     * @brief Get the name of the municipality.
     * @return The name of the municipality.
     */
    string getMunicipality() const { return municipality_; }
    /*!
     * @brief Get the maximum delivery of the reservoir.
     * @return The maximum delivery of the reservoir.
     */
    int getMaxDelivery() const { return maxDelivery_; }
    /*!
     * @brief Set the name of the reservoir.
     * @param newReservoir
     */
    void setReservoir(const string &newReservoir) { reservoir_ = newReservoir; }
    /*!
     * @brief Set the name of the municipality.
     * @param newMunicipality
     */
    void setMunicipality(const string &newMunicipality) { municipality_ = newMunicipality; }
    /*!
     * @brief Set the maximum delivery of the reservoir.
     * @param newMaxDelivery
     */
    void setMaxDelivery(const int newMaxDelivery) { maxDelivery_ = newMaxDelivery; }

private:
    string reservoir_; /*!< Name of the reservoir. */
    string municipality_; /*!< Name of the municipality. */
    int maxDelivery_; /*!< Maximum delivery of the reservoir. */
};

#endif //PROJECT_1_ATWSM_RESERVOIR_H
