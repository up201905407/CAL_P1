#include <iostream>
#include "src/Graph/Graph.h"
#include "src/GraphBuilder/graphbuilder.h"
#include "src/ClarkeWright/ClarkeWright.h"
#include "src/Gui/gui.h"
#include "src/Company/company.h"
#include "src/Vehicle/vehicle.h"
#include "src/Basket/basket.h"
#include "src/Menu/menu.h"


void print(std::vector<unsigned long int> const &input)
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
    std::cout<<std::endl;
}

void sccViewer(std::set<std::set<unsigned long int>> input){
    for(auto i = input.begin(); i!=input.end(); i++){
        std::cout<<"->";
        for (auto it = i->begin(); it!=i->end(); it++) {
            std::cout << *(it) << ' ';
        }
        std::cout<<std::endl;
    }
}

int main() {
    Graph<unsigned long int> graph;
    GraphBuilder<unsigned long int> graphBuilder(&graph);
    std::string city = "porto";
    if (!graphBuilder.fillGraph(city)){
        std::cout << "error" << std::endl;
    }
    //Gui<unsigned long int> gui(&graph);
    //int scc_Vertexes = gui.graphViewerConnectivityCheck(graph.getTarjanStronglyConnectedVertex());
    //std::cout<<"Total number of Vertexes: "<<graph.getNumVertex()<<std::endl<< "Vertexes belonging to a SCC: "<<scc_Vertexes<<std::endl<<"Ratio: "<<(double)scc_Vertexes/(double )graph.getNumVertex() * 100<<"%"<<std::endl;
    unsigned long int depot = 111447975;

    Company company(depot);

    /** Testing purposes**/
    Vehicle v1(30);
    Vehicle v2(40);
    Vehicle v3(14);
    Vehicle v4(18);

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

    //Testing purposes
    /*
    ClarkeWright<unsigned long int> clarkeWright(&graph,&company);

    clarkeWright.clarkeWight();

    for(Vehicle *vehicle : company.getFleet()){
        print(vehicle->getPathList());
    }
*/
    Gui<unsigned long int> gui(&graph, &company);
    Menu menu(&company, &graph, &gui);
    menu.init();

    return 0;

}
