#include <iostream>
#include "menu.h"

Menu::Menu(Company *company){
    this->company = company;
}

void Menu::init(){
    while (true){
        std::cout << "1 - Insert data" << std::endl;
        std::cout << "2 - Verify connectivity" << std::endl;
        std::cout << "3 - Get shortest path" << std::endl;
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
                insertionMenu();
                break;
            case 2:
                // função que verifica conetividade
                // if (tudo ok)
                //    std::cout << "It is possible to deliver all orders!" << std::endl << std::endl << std::endl;
                // else
                //    std::cout << "It's not possible to deliver all orders. Our fleet can't reach all destinations." << std::endl << std::endl << std::endl;
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

void Menu::insertionMenu(){
    while (true){
        std::cout << "1 - Create vehicle" << std::endl;
        std::cout << "2 - Create package" << std::endl;
        std::cout << "3 - Create basket" << std::endl;
        std::cout << "4 - Back" << std::endl;
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
                //createPackage();
                break;
            case 3:
                createBasket();
                break;
            case 4:
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