#include "Interface.h"
#include <iostream>
using namespace std;

void Interface::run() {
    system("clear");
    bool running = true;
    while (running) {
        switch (displayDataSetMenu()) {
            case 0:
                std::cout << "Goodbye!" << std::endl;
                std::cout << "Press Enter to exit.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
                running = false;
                break;
            case 1:
                menuExtraFullyConnectedGraphs();
                running = false;
                break;
            case 2:
                menuRealWorldGraphs();
                running = false;
                break;
            case 3:
                menuToyGraphs();
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
        switch (displayStatementOfWork()) {
            case 0:
                std::cout << "Goodbye!" << std::endl;
                std::cout << "Press Enter to exit.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
                running = false;
                break;
            case 1:
                //Backtracking Algorithm
                manager.backtracking();
                break;
            case 2:
                //Triangular Approximation Heuristic
                manager.TriangularApproximation();
                break;
            case 3:
                //Other Heuristics
                manager.Faster2ApproximationTSP();
                std::cout << "\nPress enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;
            case 4:
                //TSP in the Real World
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

int Interface::displayDataSetMenu() {
    cout << "Please, select the dataset you want to use: " << endl;
    cout << "1. Extra Fully Connected Graphs" << endl;
    cout << "2. Real Word Graphs" << endl;
    cout << "3. Toy Graph" << endl;
    int choice;
    cin >> choice;
    return choice;
}

int Interface::displayStatementOfWork() {
    system("clear");
    std::cout << "================== Statement Of Work ==================\n";
    std::cout << "===========================================================\n";
    std::cout << std::endl;
    std::cout << " 1. Backtracking Algorithm.                             \n";
    std::cout << " 2. Triangular Approximation Heuristic.                 \n";
    std::cout << " 3. Other Heuristics.                                   \n";
    std::cout << " 4. TSP in the Real World.                              \n";
    std::cout << std::endl;
    std::cout << " Enter your choice (1-4)                                  \n";
    std::cout << " Press '0' to exit program                                \n";
    std::cout << std::endl;
    std::cout << "==========================================================\n";
    int option;
    std::cin >> option;
    return option;
}

void Interface::menuToyGraphs() {
    const std::vector<std::string> graphFiles = {"shipping.csv", "stadiums.csv", "tourism.csv"};

    while (true) {
        cout << "\n======================== Toy Graphs ===================== \n";
        cout << "======================================================= \n\n";

        for (size_t i = 0; i < graphFiles.size(); ++i) {
            cout << i + 1 << ". " << graphFiles[i] << "\n";
        }

        cout << "\n======================================================= \n";
        cout << "Enter your choice (1-" << graphFiles.size() << "):";
        cout << " Press '0' to exit.                                      \n";

        int choice;
        cin >> choice;

        if (choice == 0) {
            break;
        } else if (choice > 0 && choice <= graphFiles.size()) {
            manager.readToyGraph(graphFiles[choice - 1]);
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
            cin.ignore();
            cin.get();
            system("clear");
        }
    }
}

void Interface::menuRealWorldGraphs() {
    const std::vector<std::string> graphNames = {"graph1", "graph2", "graph3"}; // Store graph names

    while (true) {
        cout << "\n==================== Real World Graphs ================== \n";
        cout << "======================================================= \n\n";

        for (size_t i = 0; i < graphNames.size(); ++i) {
            cout << i + 1 << ". " << graphNames[i] << "\n"; // Display graph options dynamically
        }

        cout << "\n======================================================= \n";
        cout << "Enter your choice (1-" << graphNames.size() << "):";
        cout << " Press '0' to exit.                                      \n";

        int choice;
        cin >> choice;

        if (choice == 0) {
            break;
        } else if (choice > 0 && choice <= graphNames.size()) {
            manager.readRealWorldGraph(graphNames[choice - 1]); // Access graph name from vector
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
            cin.ignore();
            cin.get();
            system("clear");
        }
    }
}

void Interface::menuExtraFullyConnectedGraphs() {
    const std::vector<int> edgeOptions = {25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900};

    while (true) {
        cout << "\n=============== Extra Fully Connected Graphs ============== \n";
        cout << "======================================================= \n\n";

        for (size_t i = 0; i < edgeOptions.size(); ++i) {
            cout << i + 1 << ".  " << edgeOptions[i] << " edges\n";
        }

        cout << "\n======================================================= \n";
        cout << "Enter your choice (1-" << edgeOptions.size() << "):";
        cout << " Press '0' to exit.                                      \n";

        int choice;
        cin >> choice;

        if (choice == 0) {
            break;
        } else if (choice > 0 && choice <= edgeOptions.size()) {
            manager.readExtraFullyConnectedGraph(edgeOptions[choice - 1]);
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
            cin.ignore();
            cin.get();
            system("clear");
        }
    }
}





