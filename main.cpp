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
    /*
    Gui<unsigned long int> gui(&graph);
    unsigned long int start = 90379359;
    unsigned long int end = 90379614;
    //gui.graphViewer();
    //std::cout << graph.aStarShortestPath(start, end) << std::endl;
    //print(graph.getPath(start, end));
    int scc_Vertexes = gui.graphViewerConnectivityCheck(graph.getTarjanStronglyConnectedVertex());
    std::cout<<"Total number of Vertexes: "<<graph.getNumVertex()<<std::endl<< "Vertexes belonging to a SCC: "<<scc_Vertexes<<std::endl<<"Ratio: "<<(double)scc_Vertexes/(double )graph.getNumVertex() * 100<<"%"<<std::endl;
    //gui.graphViewerWithPath(start, end);
         */
    unsigned long int depot = 314075472;

    Company company(depot);

    /** Testing purposes**/
    Vehicle v1(30);
    Vehicle v2(40);
    Vehicle v3(14);
    Vehicle v4(18);

    Basket b1("Luis", 20, 495504022, 1);
    Basket b2("Luis", 10, 111632672, 2);
    Basket b3("Luis", 15, 111632674, 3);
    Basket b4("Luis", 5, 90381067, 4);

    company.addVehicle(&v1);
    company.addVehicle(&v2);
    company.addVehicle(&v3);
    company.addVehicle(&v4);

    company.addBasket(&b1);
    company.addBasket(&b2);
    company.addBasket(&b3);
    company.addBasket(&b4);

     /* Testing purposes
    ClarkeWright<unsigned long int> clarkeWright(&graph,&company);

    clarkeWright.clarkeWight();

    for(Vehicle *vehicle : company.getFleet()){
        print(vehicle->getPathList());
    }
     */

    Menu menu(&company, &graph);
    menu.init();

    return 0;

}
