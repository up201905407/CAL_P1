#ifndef _COMPANY_H_
#define _COMPANY_H_

#include "../Vehicle/vehicle.h"

class Company{
private:
    double latitude;
    double longitude;
    std::vector<Vehicle*> fleet;
    std::vector<Basket*> baskets;
public:
    Company(double latitude, double longitude);
    double getLatitude();
    double getLongitude();
    bool addVehicle(Vehicle* vehicle);
    bool addBasket(Basket* basket);
    std::vector<Vehicle*> getFleet();
    Vehicle* findVehicle(unsigned int id);
    Basket* findBasket(unsigned long int numFat);
    bool removeVehicle(unsigned int id);
    bool removeBasket(unsigned long int numFat);
    bool distributeBasketsByVehicles();

};

#endif //_COMPANY_H_
