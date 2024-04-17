#include "WaterSupplyManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_set>

#include "City.h"
#include "Metrics.h"
#include "Reservoir.h"
#include "Station.h"


void WaterSupplyManager::readCSV(bool isLarge) {
    std::string line;
    std::ifstream citiesFile;
    std::ifstream stationsFile;
    std::ifstream pipesFile;
    std::ifstream reservoirsFile;

    if (isLarge) {
        citiesFile.open("../dataset/Project1LargeDataSet/Cities.csv");
        stationsFile.open("../dataset/Project1LargeDataSet/Stations.csv");
        pipesFile.open("../dataset/Project1LargeDataSet/Pipes.csv");
        reservoirsFile.open("../dataset/Project1LargeDataSet/Reservoir.csv");
    }
    else {
        citiesFile.open("../dataset/Project1DataSetSmall/Cities_Madeira.csv");
        stationsFile.open("../dataset/Project1DataSetSmall/Stations_Madeira.csv");
        pipesFile.open("../dataset/Project1DataSetSmall/Pipes_Madeira.csv");
        reservoirsFile.open("../dataset/Project1DataSetSmall/Reservoirs_Madeira.csv");
    }

    getline(citiesFile, line);
    getline(stationsFile, line);
    getline(pipesFile, line);
    getline(reservoirsFile, line);

    // Lines with empty fiels at the end should be getting automatically ignored
    while (getline(citiesFile, line)) {
        std::stringstream lineStream(line);
        string id, demand, population, code, cityName;
        if (std::getline(lineStream, cityName, ',')
            && getline(lineStream, id, ',')
            && getline(lineStream, code, ',')
            && getline(lineStream, demand, ',')
            && getline(lineStream, population)) {
            if (population.back() == '\r') population.pop_back(); // Remove last character (which is a '\r' character)
            if (!isLarge) {
                population.erase(std::remove(population.begin(), population.end(), '\"'), population.end());  // Remove double quotes
                population.erase(std::remove(population.begin(), population.end(), ','), population.end());
            }
            auto *city = new City(cityName, stoi(id), code, stoi(demand), stoi(population));
            _waterNetwork.addVertex(city);
        }
    }

    while (getline(stationsFile, line)) {
        // Skip empty lines (like last line in Stations_Madeira.csv)
        if (std::all_of(line.begin(), line.end(), [](const char c) { return c == ','; })) {
            continue;
        }

        std::stringstream lineStream(line);
        string id, code;
        if (std::getline(lineStream, id, ',') && getline(lineStream, code, ',')) {
            if (code.back() == '\r') code.pop_back(); // Remove last character (which is a '\r' character)
            auto station = new Station(stoi(id), code);
            _waterNetwork.addVertex(station);
        }
    }

    while (getline(reservoirsFile, line)) {
        std::stringstream lineStream(line);
        string name, municipality, id, code, maxDelivery;
        if (std::getline(lineStream, name, ',')
            && getline(lineStream, municipality, ',')
            && getline(lineStream, id, ',')
            && getline(lineStream, code, ',')
            && getline(lineStream, maxDelivery, ',')) {
            if (maxDelivery.back() == '\r') maxDelivery.pop_back(); // Remove last character (which is a '\r' character)
            auto *reservoir = new Reservoir(name, municipality, stoi(id), code, stoi(maxDelivery));
            _waterNetwork.addVertex(reservoir);
        }
    }

    while (getline(pipesFile, line)) {
        std::stringstream lineStream(line);
        string direction, src, dest, capacity;
        if (getline(lineStream, src, ',')
            && getline(lineStream, dest, ',')
            && getline(lineStream, capacity, ',')
            && getline(lineStream, direction, ',')) {
            //if last character is a '\r' character, remove it
            if (direction.back() == '\r') direction.pop_back();

            auto source = _waterNetwork.findVertex(src);
            auto destination = _waterNetwork.findVertex(dest);

            if (source == nullptr || destination == nullptr) {
                cout << "Error: Source or destination vertex does not exist" << endl;
            }
            _waterNetwork.addEdge(src, dest, stoi(capacity));
            if (stoi(direction) == 0) {
                _waterNetwork.addEdge(dest, src, stoi(capacity));
            }
        }
    }
}


void WaterSupplyManager::runEdmondsKarp(Network copyNetwork, bool improvedBalance) {
    auto *superSource = new Node(0, "superSource");
    auto *superSink = new Node(1, "superSink");
    copyNetwork.addVertex(superSource);
    copyNetwork.addVertex(superSink);

    for (auto [fst, snd]: copyNetwork.getNodeSet()) {
        Node *node = snd;
        if (const auto reserv = dynamic_cast<Reservoir *>(node)) {
            copyNetwork.addEdge(superSource->getCode(), reserv->getCode(), reserv->getMaxDelivery());
        }
        if (const auto city = dynamic_cast<City *>(node)) {
            copyNetwork.addEdge(city->getCode(), superSink->getCode(), city->getDemand());
        }
    }

    _edmondsKarp.edmondsKarp(copyNetwork, superSource->getCode(), superSink->getCode(), improvedBalance);
}

void WaterSupplyManager::maxFlow(const std::string &destCity) {
    Network copyNetwork = _waterNetwork;
    runEdmondsKarp(copyNetwork, false);

    // Print the flow for a specific city or for all of them, depending on the choice of the user
    if (!destCity.empty()) {
        City *cityNode = nullptr;
        for (auto [fst, snd] : copyNetwork.getNodeSet()) {
            if (auto city = dynamic_cast<City *>(snd)) {
                if (city->getCity() == destCity) {
                    cityNode = dynamic_cast<City *>(snd);
                    break;
                }
            }
        }
        if (cityNode) {
            int flow = 0;
            for (const auto pipe : cityNode->getIncoming()) {
                flow += pipe->getFlow();
            }
            cout << "City: " << cityNode->getCity() << " | Code: " << cityNode->getCode() << " | Flow: " << flow << endl;
        } else {
            cout << "City not found. " << destCity << endl;
        }
    } else {
        for (auto [fst, snd]: copyNetwork.getNodeSet()) {
            Node *node = snd;
            if (const auto city = dynamic_cast<City *>(node)) {
                int flow = 0;
                for (const auto pipe: city->getIncoming()) {
                    flow += pipe->getFlow();
                }
                cout << "City: " << city->getCity() << " | Code: " << city->getCode() << " | Flow: " << flow << endl;
            }
        }
    }
}


void WaterSupplyManager::canNetworkMeetWaterNeeds() {
    //Using the same approach as before
    Network copyNetwork = _waterNetwork;
    runEdmondsKarp(copyNetwork, false);

    // Check if each city's demand is met
    for (auto &[_, node] : _waterNetwork.getNodeSet()) {
        if (City *city = dynamic_cast<City *>(node)) {
            int demand = city->getDemand();
            int actualFlow = 0;
            for (const auto pipe : city->getIncoming()) {
                actualFlow += pipe->getFlow();
            }
            int deficit = demand - actualFlow;
            if (deficit > 0) {
                std::cout << city->getCode() << "-" << city->getCity() << std::endl;
                std::cout << "Deficit: " << deficit << std::endl;
                std::cout << std::endl;
            }
        }
    }
}

void WaterSupplyManager::minimizeDifferencesFlowCapacity() {
//Using the same approach as before
    Network copyNetwork = _waterNetwork;
    cout << "Original network:" << endl;
    runEdmondsKarp(copyNetwork, false);
    Metrics metrics;
    metrics.calculateMetrics(copyNetwork);
    cout << "Average: " << metrics.average << endl;
    cout << "Variance: " << metrics.variance << endl;
    cout << "Max Difference: " << metrics.maxDifference << endl;


    Network copyNetwork2 = _waterNetwork;
    //Reset flow

    cout << endl << "Improved balance network:" << endl;
    runEdmondsKarp(copyNetwork2, true);
    Metrics metrics2;
    metrics2.calculateMetrics(copyNetwork2);
    cout << "Average: " << metrics2.average << endl;
    cout << "Variance: " << metrics2.variance << endl;
    cout << "Max Difference: " << metrics2.maxDifference << endl;

}

void WaterSupplyManager::citiesAffectedByNodeRemoval(const std::string &src) {
    runEdmondsKarp(_waterNetwork, false);

    unordered_map<string, int> citiesFlow;
    //Store a copy of the flow for each city
    for (auto &[_, node] : _waterNetwork.getNodeSet()) {
        if (auto city = dynamic_cast<City *>(node)) {
            int flow = 0;
            for (const auto pipe : city->getIncoming()) {
                flow += pipe->getFlow();
            }
            citiesFlow[city->getCode()] = flow;
        }
    }

    //Removed the reservoir from the network (make a copy before so you cann add it back later)
    _waterNetwork.removeVertex(src);
    runEdmondsKarp(_waterNetwork, false);

    //Check the flow for each city and compare it with the previous flow (if it is smaller, print the city)
    bool flag = false;
    for (auto &[_, node] : _waterNetwork.getNodeSet()) {
        if (auto city = dynamic_cast<City *>(node)) {
            int flow = 0;
            for (const auto pipe : city->getIncoming()) {
                flow += pipe->getFlow();
            }
            if (flow < citiesFlow[city->getCode()]) {
                cout << "City: " << city->getCity() << " | Code: " << city->getCode() << " | Old Flow: " << citiesFlow[city->getCode()] << " | New Flow: " << flow << endl;
                flag = true;
            }
        }
    }
    if (!flag) {
        cout << "No city was affected by the removal of the pipe" << endl;
    }
}

void WaterSupplyManager::citiesAffectedByPipeRemoval(const string &src, const string &dest) {
    runEdmondsKarp(_waterNetwork, false);

    unordered_map<string, int> citiesFlow;
    //Store a copy of the flow for each city
    for (auto &[_, node] : _waterNetwork.getNodeSet()) {
        if (auto city = dynamic_cast<City *>(node)) {
            int flow = 0;
            for (const auto pipe : city->getIncoming()) {
                flow += pipe->getFlow();
            }
            citiesFlow[city->getCode()] = flow;
        }
    }

    _waterNetwork.removeEdge(src, dest);
    runEdmondsKarp(_waterNetwork, false);

    //Check the flow for each city and compare it with the previous flow (if it is smaller, print the city)
    bool flag = false;
    for (auto &[_, node] : _waterNetwork.getNodeSet()) {
        if (auto city = dynamic_cast<City *>(node)) {
            int flow = 0;
            for (const auto pipe : city->getIncoming()) {
                flow += pipe->getFlow();
            }
            if (flow < citiesFlow[city->getCode()]) {
                cout << "City: " << city->getCity() << " | Code: " << city->getCode() << " | Old Flow: " << citiesFlow[city->getCode()] << " | New Flow: " << flow << endl;
                flag = true;
            }
        }
    }
    if (!flag) {
        cout << "No city was affected by the removal of the pipe" << endl;
    }
}
