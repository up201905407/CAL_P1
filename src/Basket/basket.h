#ifndef _BASKET_H_
#define _BASKET_H_

#include <iostream>


class Basket{
private:
    std::string clientName; /*<Recipient's name*/
    unsigned int numPack; /*<Number of packages*/
    unsigned long int idDest; /*<Target vertex identifier*/
    unsigned long int numFat; /*<Bill number*/
public:
    /**
    * Basket's constructor
    * @param clientName Name of the client to receive the meal
    * @param numPack Number of packages in the basket
    * @param idDest Id of node of destination
    * @param numFat Bill number
    */
    Basket(std::string clientName, unsigned int numPack, unsigned long idDest, unsigned long numFat);
    /**
    * Updates client's name
    * @param clientName Name of the client to receive the meal
    */
    void setClientName(std::string clientName);
    /**
    * returns the name of the client to receive the meal
    * @return Name of the client to receive the meal
    */
    std::string getClientName();
    /**
    * Updates number of packages
    * @param numPack Number of packages in the basket
    */
    void setNumPack(unsigned int numPack);
    /**
    * returns number of packages
    * @return number of packages
    */
    unsigned int getNumPack();
    /**
    * Updates destination's Id
    * @param idDest Destination's Id
    */
    void setIdDest( unsigned long idDest);
    /**
    * returns destination's Id
    * @return destination's Id
    */
    unsigned long getIdDest();
    /**
    * Updates Bill number
    * @param Bill number
    */
    void setNumFat(unsigned long int numFat);
    /**
     * returns Bill number
     * @return Bill number
     */
    unsigned long int getNumFat();
};

#endif //_BASKET_H_
