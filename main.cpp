/******************************************************************************

Name of the Module: 04 Assign Hot Dog Stands
Date Written: 03/31/2025
Author: Hazel White
Program Purpose: This is a program that handles the business transactions 
and tracks the activities of all your hotdog stands.

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

#include "HotDogStandsClass.h"
#include "TransactionsClass.h"

using namespace std;

const string   HOTDOG_STANDS_FILE_NAME_STR = "InfoHotDogStands.txt";
const string   TRANSACTIONS_FILE_NAME_STR  = "InfoHotDogStandsTransactions.txt";
const string   GLOBAL_SOLD__FILE_NAME_STR  = "InfoGlobalSold.txt";

//Overloaded stream insertion operator prototypes:
ostream& operator<<(ostream& leftSideOutputStream, const HotDogStandsClass& hotDogStandObj);
ostream& operator<<(ostream& leftSideOutputStream, const TransactionsClass& transactionsObj);

//Prototypes:
void CheckFileStreamOpen(string globalSoldFileNameStr, ifstream& inFile);

void ReadInFromGlobalSoldFile(string globalSoldFileNameStr);
void ReadInFromHotDogStandsFileTo(string hotDogStandsFileNameStr, HotDogStandsClass*& hotDogStandsAry, unsigned& standsLineCount);
void ReadInFromTransactionsFileTo(string transactionsFileNameStr, TransactionsClass*& transactionsAry, unsigned& transactionsLineCount);

void displayStands(HotDogStandsClass* hotDogStandsAry, unsigned totalNoHotDogStandsUns);

unsigned getMatchingHotDogStandIndexUns(HotDogStandsClass* hotDogStandsAry, unsigned totalNoHotDogStandsUns, TransactionsClass* transactionsAry, unsigned transactonsNoUns);

void processTransactions(HotDogStandsClass*& hotDogStandsAry, unsigned totalNoHotDogStandsUns, TransactionsClass* transactionsAry, unsigned totalNoTransactonsUns);

void UpdateHotDogStandsFile(string hotDogStandsFileNameStr, HotDogStandsClass* hotDogStandsAry, unsigned totalNoHotDogStandsUns);
void UpdateGlobalSoldFile(string globalSoldFileNameStr);


int main() {
    cout << setprecision(2) << fixed << showpoint;

    //Dynamically allocated arrays for storing hot dog stands and transactions
    HotDogStandsClass* hotDogStandsAry = nullptr;
    unsigned          hotDogStandsCountUns;
    TransactionsClass* transactionsAry = nullptr;
    unsigned          transactonsCountUns;
    
    //Reading from the 3 .txt files:
    ReadInFromGlobalSoldFile(GLOBAL_SOLD__FILE_NAME_STR);
    ReadInFromHotDogStandsFileTo(HOTDOG_STANDS_FILE_NAME_STR, hotDogStandsAry, hotDogStandsCountUns);
    ReadInFromTransactionsFileTo(TRANSACTIONS_FILE_NAME_STR, transactionsAry, transactonsCountUns);

    cout << "Initial states of stands:" << endl;
    cout << "=========================" << endl << endl;
    displayStands(hotDogStandsAry, hotDogStandsCountUns);

    cout << "Process Transactions:" << endl;
    cout << "=====================" << endl << endl;
    processTransactions(hotDogStandsAry, hotDogStandsCountUns, transactionsAry, transactonsCountUns);

    cout << "Final states of stands:" << endl;
    cout << "=======================" << endl << endl;
    displayStands(hotDogStandsAry, hotDogStandsCountUns);

    //The following 2 files are beging updated with current information before the program ends: 
    UpdateHotDogStandsFile(HOTDOG_STANDS_FILE_NAME_STR, hotDogStandsAry, hotDogStandsCountUns);
    UpdateGlobalSoldFile(GLOBAL_SOLD__FILE_NAME_STR);

    cout << "Please press enter key once or twice to end..."; cin.ignore(); cin.get();
    
    // Clean up dynamically allocated memory to prevent memory leaks
    delete[] hotDogStandsAry;
    delete[] transactionsAry;
    
    exit(EXIT_SUCCESS);
}


// Overloaded << operator for HotDogStandsClass
ostream& operator<<(ostream& leftSideOutputStream, const HotDogStandsClass& hotDogStandObj) {
    cout << "Stand ID: " << hotDogStandObj.getIdStr() << endl;
    cout << "Address: " << hotDogStandObj.getAddressStr() << endl;
    cout << "Price: $" << hotDogStandObj.getPriceFl() << endl;
    cout << "Inventory: " << hotDogStandObj.getInventoryAmountUns() << " hotdogs" << endl;
    cout << "Store Sold: " << hotDogStandObj.getSoldAmountUns() << " at $" << hotDogStandObj.getPriceFl() << " ea." << endl;
    return leftSideOutputStream;
}

// Overloaded << operator for TransactionsClass
ostream& operator<<(ostream& leftSideOutputStream, const TransactionsClass& transactionsObj) {
    cout << "Stand ID: " << transactionsObj.getIdentifcationStr() << endl;
    cout << "Transaction Type: " << transactionsObj.getTransactionIdStr() << endl;
    cout << "Transaction Quantity: " << transactionsObj.getTransactionArgumentUns() << endl;
    return leftSideOutputStream;
}


//Functions Interacting with the 3 .txt files/file content:-------------------------------------------------------------------------------

//Function to check if a file opened successfully
void CheckFileStreamOpen(string globalSoldFileNameStr, ifstream &inFile) {
  if (inFile.fail()) {
    cout << "File " << globalSoldFileNameStr << "could not be opened !" << endl;
    cout << endl << "Press the enter key once or twice to continue..." << endl; cin.ignore(); cin.get();
    exit(EXIT_FAILURE);
  }
}

//Reads the global sold count from file
void ReadInFromGlobalSoldFile(string globalSoldFileNameStr) {
  ifstream inFile(globalSoldFileNameStr);
  CheckFileStreamOpen(globalSoldFileNameStr, inFile);
  inFile >> HotDogStandsClass::globalSoldCountUns;
  inFile.close();
}

//Reads hot dog stand data from file
void ReadInFromHotDogStandsFileTo(string hotDogStandsFileNameStr, HotDogStandsClass*& hotDogStandsAry, unsigned& hotDogStandsCountUns) {
  ifstream inFile(hotDogStandsFileNameStr);
  CheckFileStreamOpen(hotDogStandsFileNameStr, inFile);

  string lineInFileBufferStr;

  //Count the number of lines in the file
  hotDogStandsCountUns = 0;
  while (getline(inFile, lineInFileBufferStr))
    ++hotDogStandsCountUns;

  hotDogStandsAry = new HotDogStandsClass[hotDogStandsCountUns];

  inFile.clear(); inFile.seekg(0, ios::beg);
  string inputStr;
  constexpr char COMMA_DELIMTER_CHAR = ',';

  //for each line read from the file
  for (unsigned lineCount = 0; lineCount < hotDogStandsCountUns; ++lineCount) {
    getline(inFile, lineInFileBufferStr);
    istringstream isStringStream(lineInFileBufferStr);

    //read everything up to the comma delimeter
    getline(isStringStream, inputStr, COMMA_DELIMTER_CHAR);
    hotDogStandsAry[lineCount].setIdStr(inputStr);

    //read Address
    getline(isStringStream, inputStr, COMMA_DELIMTER_CHAR);
    hotDogStandsAry[lineCount].setAddressStr(inputStr);

    //read Hotdog Price
    getline(isStringStream, inputStr, COMMA_DELIMTER_CHAR);
    hotDogStandsAry[lineCount].setPriceFl(stof(inputStr));

    //read Inventory
    getline(isStringStream, inputStr, COMMA_DELIMTER_CHAR);
    hotDogStandsAry[lineCount].setInventoryAmountUns(static_cast<unsigned>(stoul(inputStr)));
    
    
    //read Sold Amount of Hotdogs
    getline(isStringStream, inputStr, COMMA_DELIMTER_CHAR);
    hotDogStandsAry[lineCount].setSoldAmountUns(static_cast<unsigned>(stoul(inputStr)));
    
    
  }
  inFile.close();
}

//Reads transactions from file
void ReadInFromTransactionsFileTo(string transactionsFileNameStr, TransactionsClass*& transactionsAry, unsigned& transactionsLineCount) {

  ifstream inFile(transactionsFileNameStr);
  CheckFileStreamOpen(transactionsFileNameStr, inFile);

  string lineInFileBufferStr;

  //Count the number of lines in the transactions file
  transactionsLineCount = 0;
  while (getline(inFile, lineInFileBufferStr))
    ++transactionsLineCount;

  transactionsAry = new TransactionsClass[transactionsLineCount];

  inFile.clear(); inFile.seekg(0, ios::beg);
  string inputStr;
  constexpr char COMMA_DELIMTER_CHAR = ',';

  for (unsigned lineCount = 0; lineCount < transactionsLineCount; ++lineCount) {
    getline(inFile, lineInFileBufferStr);
    istringstream isStringStream(lineInFileBufferStr);

    //read Stand Identification
    getline(isStringStream, inputStr, COMMA_DELIMTER_CHAR);
    transactionsAry[lineCount].setIdentifcationStr(inputStr);

    //read Transaction ID
    getline(isStringStream, inputStr, COMMA_DELIMTER_CHAR);
    transactionsAry[lineCount].setTransactionIdStr(inputStr);

    //read Transaction Argument
    getline(isStringStream, inputStr, COMMA_DELIMTER_CHAR);
    transactionsAry[lineCount].setTransactionArgumentUns(static_cast<unsigned>(stoul(inputStr)));
    
  }

  inFile.close();
}
//----------------------------------------------------------------------------------------------------------------------------------------

//Displays all information of each hot dog stand and the global sales count
void displayStands(HotDogStandsClass* hotDogStandsAry, unsigned totalNoHotDogStandsUns) {

  for (unsigned index = 0; index < totalNoHotDogStandsUns; ++index) {
    cout << hotDogStandsAry[index] << endl;
  }
  
  cout << endl << "Global Sold : " << HotDogStandsClass::globalSoldCountUns << endl << endl;
  cout << "Please press enter key once or twice to continue..."; cin.ignore(); cin.get();
  cout << endl << endl;
}

//Finds the index of a hot dog stand that matches a given transaction
unsigned getMatchingHotDogStandIndexUns(HotDogStandsClass* hotDogStandsAry, unsigned totalNoHotDogStandsUns, TransactionsClass* transactionsAry, unsigned transactonsCountUns) {    
    for (unsigned seekIndex = 0; seekIndex < totalNoHotDogStandsUns; ++seekIndex)
        if (hotDogStandsAry[seekIndex].getIdStr() == transactionsAry[transactonsCountUns].getIdentifcationStr())
            return(seekIndex);
            
    return totalNoHotDogStandsUns; // Return an invalid index to indicate: no match found
}

//Processes a single transaction and updates/edits the corresponding hot dog stand's information accordingly
void processTransaction(TransactionsClass transactionObj, HotDogStandsClass& hotDogStandObj) {
  if (transactionObj.getTransactionIdStr() == "stock inventory") {
      unsigned stockUns = transactionObj.getTransactionArgumentUns();
      hotDogStandObj.stockInventoryAmountUns(stockUns);
  }
  else if (transactionObj.getTransactionIdStr() == "buy")
  {
      unsigned buyUns = transactionObj.getTransactionArgumentUns();
      hotDogStandObj.hotDogsBuyUns(buyUns);
  }

};

//Processes all transactions and displays the new hot dog stands information
void processTransactions(HotDogStandsClass*& hotDogStandsAry, unsigned totalNoHotDogStandsUns, TransactionsClass* transactionsAry, unsigned transactonsCountUns) {

  for (unsigned transactionNoUns = 0; transactionNoUns < transactonsCountUns; ++transactionNoUns) {
    //Find correct stand
    unsigned hotDogStandIndexUns = getMatchingHotDogStandIndexUns(hotDogStandsAry, totalNoHotDogStandsUns, transactionsAry, transactionNoUns);
    cout << "-----------------------------" << endl << endl;
    cout << "HotDog Stand Current Status :" << endl << endl;
    cout << hotDogStandsAry[hotDogStandIndexUns] << endl;
    cout << "Transaction: " << endl << endl;
    cout << transactionsAry[transactionNoUns] << endl;
    processTransaction(transactionsAry[transactionNoUns], hotDogStandsAry[hotDogStandIndexUns]);
    cout << "HotDog Stand Status After Transaction :" << endl << endl;
    cout << hotDogStandsAry[hotDogStandIndexUns] << endl << endl;
    cout << "Global Sold : " << HotDogStandsClass::globalSoldCountUns << endl << endl;
    cout << "Please press enter key once or twice to continue..."; cin.ignore(); cin.get();
  }
}

//Updates the hot dog stands file with the latest stand data
void UpdateHotDogStandsFile(string   hotDogStandsFileNameStr, HotDogStandsClass* hotDogStandsAry, unsigned totalNoHotDogStandsUns) {
  ofstream outFile(hotDogStandsFileNameStr);

  for (unsigned writeIndex = 0; writeIndex < totalNoHotDogStandsUns; ++writeIndex)
    outFile <<
    hotDogStandsAry[writeIndex].getIdStr()              << "," <<
    hotDogStandsAry[writeIndex].getAddressStr()         << "," <<
    hotDogStandsAry[writeIndex].getPriceFl()            << "," <<
    hotDogStandsAry[writeIndex].getInventoryAmountUns() << "," <<
    hotDogStandsAry[writeIndex].getSoldAmountUns()      << endl;

  outFile.close();
};

//Updates the global sales file with the latest total sales count
void UpdateGlobalSoldFile(string globalSoldFileNameStr) {
  ofstream outFile(globalSoldFileNameStr);
  outFile << HotDogStandsClass::globalSoldCountUns << endl;

};








