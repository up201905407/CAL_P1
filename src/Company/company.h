#ifndef _COMPANY_H_
#define _COMPANY_H_

#include "../Vehicle/vehicle.h"

class Company{
private:
    std::vector<Vehicle*> fleet;
    std::vector<Basket*> baskets;
public:
    bool addVehicle(Vehicle* vehicle);
    bool addBasket(Basket* basket);
    Vehicle* findVehicle(unsigned int id);
    Basket* findBasket(unsigned long int numFat);
    bool removeVehicle(unsigned int id);
    bool removeBasket(unsigned long int numFat);
    void distributeBasketsByVehicles();

};

#endif //_COMPANY_H_
