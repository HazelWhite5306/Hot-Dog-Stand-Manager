#ifndef HOTDOG_STAND_CLASS_H
#define HOTDOG_STAND_CLASS_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class HotDogStandsClass {

private:
  string   identificationStr,
           addressStr;
           
  float    hotdogPriceFl;
  
  unsigned inventoryAmountUns,
           soldAmountUns;

public:
  // Default Constructor
  HotDogStandsClass() : identificationStr(""), addressStr(""), hotdogPriceFl(0.0), inventoryAmountUns(0), soldAmountUns(0) {}
    
  HotDogStandsClass(string identificationStr, string addressStr, double hotdogPriceFl, int inventoryAmountUns, int soldAmountUns) {
    this->identificationStr = identificationStr;
    this->addressStr = addressStr;
    this->hotdogPriceFl = hotdogPriceFl;
    this->inventoryAmountUns = inventoryAmountUns;
    this->soldAmountUns = soldAmountUns;
  }

  static unsigned globalSoldCountUns;
  
  //Getter Methods: 
  const string& getIdStr() const { return identificationStr; };
  const string& getAddressStr() const { return addressStr; };
  float getPriceFl() const { return hotdogPriceFl; };
  unsigned getSoldAmountUns() const { return soldAmountUns; };
  unsigned getInventoryAmountUns() const { return inventoryAmountUns; };
  
  //Setter Methods:
  void setIdStr(const string& identificationStr) {this->identificationStr = identificationStr; }
  void setAddressStr(const string& addressStr) {this->addressStr = addressStr; }
  void setPriceFl(float hotdogPriceFl) {this->hotdogPriceFl = hotdogPriceFl; }
  void setSoldAmountUns(unsigned soldAmountUns) {this->soldAmountUns = soldAmountUns; }
  void setInventoryAmountUns(unsigned inventoryAmountUns) {this->inventoryAmountUns = inventoryAmountUns; }
  
  //Other Methods: 
  void stockInventoryAmountUns(unsigned stockCountUns) {
      inventoryAmountUns += stockCountUns;//Adds stock to the inventory of the hot dog stand
  }
  void hotDogsBuyUns(unsigned count);//prototype (function in HotDogStandsClass.cpp file)

};

#endif