#ifndef _MENU_H_
#define _MENU_H_

#include "../Company/company.h"
#include "../Gui/gui.h"
#include "../Graph/Graph.h"

class Menu {
public:
    Menu(Company *company, Graph<unsigned long int> *graph);
    void init();

private:
    Graph<unsigned long int>* graph;
    Company *company;
    Gui<unsigned long> gui = nullptr;
    void dataMenu();
    void connectivityMenu();
    void resultsMenu();
    void createVehicle();
    void createBasket();
    void deleteVehicle();
    void deleteBasket();
};


#endif //_MENU_H_
