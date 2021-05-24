#ifndef _GUI_H_
#define _GUI_H_

#include "../Graph/Graph.h"
#include "graphviewer.h"
#include "../Company/company.h"
#include <set>

using Node_Viewer = GraphViewer::Node;
using Edge_Viewer = GraphViewer::Edge;

template<class T>
class Gui{
private:
    Graph<T>* graph;
    Company *company;
    std::vector<GraphViewer::Color> colors = {
            GraphViewer::BLUE,
            GraphViewer::CYAN,
            GraphViewer::DARK_GRAY,
            GraphViewer::GRAY,
            GraphViewer::LIGHT_GRAY,
            GraphViewer::YELLOW
    };
public:
    /**
     * Gui's constructor
     * @param graph
     * @param company
     */
    Gui(Graph<T>* graph, Company* company);
    /**
     * Interface to view the map with the path
     */
    void graphViewerWithPath();
    /**
     * Checks the connectivy of the graph and counts the numbe rof vertex strongly connected
     * @param scc Set containing all the strongly connected componentes
     * @return Number of nodes strongly connected
     */
    int graphViewerConnectivityCheck(const std::set<std::set<T>> &scc);
};

template<class T>
Gui<T>::Gui(Graph<T> *graph, Company* company) {
    this->graph = graph;
    this->company = company;
}

template <class T>
void Gui<T>::graphViewerWithPath(){
    std::vector<std::pair<unsigned long int, std::pair<unsigned long int, unsigned long int>>> edges_pair;
    GraphViewer gv;
    gv.setScale(1.0/4000.0);
    gv.setCenter(sf::Vector2f(-8.600, -41.146));
    int i = 0;
    for(Vertex<T> *vertex : graph->getVertexSet()){
        Node_Viewer &node = gv.addNode(vertex->getInfo(), sf::Vector2f(vertex->getLongitude(), -vertex->getLatitude()));
        node.setOutlineThickness(0.00002);
        node.setSize(0.0001);
        node.setColor(GraphViewer::GREEN);
        for (Edge<T> edge_vertex : vertex->getAdj()){
            edges_pair.push_back({edge_vertex.getInfo(), {vertex->getInfo(), edge_vertex.getDest()->getInfo()}});
        }
    }

    for(auto pair : edges_pair){
        Edge_Viewer &edge = gv.addEdge(pair.first,
                                       gv.getNode(pair.second.first),
                                       gv.getNode(pair.second.second),
                                       GraphViewer::Edge::UNDIRECTED);
        edge.setThickness(0.0001);
        edge.setColor(GraphViewer::RED);
    }

    gv.setBackground(
            "../src/Gui/resources/map.jpg",
            sf::Vector2f(-8.7817, -41.3095),
            sf::Vector2f(1.3297, 1.0)/7010.0f,
            0.8
    );
    int color = 0;
    for (Vehicle * vehicle : company->getFleet()){

        for (auto &info : vehicle->getPathList()){
            Node_Viewer &dest = gv.getNode(info);
            dest.setColor(GraphViewer::MAGENTA);
        }
        for (auto &info : vehicle->getPath()){
            Edge_Viewer &edge = gv.getEdge(info);
            edge.setColor(colors[color % 6]);

        }
        color++;
    }

    Node_Viewer &depot = gv.getNode(company->getDepotInfo());
    depot.setColor(GraphViewer::ORANGE);

    //gv.setEnabledNodes(false); // Disable node drawing
    gv.setEnabledEdgesText(false); // Disable edge text drawing
    gv.setZipEdges(true);
    gv.createWindow(1600, 900);
    gv.join();
}

template<class T>
int Gui<T>::graphViewerConnectivityCheck(const std::set<std::set<T>> &scc) {
    std::vector<std::pair<unsigned long int, std::pair<unsigned long int, unsigned long int>>> edges_pair;
    GraphViewer gv;
    gv.setScale(1.0/4000.0);
    gv.setCenter(sf::Vector2f(-8.600, -41.146));
    int i = 0;
    for(Vertex<T> *vertex : graph->getVertexSet()){
        Node_Viewer &node = gv.addNode(vertex->getInfo(), sf::Vector2f(vertex->getLongitude(), -vertex->getLatitude()));
        node.setOutlineThickness(0.00002);
        node.setSize(0.0001);
        node.setColor(GraphViewer::GREEN);
        for (Edge<T> edge_vertex : vertex->getAdj()){
            edges_pair.push_back({edge_vertex.getInfo(), {vertex->getInfo(), edge_vertex.getDest()->getInfo()}});
        }
    }

    for(auto pair : edges_pair){
        Edge_Viewer &edge = gv.addEdge(pair.first,
                                       gv.getNode(pair.second.first),
                                       gv.getNode(pair.second.second),
                                       GraphViewer::Edge::UNDIRECTED);
        edge.setThickness(0.0001);
        edge.setColor(GraphViewer::WHITE);
    }

    gv.setBackground(
            "../src/Gui/resources/map.jpg",
            sf::Vector2f(-8.7817, -41.3095),
            sf::Vector2f(1.3297, 1.0)/7010.0f,
            0.8
    );

    for(auto set: scc){
        for(auto vertex : set){
            Node_Viewer &vertice = gv.getNode(vertex);
            vertice.setColor(GraphViewer::MAGENTA);
        }
    }

    int counter = 0;
    for(auto node : gv.getNodes()){
        if(node->getColor()==GraphViewer::MAGENTA)
            counter++;
    }


    gv.setEnabledNodes(true); // Disable node drawing
    gv.setEnabledEdgesText(false); // Disable edge text drawing
    gv.setZipEdges(true);
    gv.createWindow(1600, 900);
    gv.join();

    return counter;
}


#endif //_GUI_H_
