#ifndef _CLARKEWRIGHT_H_
#define _CLARKEWRIGHT_H_

#include "../Graph/Graph.h"
#include "../Company/company.h"
#include "../Utils/utils.h"
#include <vector>
#include <iterator>


/**
 *
 * Struct which represents the savings from Clarke and Wright
 * in->Inicial point
 * target->Final point
 * saved-> Saved cost
 */
template<typename T>
struct saving{
    T in;
    T target;
    double saved;
};

/**
 * Struct that represents vehicle path
 * begin-> Path's beginning
 * end-> Path's ending
 * path-> Path
 */
template<typename T>
struct road{
    T begin;
    T end;
    std::vector<T> path;
};

/**
 *Clark and Wright Algorithm
 */
template<class T>
class ClarkeWright {
private:
    /**
     * Stores the costs between two main vertexes
     */
    double costs[50][50];
    //1º vertex needs to be depot
    /**
     * Demand points
     */
    std::vector<Vertex<T>*> vertexes;
    Graph<T> *graph;
    Company* company;

    /**
     * Vector of savings
     */
    std::vector<saving<T>> savings;

    /**
     *Creates the vector of demand points from their infos on baskets
     */
    void createVertexes();
    /**
     * Creates the matrix which contains all the costs between two points
     */
    void getCostsMatrix();
    /**
     * Creatas the savings vector from the costs' matrix
     */
    void getSavingsFromMatrix();
    /**
     * Sorts the saving vector in descending order
     */
    void sortSavings();

public:
    /**
     * Contructor of this class
     * @param graph Graph of the main city
     * @param company Company PapaRicos
     */
    ClarkeWright(Graph<T> *graph, Company* company);
    /**
     * Function that executes the Clarke and Wright algortithm with some restrictions
     * @return true if it worked out and false if all the baskets can´t be delivered
     */
    bool clarkeWight();
};

template<class T>
ClarkeWright<T>::ClarkeWright(Graph<T> *graph,Company *company) {
    this->graph = graph;
    this->company = company;
}

template<class T>
void ClarkeWright<T>::createVertexes() {
    this->vertexes.clear();
    this->vertexes.push_back(graph->findVertex(this->company->getDepotInfo()));
    for(Basket* basket: this->company->getBaskets())
    {
        this->vertexes.push_back(graph->findVertex(basket->getIdDest()));
    }
}

template<class T>
void ClarkeWright<T>::getCostsMatrix() {


    for(int i = 0; i < this->vertexes.size() -1; i++){
        for(int j = 0; j<this->vertexes.size()-1; j++){
            if(i <= j) this->costs[j][i] = 0.0;
            else{
                costs[j][i] = haversine(vertexes[i]->getLatitude(),vertexes[i]->getLongitude(),vertexes[j]->getLatitude(),vertexes[j]->getLongitude());
            }
        }
    }

}
template<class T>
void ClarkeWright<T>::getSavingsFromMatrix() {
    this->savings.clear();
    saving<unsigned long> saved;

    for(int i = 1; i<vertexes.size()-1; i++){
        for(int j = i+1; j<vertexes.size(); j++){
            saved.in = vertexes[i]->getInfo();
            saved.target = vertexes[j]->getInfo();
            saved.saved = costs[0][i] + costs[0][j] - costs[i][j];

            savings.push_back(saved);
        }
    }
}

template<class T>
void ClarkeWright<T>::sortSavings() {
    std::sort(savings.begin(), savings.end(),[](saving<T> &saving1, saving<T> &saving2){return saving1.saved > saving2.saved;});
}

//Limitação 1 : Não podem haver dois cabazes no mesmo vértice
//Limitação 2 : Não consegue dar refill no meio da entrega
template<class T>
bool ClarkeWright<T>::clarkeWight() {
    this->createVertexes();
    this->getCostsMatrix();
    this->getSavingsFromMatrix();
    this->sortSavings();
    road<unsigned long > road;

    int sizeOfVehicles = this->company->getFleet().size();
    int counter = 0;


    //Enquanto houver baskets, vai ao primeiro camião disponível e adiciona um produto, se conseguir
    while(!this->company->getBaskets().empty()){
        if(sizeOfVehicles == counter){return false;}

        if( this->company->getFleet().at(counter)->getMaxCap() == this->company->getFleet().at(counter)->getCurrentLoad()){
            //Adicionar no final o depot no inicio e fim
            road.path.insert(road.path.begin(),this->company->getDepotInfo());
            road.path.insert(road.path.end(),this->company->getDepotInfo());
            this->company->getFleet().at(counter)->setPathList(road.path);
            counter++;

            continue;
        }

        road.path.clear();
        road.end = 0;
        road.begin = 0;

        auto i= savings.begin();

        if(this->company->getBaskets().size()==1 && this->company->getFleet().at(counter)->getCurrentLoad()+this->company->getBaskets().at(0)->getNumPack()<=this->company->getFleet().at(counter)->getMaxCap()){
            road.path = {this->company->getDepotInfo(),this->company->getBaskets().at(0)->getIdDest(),this->company->getDepotInfo()};
            this->company->setBaskets({});
            this->company->getFleet().at(counter)->setPathList(road.path);
            return true;
        }

        for(i = savings.begin(); i!=savings.end(); i++){
            bool inInPath = false;
            bool targInPath = false;


            if(road.begin == i->in || road.end == i->in) inInPath = true;
            if(road.begin == i->target || road.end == i->target) targInPath = true;

            //Caso nenhum dos vértices esteja no path
            if(!(inInPath || targInPath)){
                //Se os dois vértices forem o mesmo
                /*
                if(i->in == i->target){
                    //se ambos os pedidos não caberem no camião
                    if(vehicle->getCurrentLoad() + this->company->findBasketByDest(i->in) + this->company->findBasketByDest(i->target)> vehicle->getMaxCap() )
                    {
                        //se não couber nenhum dos dois
                        if(vehicle->getCurrentLoad() + this->company->findBasketByDest(i->in)>0 && vehicle->getCurrentLoad() + this->company->findBasketByDest(i->target)>0){
                            continue;
                        }
                        else{ //se couber apenas o inicial
                            if(vehicle->getCurrentLoad() + this->company->findBasketByDest(i->in)<=0){
                                vehicle->setCurrentLoad(vehicle->getCurrentLoad()+this->company->findBasketByDest(i->in));
                                vehicle->addBasket(this->company->findBasketByDest(i->in));
                                this->company->removeBasket(this->company->findBasketByDest(i->in)->getNumFat());
                                //escrever o path no veiculo *Adiciona um vértice*
                                this->savings.erase(i);
                                i =savings.begin();
                            }else{
                                vehicle->setCurrentLoad(vehicle->getCurrentLoad()+this->company->findBasketByDest(i->target));
                                vehicle->addBasket(this->company->findBasketByDest(i->target));
                                this->company->removeBasket(this->company->findBasketByDest(i->target)->getNumFat());
                                //escrever o path no veiculo *Adiciona um vértice*
                                this->savings.erase(i);
                                i =savings.begin();
                            }
                            if(vehicle->getCurrentLoad() == vehicle->getMaxCap()) break;
                        }

                    }
                    //Cabem os dois no camião
                    else{
                        vehicle->setCurrentLoad(vehicle->getCurrentLoad()+this->company->findBasketByDest(i->in) + this->company->findBasketByDest(i->target));
                        vehicle->addBasket(this->company->findBasketByDest(i->in));
                        this->company->removeBasket(this->company->findBasketByDest(i->in)->getNumFat());
                        vehicle->addBasket(this->company->findBasketByDest(i->target));
                        this->company->removeBasket(this->company->findBasketByDest(i->in)->getNumFat());
                        //*escrever o path no veiculo* Adiciona um vértice*
                        this->savings.erase(i);
                        i =savings.begin();
                    }

                    if(vehicle->getCurrentLoad() == vehicle->getMaxCap()) break;

                }
                 */
                //Os dois vértices não são o mesmo
                //Se já existirem pontos de rota, ao não coicidir iriamos fazer outro caminho
                if(!(this->company->findBasketByDest(i->in) != nullptr && this->company->findBasketByDest(i->target)!= nullptr)){
                    savings.erase(i);
                    i = savings.begin();
                    continue;
                }

                if(!road.path.empty()) continue;
                if((this->company->getFleet().at(counter)->getCurrentLoad() + this->company->findBasketByDest(i->in)->getNumPack() + this->company->findBasketByDest(i->target)->getNumPack() )> this->company->getFleet().at(counter)->getMaxCap() ) continue;

                this->company->getFleet().at(counter)->setCurrentLoad(this->company->getFleet().at(counter)->getCurrentLoad()+this->company->findBasketByDest(i->in)->getNumPack() + this->company->findBasketByDest(i->target)->getNumPack());
                this->company->getFleet().at(counter)->addBasket(this->company->findBasketByDest(i->in));
                this->company->removeBasket(this->company->findBasketByDest(i->in)->getNumFat());
                this->company->getFleet().at(counter)->addBasket(this->company->findBasketByDest(i->target));
                this->company->removeBasket(this->company->findBasketByDest(i->target)->getNumFat());
                //*escrever o path no veiculo *Adiciona dois vértices*
                road.begin = i->in;
                road.end = i->target;
                road.path.push_back(road.begin);
                road.path.push_back(road.end);

                this->savings.erase(i);
                i =savings.begin();

                if(this->company->getFleet().at(counter)->getCurrentLoad() == this->company->getFleet().at(counter)->getMaxCap()) break;
            }
            //Apenas está registado o lado in

            else if(inInPath){
                if(this->company->findBasketByDest(i->target)->getIdDest()==0){
                    savings.erase(i);
                    i = savings.begin();
                    continue;
                }

                if(this->company->getFleet().at(counter)->getCurrentLoad() +  this->company->findBasketByDest(i->target)->getNumPack() > this->company->getFleet().at(counter)->getMaxCap() ) continue;
                this->company->getFleet().at(counter)->setCurrentLoad(this->company->getFleet().at(counter)->getCurrentLoad()+this->company->findBasketByDest(i->target)->getNumPack());
                this->company->getFleet().at(counter)->addBasket(this->company->findBasketByDest(i->target));
                this->company->removeBasket(this->company->findBasketByDest(i->target)->getNumFat());
                //escrever o path no veiculo *Adiciona um vértice*
                if(i->in == road.begin){
                    road.begin = i->target;
                    road.path.insert(road.path.begin(),road.begin);
            }else if(i->in == road.end){
                    road.end = i->target;
                    road.path.push_back(road.end);
                }

                this->savings.erase(i);
                i =savings.begin();
                if(this->company->getFleet().at(counter)->getCurrentLoad() == this->company->getFleet().at(counter)->getMaxCap()) break;
            }
            //Apenas está registado o lado target
            else if(targInPath){
                if(this->company->findBasketByDest(i->in)->getIdDest()==0){
                    savings.erase(i);
                    i = savings.begin();
                    continue;
                }

                if((this->company->getFleet().at(counter)->getCurrentLoad() + this->company->findBasketByDest(i->in)->getNumPack()) > this->company->getFleet().at(counter)->getMaxCap() ) continue;
                this->company->getFleet().at(counter)->setCurrentLoad(this->company->getFleet().at(counter)->getCurrentLoad()+this->company->findBasketByDest(i->in)->getNumPack());
                this->company->getFleet().at(counter)->addBasket(this->company->findBasketByDest(i->in));
                this->company->removeBasket(this->company->findBasketByDest(i->in)->getNumFat());
                //escrever o path no veiculo *Adiciona um vértice*
                if(i->target == road.begin){
                    road.begin = i->in;
                    road.path.insert(road.path.begin(),road.begin);
                }else if(i->target == road.end){
                    road.end = i->in;
                    road.path.push_back(road.end);
                }
                this->savings.erase(i);
                i =savings.begin();
                if(this->company->getFleet().at(counter)->getCurrentLoad() == this->company->getFleet().at(counter)->getMaxCap()) break;
            }
            else if(targInPath && inInPath) continue;

        }

        if(i == savings.end()){
            road.path.insert(road.path.begin(),this->company->getDepotInfo());
            road.path.insert(road.path.end(),this->company->getDepotInfo());
            this->company->getFleet().at(counter)->setPathList(road.path);
            counter++;
            continue;
        }

    }

    return true;


}






#endif //_CLARKEWRIGHT_H_
