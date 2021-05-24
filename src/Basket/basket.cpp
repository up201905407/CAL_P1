#include "basket.h"


Basket::Basket(std::string clientName, unsigned int numPack, unsigned long idDest, unsigned long numFat){
    this->clientName = clientName;
    this->numPack = numPack;
    this->idDest = idDest;
    this->numFat = numFat;
}

void Basket::setClientName(std::string clientName){
    this->clientName = clientName;
}

std::string Basket::getClientName(){
    return clientName;
}

void Basket::setNumPack(unsigned int numPack){
    this->numPack = numPack;
}

unsigned int Basket::getNumPack(){
    return numPack;
}

void Basket::setIdDest(unsigned long idDest){
    this->idDest = idDest;
}

unsigned long Basket::getIdDest(){
    return idDest;
}

void Basket::setNumFat(unsigned long int numFat){
    this->numFat = numFat;
}

unsigned long Basket::getNumFat(){
    return numFat;
}