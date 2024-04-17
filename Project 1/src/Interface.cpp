#include "Interface.h"

#include <iostream>

// WaterSupplyManager Interface::_waterSupplyManager;

void Interface::run() {
    system("clear");
    bool running = true;
    while (running) {
        switch (displayDataSetMenu()) {
            case 1:
                _waterSupplyManager.readCSV(false);
                running = false;
                break;
            case 2:
                _waterSupplyManager.readCSV(true);
                running = false;
                break;
            default:
                std::cout << "Please, insert a valid number" << std::endl;
                std::cout << "Press enter to continue...";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }

    running = true;

    while (running) {
        switch (displayMainMenu()) {
            case 0:
                std::cout << "Goodbye!" << std::endl;
                std::cout << "Press Enter to exit.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
                running = false;
                break;
            case 1:
                basicMetricsMenu();
                break;
            case 2:
                lineFailureMenu();
                break;
            default:
                std::cout << "Please, insert a valid number" << std::endl;
                std::cout << "Press enter to continue...";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}

int Interface::displayDataSetMenu() {
    cout << "Please, select the dataset you want to use: " << endl;
    cout << "1. Small Dataset" << endl;
    cout << "2. Large Dataset" << endl;
    int choice;
    cin >> choice;
    return choice;
}

int Interface::displayMainMenu() {
    system("clear");
    std::cout << "====================== Main Menu ====================== \n";
    std::cout << "======================================================= \n";
    std::cout << " 1. Basic Service Metrics                               \n";
    std::cout << " 2. Reliability and Sensitivity to Line Failures        \n";
    std::cout << std::endl;
    std::cout << " Enter your choice (1-2)                                \n";
    std::cout << " Press '0' to exit.                                     \n";
    std::cout << std::endl;
    std::cout << "======================================================= \n";
    int choice;
    std::cin >> choice;
    return choice;
}

int Interface::displayBasicMetricsMenu() {
    system("clear");
    std::cout << "================== Basic Service Metrics ==================\n";
    std::cout << "===========================================================\n";
    std::cout << std::endl;
    std::cout << " 1. Maximum amount of water that can reach each or a specific city.\n";
    std::cout << " 2. Can an existing network configuration meet the water needs"
            " of its customer? \n";
    std::cout << " 3. Show that you can minimize the differences of flow to capacity"
            " on each pipe across the entire network. \n";
    std::cout << std::endl;
    std::cout << " Enter your choice (1-3)                                   \n";
    std::cout << " Press '0' to return                                        \n";
    std::cout << std::endl;
    std::cout << "==========================================================\n";
    int option;
    std::cin >> option;
    return option;
}

void Interface::basicMetricsMenu() {
    bool running = true;
    while (running) {
        switch (displayBasicMetricsMenu()) {
            case 0:
                running = false;
                break;
            case 1:
                DisplayOptionFlow();
                break;
            case 2:
                _waterSupplyManager.canNetworkMeetWaterNeeds();
                std::cout << "Press enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            case 3:
                _waterSupplyManager.minimizeDifferencesFlowCapacity();
                std::cout << "Press enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            default:
                std::cout << "Please, insert a valid number" << std::endl;
                std::cout << "Press enter to continue...";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}

void Interface::DisplayOptionFlow() {
    std::cout << "Do you want to display flow for a specific city or for all cities?" << std::endl;
    std::cout << "1. Display flow for a specific city" << std::endl;
    std::cout << "2. Display flow for all cities" << std::endl;
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            displayFlowSpecificCity();
            break;
        case 2:
            displayFlowAllCities();
            break;
        default:
            std::cout << "Please, insert a valid number" << std::endl;
            std::cout << "Press enter to continue...";
            std::cin.ignore();
            std::cin.get();
            system("clear");
            break;
    }
}

void Interface::displayFlowSpecificCity() {
    std::string city;
    std::cout << "Enter the name of the city:\n";
    std::cin.ignore();
    getline(std::cin, city);
    std::cout << std::endl;
    std::cout << "The calculation is in process...\n";
    _waterSupplyManager.maxFlow(city);
    std::cout << "Press enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void Interface::displayFlowAllCities() {
    std::cout << "The calculation is in process...\n";
    _waterSupplyManager.maxFlow("");
    std::cout << "Press enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

int Interface::displayLineFailureMenu() {
    system("clear");
    std::cout << "========= Reliability and Sensitivity to Line Failures =========\n";
    std::cout << "===========================================================\n";
    std::cout << std::endl;
    std::cout << " 1. Which cities are affected if one water reservoir is out of service \n";
    std::cout << " 2. Which cities are affected if one pumping station is out of service \n";
    std::cout << " 3. Which cities are affected if on pipe is out of service \n";
    std::cout << std::endl;
    std::cout << " Enter your choice (1-3)                                   \n";
    std::cout << " Press '0' to exit.                                        \n";
    std::cout << std::endl;
    std::cout << "==========================================================\n";
    int option;
    std::cin >> option;
    return option;
}

void Interface::lineFailureMenu() {
    bool running = true;
    while (running) {
        std::string src, dest;
        switch (displayLineFailureMenu()) {
            case 0:
                running = false;
                break;
            case 1:
                std::cin.ignore();
                cout << "Enter the code of the water reservoir that will be out of service: ";
                getline(std::cin, src);
                std::cout << std::endl;
                _waterSupplyManager.citiesAffectedByNodeRemoval(src);
                std::cout << std::endl;
                std::cout << " Press Enter to back to continue...                                       \n";
                std::cout << std::endl;
                std::cin.ignore();
                std::cin.get();
                break;
            case 2:
                std::cin.ignore();
                cout << "Enter the code of the water reservoir that will be out of service: ";
                getline(std::cin, src);
                std::cout << std::endl;
                _waterSupplyManager.citiesAffectedByNodeRemoval(src);
                std::cout << std::endl;
                std::cout << " Press Enter to back to continue...                                       \n";
                std::cout << std::endl;
                std::cin.ignore();
                std::cin.get();
                break;
            case 3:
                std::cin.ignore();
                cout << "Enter the code of the source of the pipe that will be out of service: ";
                cin >> src;
                cout << "Enter the code of the destination of the pipe that will be out of service: ";
                cin >> dest;
                std::cout << std::endl;
                _waterSupplyManager.citiesAffectedByPipeRemoval(src, dest);
                std::cout << " Press Enter to back to continue...                                       \n";
                std::cout << std::endl;
                std::cin.ignore();
                std::cin.get();
                break;
            default:
                std::cout << "Please, insert a valid number" << std::endl;
                std::cout << "Press enter to continue...";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}
