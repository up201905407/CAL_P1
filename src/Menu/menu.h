#ifndef _MENU_H_
#define _MENU_H_

#include "../Company/company.h"
#include "../Gui/gui.h"
#include "../Graph/Graph.h"

class Menu {
public:
    /**
    * Menu's constructor
    * @param company Company to be used
    * @param graph Graph to be used
    * @param gui Interface to be used
    */
    Menu(Company *company, Graph<unsigned long int> *graph, Gui<unsigned long int> *gui);
    /**
    * initializes the menu, showing the available options
    */
    void init();

private:
    Graph<unsigned long int>* graph;
    Company *company;
    Gui<unsigned long> *gui;
    /**
    * Main menu for accessing available data
    */
    void viewMenu();
    /**
    * Menu for accessing vehicles' informations
    */
    void viewFleet();
    /**
    * Menu for accessing baskets' informations
    */
    void viewBaskets();
    /**
    * Main menu for data insertion
    */
    void dataMenu();
    /**
    * Main menu for connectivity informations
    */
    void connectivityMenu();
    /**
    * Main menu for results
    */
    void resultsMenu();
    /**
    * Menu for vehicle's insertion
    */
    void createVehicle();
    /**
    * Menu for basket's insertion
    */
    void createBasket();
    /**
    * Menu for vehicle's deletion
    */
    void deleteVehicle();
    /**
    * Menu for basket's deletion
    */
    void deleteBasket();
};


#endif //_MENU_H_
