#ifndef _MENU_H_
#define _MENU_H_

#include "../Company/company.h"

class Menu {
public:
    Menu(Company *company);
    void init();

private:
    Company *company;
    void insertionMenu();
    void resultsMenu();
    void createVehicle();
    void createBasket();
};


#endif //_MENU_H_
