#include <iostream>
#include "menu.h"


Menu::Menu(Company *company,Graph<unsigned long int> *graph){
    this->company = company;
    this->graph = graph;

}


void Menu::init(){
    this->gui = Gui<unsigned long int>(this->graph);
    while (true){
        std::cout << "1 - Edit data" << std::endl;
        std::cout << "2 - Verify connectivity" << std::endl;
        std::cout << "3 - Distribute baskets by vehicles and get shortest path" << std::endl;
        std::cout << "4 - Exit" << std::endl;
        int userInput;
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
                //insertionMenu();
                break;
            case 2:
                connectivityMenu();
                break;
            case 3:
                resultsMenu();
                break;
            case 4:
                // guardar dados num ficheiro
                return;
            default:
                std::cout << "Please enter a valid option" << std::endl;
                continue;
        }
    }
}

void Menu::dataMenu(){
    while (true){
        std::cout << "1 - Create vehicle" << std::endl;
        std::cout << "2 - Create basket" << std::endl;
        std::cout << "3 - Delete vehicle" << std::endl;
        std::cout << "4 - Delete basket" << std::endl;
        std::cout << "5 - Back" << std::endl;
        int userInput;
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
                counter = gui.graphViewerConnectivityCheck(graph->getTarjanStronglyConnectedVertex());
                std::cout<<"Total number of Vertexes: "<<graph->getNumVertex()<<std::endl<< "Vertexes belonging to a SCC: "<<counter<<std::endl<<"Ratio: "<<(double)counter/(double )graph->getNumVertex() * 100<<"%"<<std::endl;
                _sleep(5);
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
    while (true){
        std::cout << "1 - Confirm and show results" << std::endl;
        std::cout << "2 - Back" << std::endl;
        int userInput;
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
                //this->company.distributeBasketsByVehicles();
                //show graph viewer with path colored
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
    getline(std::cin, clientName);
    while (std::cin.fail() || std::cin.eof()){
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Please enter client name" << std::endl;
        getline(std::cin, clientName);
    }

    std::cout << "Please enter number of packages" << std::endl;
    int numPack;
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
