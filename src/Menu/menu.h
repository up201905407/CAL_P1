#ifndef _MENU_H_
#define _MENU_H_

#include "../Company/company.h"


class Menu {
public:
    Menu(Company *company);
    void init();

private:
    Company *company;
    void dataMenu();
    void resultsMenu();
    void createVehicle();
    void createBasket();
    void deleteVehicle();
    void deleteBasket();
};


#endif //_MENU_H_
