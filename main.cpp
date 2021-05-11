#include <iostream>
#include "src/Graph/Graph.h"
#include "src/GraphViewer/graphviewer.h"
#include "src/Utils/utils.h"

int main() {
    Graph<int> graph;
    GraphViewer<int> graphViewer(&graph);
    std::string city = "porto";
    graphViewer.fillGraph(city);
    graph.print();
    return 0;
}
