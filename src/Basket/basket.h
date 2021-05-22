#ifndef _BASKET_H_
#define _BASKET_H_

#include <iostream>

class Basket{
private:
    std::string clientName; /*<Recipient's name*/
    unsigned int numPack; /*<Number of packages*/
    unsigned long int idDest; /*<Target vertex identifier*/
    unsigned long int numFat; /*<Bill number*/
    double dist; /*<Value used when calculating routes*/
public:
    Basket(std::string clientName, unsigned int numPack, unsigned long idDest, unsigned long numFat);
    void setClientName(std::string clientName);
    std::string getClientName();
    void setNumPack(unsigned int numPack);
    unsigned int getNumPack();
    void setIdDest(unsigned long int idDest);
    unsigned long getIdDest();
    void setNumFat(unsigned long int numFat);
    unsigned long int getNumFat();
    void setDist(double dist);
    double getDist();
};

#endif //_BASKET_H_
