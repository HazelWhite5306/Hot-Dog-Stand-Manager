#ifndef HOTDOG_STAND_CLASS_CPP
#define HOTDOG_STAND_CLASS_CPP

#include "HotDogStandsClass.h"

using namespace std;

unsigned HotDogStandsClass::globalSoldCountUns = 0;

/*Handles the purchases of hot dogs by reducing inventory and increasing sales, 
or notifying if a sale cannot be made due to: not enough inventory or no more hot dogs*/ 
void HotDogStandsClass::hotDogsBuyUns(unsigned count) {
    if (count > inventoryAmountUns && inventoryAmountUns == 0) {
        cout << "*Sorry, there are no more hotdogs left to be sold*\n" << endl;
    } else if (count > inventoryAmountUns) {
        cout << "*Sorry, we only have " << inventoryAmountUns <<" hotdogs left.*\n" << endl;
    }else {
        inventoryAmountUns -= count;
        soldAmountUns += count;
        globalSoldCountUns += count;
    }
}

#endif