#include <iostream>
#include "menu.h"
#include "../ClarkeWright/ClarkeWright.h"


Menu::Menu(Company *company, Graph<unsigned long int> *graph, Gui<unsigned long int> *gui){
    this->company = company;
    this->graph = graph;
    this->gui = gui;

}


void Menu::init(){
    while (true){
        std::cout << "1 - View fleet and baskets" << std::endl;
        std::cout << "2 - Edit data" << std::endl;
        std::cout << "3 - Verify connectivity" << std::endl;
        std::cout << "4 - Distribute baskets by vehicles and get shortest path" << std::endl;
        std::cout << "5 - Exit" << std::endl;
        int userInput;
        std::cout << "-> ";
        std::cin >> userInput;
        if (std::cin.fail() || std::cin.eof()){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid option" << std::endl;
            continue;
        }
        std::cin.ignore(1000, '\n');
        switch (userInput) {
            case 1:
                viewMenu();
                break;
            case 2:
                dataMenu();
                break;
            case 3:
                connectivityMenu();
                break;
            case 4:
                resultsMenu();
                break;
            case 5:
                // guardar dados num ficheiro
                return;
            default:
                std::cout << "Please enter a valid option" << std::endl;
                continue;
        }
    }
}

void Menu::viewMenu() {
    while (true) {
        std::cout << "1 - View fleet" << std::endl;
        std::cout << "2 - View Baskets" << std::endl;
        std::cout << "3 - Back" << std::endl;
        int userInput;
        std::cout << "-> ";
        std::cin >> userInput;
        if (std::cin.fail() || std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid option" << std::endl;
            continue;
        }
        std::cin.ignore(1000, '\n');
        switch (userInput) {
            case 1:
                viewFleet();
                break;
            case 2:
                viewBaskets();
                break;
            case 3:
                return;
            default:
                std::cout << "Please enter a valid option" << std::endl;
                continue;
        }
    }
}

void Menu::viewFleet(){
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "                   Fleet                   " << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << std::endl;
    int counter = 1;
    for (Vehicle* vehicle : company->getFleet()){
        std::cout << "Vehicle #" << counter << std::endl;
        std::cout << "  Id: " << vehicle->getId() << std::endl;
        std::cout << "  Capacity: " << vehicle->getMaxCap() << std::endl;
        counter++;
        std::cout << std::endl;
    }
    std::string input;
    std::cout << "Press ENTER to return...";
    std::getline(std::cin, input); //only to acknowledge that the user pressed a key

}

void Menu::viewBaskets(){
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "                 Baskets                   " << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << std::endl;
    int counter = 1;
    for (Basket* basket : company->getBaskets()){
        std::cout << "Basket #" << counter << std::endl;
        std::cout << "  Id Dest: " << basket->getIdDest() << std::endl;
        std::cout << "  Num Fat: " << basket->getNumFat() << std::endl;
        std::cout << "  Num Pack: " << basket->getNumPack() << std::endl;
        counter++;
        std::cout << std::endl;
    }
    std::string input;
    std::cout << "Press ENTER to return...";
    std::getline(std::cin, input); //only to acknowledge that the user pressed a key
}

void Menu::dataMenu(){
    while (true){
        std::cout << "1 - Create vehicle" << std::endl;
        std::cout << "2 - Create basket" << std::endl;
        std::cout << "3 - Delete vehicle" << std::endl;
        std::cout << "4 - Delete basket" << std::endl;
        std::cout << "5 - Back" << std::endl;
        int userInput;
        std::cout << "-> ";
        std::cin >> userInput;
        if (std::cin.fail() || std::cin.eof()){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid option" << std::endl;
            continue;
        }
        std::cin.ignore(1000, '\n');
        switch (userInput) {
            case 1:
                createVehicle();
                break;
            case 2:
                createBasket();
                break;
            case 3:
                deleteVehicle();
                break;
            case 4:
                deleteBasket();
                break;
            case 5:
                return;
            default:
                std::cout << "Please enter a valid option" << std::endl;
                continue;
        }
    }
}

void Menu::connectivityMenu() {
    int counter ;
    while (true){
        std::cout << "1 - Confirm and show results" << std::endl;
        std::cout << "2 - Back" << std::endl;
        int userInput;
        std::cout << "-> ";
        std::cin >> userInput;
        if (std::cin.fail() || std::cin.eof()){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid option" << std::endl;
            continue;
        }
        std::cin.ignore(1000, '\n');
        switch(userInput){
            case 1:
                counter = gui->graphViewerConnectivityCheck(graph->getTarjanStronglyConnectedVertex());
                std::cout<<"Total number of Vertexes: "<<graph->getNumVertex()<<std::endl<< "Vertexes belonging to a SCC: "<<counter<<std::endl<<"Ratio: "<<(double)counter/(double )graph->getNumVertex() * 100<<"%"<<std::endl;
                break;
            case 2:
                return;
            default:
                std::cout << "Please enter a valid option" << std::endl;
                continue;
        }
    }
}

void Menu::resultsMenu(){
    // mostrar mapa
    // mostrar o caminho de cada veículo
    ClarkeWright<unsigned long int> clarkeWright(graph,company);
    while (true){
        std::cout << "1 - Confirm and show results" << std::endl;
        std::cout << "2 - Back" << std::endl;
        int userInput;
        std::cout << "-> ";
        std::cin >> userInput;
        if (std::cin.fail() || std::cin.eof()){
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a valid option" << std::endl;
            continue;
        }
        std::cin.ignore(1000, '\n');
        switch (userInput) {
            case 1:
                clarkeWright.clarkeWight();
                for(Vehicle *vehicle : company->getFleet()) {
                    for (int i = 0; i < ((int)vehicle->getPathList().size()) - 1; i++) {
                        std::cout << i << "<" << (vehicle->getPathList().size() -1) << std::endl;
                        if (!graph->aStarShortestPath(vehicle->getPathList()[i], vehicle->getPathList()[i + 1])) {
                            std::cout << "ERROR" << std::endl;
                            return;
                        }
                        vehicle->addPath(graph->getPath(vehicle->getPathList()[i], vehicle->getPathList()[i + 1]));
                    }
                }
                gui->graphViewerWithPath();
                break;
            case 2:
                return;
            default:
                std::cout << "Please enter a valid option" << std::endl;
                continue;
        }
    }
}

void Menu::createVehicle(){
    std::cout << "Please enter vehicle capacity" << std::endl;
    int vehicleCap;
    std::cout << "-> ";
    std::cin >> vehicleCap;
    while (std::cin.fail() || std::cin.eof() || vehicleCap <= 0){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Please enter vehicle capacity" << std::endl;
        std::cin >> vehicleCap;
    }
    Vehicle* v = new Vehicle(vehicleCap);
    company->addVehicle(v);
    return;
}

void Menu::createBasket(){
    std::cout << "Please enter client name" << std::endl;
    std::string clientName;
    std::cout << "-> ";
    getline(std::cin, clientName);
    while (std::cin.fail() || std::cin.eof()){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Please enter client name" << std::endl;
        getline(std::cin, clientName);
    }

    std::cout << "Please enter number of packages" << std::endl;
    int numPack;
    std::cout << "-> ";
    std::cin >> numPack;
    while (std::cin.fail() || std::cin.eof() || numPack <= 0){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Please enter number of packages" << std::endl;
        std::cin >> numPack;
    }

    std::cout << "Please enter id of destination" << std::endl;
    int idDest;
    std::cin >> idDest;
    while (std::cin.fail() || std::cin.eof() || idDest <= 0){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Please enter id of destination" << std::endl;
        std::cin >> idDest;
    }

    std::cout << "Please enter invoice number" << std::endl;
    int numFat;
    std::cout << "-> ";
    std::cin >> numFat;
    while (std::cin.fail() || std::cin.eof() || numFat <= 0){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Please enter invoice number" << std::endl;
        std::cin >> numFat;
    }

    Basket* b = new Basket(clientName, numPack, idDest, numFat);
    company->addBasket(b);
    return;
}


void Menu::deleteVehicle(){
    std::cout << "Please enter the id of vehicle to be erased" << std::endl;
    int vehicleId;
    std::cout << "-> ";
    std::cin >> vehicleId;
    while (std::cin.fail() || std::cin.eof() || vehicleId < 0){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Please enter vehicle capacity" << std::endl;
        std::cin >> vehicleId;
    }
    company->removeVehicle(vehicleId);
    return;
}


void Menu::deleteBasket(){
    std::cout << "Please enter the numFat of basket to be erased" << std::endl;
    int numFat;
    std::cout << "-> ";
    std::cin >> numFat;
    while (std::cin.fail() || std::cin.eof() || numFat < 0){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Please enter vehicle capacity" << std::endl;
        std::cin >> numFat;
    }
    company->removeBasket(numFat);
    return;
}
