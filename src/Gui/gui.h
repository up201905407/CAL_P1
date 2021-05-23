#ifndef _GUI_H_
#define _GUI_H_

#include "../Graph/Graph.h"
#include "graphviewer.h"
#include <set>

using Node_Viewer = GraphViewer::Node;
using Edge_Viewer = GraphViewer::Edge;


template<class T>
class Gui{
private:
    Graph<T>* graph;
public:
    Gui(Graph<T>* graph);
    void graphViewer();
    void graphViewerWithPath(const T &origin, const T &dest);
    int graphViewerConnectivityCheck(const std::set<std::set<T>> &scc);
};

template<class T>
Gui<T>::Gui(Graph<T> *graph) {
    this->graph = graph;
}

template<class T>
void Gui<T>::graphViewer() {

    std::vector<std::pair<unsigned long int, std::pair<unsigned long int, unsigned long int>>> edges_pair;
    GraphViewer gv;
    gv.setScale(1.0/4000.0);
    gv.setCenter(sf::Vector2f(-8.600, -41.146));
    int i = 0;
    for(Vertex<T> *vertex : graph->getVertexSet()){
        Node_Viewer &node = gv.addNode(vertex->getInfo(), sf::Vector2f(vertex->getLongitude(), -vertex->getLatitude()));
        node.setOutlineThickness(0.00002);
        node.setSize(0.0001);
        node.setColor(GraphViewer::BLACK);
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

    gv.setEnabledNodes(false); // Disable node drawing
    gv.setEnabledEdgesText(false); // Disable edge text drawing
    gv.setZipEdges(true);
    gv.createWindow(1600, 900);
    gv.join();
}

template <class T>
void Gui<T>::graphViewerWithPath(const T &origin, const T &dest){
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

    std::vector<T> path = graph->getPath(origin, dest);
    for (auto &info : path) {
        Edge_Viewer &edge = gv.getEdge(info);
        edge.setColor(GraphViewer::BLUE);
    }

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
