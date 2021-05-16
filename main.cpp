#include <iostream>
#include "src/Graph/Graph.h"
#include "src/GraphBuilder/graphbuilder.h"
#include "src/Utils/utils.h"
#include "src/Gui/gui.h"

void print(std::vector<unsigned long int> const &input)
{
    for (int i = 0; i < input.size(); i++) {
        std::cout << input.at(i) << ' ';
    }
}

int main() {
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
    std::cout << graph.dijkstraShortestPath(start, end) << std::endl;
    print(graph.getPath(start, end));

    return 0;
}
