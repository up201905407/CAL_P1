#include <iostream>
#include "src/Graph/Graph.h"
#include "src/GraphBuilder/graphbuilder.h"
#include "src/Utils/utils.h"
#include "src/Gui/gui.h"

int main() {
    Graph<unsigned long int> graph;
    GraphBuilder<unsigned long int> graphBuilder(&graph);
    std::string city = "porto";
    if (!graphBuilder.fillGraph(city)){
        std::cout << "error" << std::endl;
    }
    Gui<unsigned long int> gui(&graph);
    gui.graphViewer();
    return 0;
}
