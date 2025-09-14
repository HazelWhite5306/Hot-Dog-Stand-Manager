#ifndef TRANSACTIONS_CLASS_CLASS_H
#define TRANSACTIONS_CLASS_CLASS_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class TransactionsClass {

private:
  string   standIdentifcationStr;
  string   transactionIdStr;
  unsigned transactionArgumentUns;

public:

  //Getter Methods
  const string& getIdentifcationStr() const { return standIdentifcationStr; };
  const string& getTransactionIdStr() const { return transactionIdStr;};
  unsigned getTransactionArgumentUns() const {return transactionArgumentUns; };
  
  //Setter Methods
  void setIdentifcationStr(string standIdentifcationStr) {this->standIdentifcationStr = standIdentifcationStr; }
  void setTransactionIdStr(string transactionIdStr) {this->transactionIdStr = transactionIdStr; }
  void setTransactionArgumentUns(unsigned transactionArgumentUns) {this->transactionArgumentUns = transactionArgumentUns; }

};

#endif