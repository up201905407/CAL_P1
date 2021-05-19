#include <iostream>
#include "src/Graph/Graph.h"
#include "src/GraphBuilder/graphbuilder.h"
#include "src/Utils/utils.h"
#include "src/Gui/gui.h"
#include "src/Menu/menu.h"

void print(std::vector<unsigned long int> const &input)
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
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
    /*
    Graph<unsigned long int> graph;
    GraphBuilder<unsigned long int> graphBuilder(&graph);
    std::string city = "porto";
    if (!graphBuilder.fillGraph(city)){
        std::cout << "error" << std::endl;
    }
    Gui<unsigned long int> gui(&graph);
    unsigned long int start = 90379359;
    unsigned long int end = 90379614;
    //gui.graphViewer();
    std::cout << graph.aStarShortestPath(start, end) << std::endl;
    print(graph.getPath(start, end));
    //sccViewer(graph.getTarjanStronglyConnectedVertex());

    gui.graphViewerWithPath(start, end);
    return 0;*/
    Company company;
    Menu menu(&company);
    menu.init();
    return 0;
}
