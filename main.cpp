#include <iostream>
#include "src/Graph/Graph.h"
#include "src/GraphBuilder/graphbuilder.h"
#include "src/Gui/gui.h"
#include "src/Company/company.h"
#include "src/Vehicle/vehicle.h"
#include "src/Basket/basket.h"
#include "src/Menu/menu.h"

int main(){
    Graph<unsigned long int> graph;
    GraphBuilder<unsigned long int> graphBuilder(&graph);
    std::string city = "porto";
    if (!graphBuilder.fillGraph(city)){
        std::cout << "Error fill Graph" << std::endl;
    }
    unsigned long int depot = 111447975;

    Company company(depot);
    /* TESTING*/


    Vehicle v2(10);
    Vehicle v3(14);
    Vehicle v4(18);
    Vehicle v1(30);

    Basket b1("Luis", 20, 111447978, 1);
    Basket b2("Luis", 10, 111447980, 2);
    Basket b3("Luis", 15, 111447984, 3);
    Basket b4("Luis", 5, 111447981, 4);

    company.addVehicle(&v1);
    company.addVehicle(&v2);
    company.addVehicle(&v3);
    company.addVehicle(&v4);

    company.addBasket(&b1);
    company.addBasket(&b2);
    company.addBasket(&b3);
    company.addBasket(&b4);

    Gui<unsigned long int> gui(&graph, &company);
    Menu menu(&company, &graph, &gui);
    menu.init();

    return 0;

}
