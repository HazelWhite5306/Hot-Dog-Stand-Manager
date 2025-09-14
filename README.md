# Hot Dog Stand Manager

## 📌 Overview
This program simulates and manages hot dog stand operations, including business transactions, inventory tracking, and global sales. It processes data from text files, applies transactions, updates records, and outputs both the initial and final states of all stands.

---

## 🛠 Features
- Reads stand information, transactions, and global sales from external text files.
- Tracks **inventory, pricing, and per-stand sales**.
- Processes multiple types of transactions:
  - Restocking inventory
  - Selling hot dogs
- Updates stand files and global sales files automatically.
- Displays before-and-after states of stands for each transaction.
- Uses **operator overloading (`<<`)** for clean output formatting.

---

## 📂 File Structure
- `main.cpp` → Program driver (business logic + file handling)  
- `HotDogStandsClass.h / .cpp` → Class representing hot dog stands  
- `TransactionsClass.h / .cpp` → Class representing transactions  
- `InfoHotDogStands.txt` → Input file containing hot dog stand data  
- `InfoHotDogStandsTransactions.txt` → Input file containing transactions  
- `InfoGlobalSold.txt` → Tracks total global sales across all stands  

---

## 🚀 How to Run
1. Clone this repository:  
   ```bash
   git clone https://github.com/<your-username>/hotdog-stand-manager.git
   cd hotdog-stand-manager

---

## Credits
- Developed by Hazel White
- Course Project and template under the guidance of Professor Scott Michael Dollinger
- University of Texas at Dallas – Computer Engineering
