#include "banners.h"
#include "controller.h"
#include "user.h"
#include "owner.h"
#include "employee.h"
#include "patron.h"
#include "item.h"
#include "fiction.h"
#include "nonfiction.h"
#include "scanner.h"
#include "search.h"
#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <utility>
#include <algorithm>
#include <vector>

void Employee::createAccount() {
   Controller controller;
   std::string patronName;
   std::string verification;
   std::string fileContents;
   std::ifstream instream;
   std::ofstream outStream;
   int ID;
   std::string IDString;
   std::string identification = "1";
   std::ostringstream convert;
   int index;
   std::string insert;


   std::cout << "What is the Patron's name? ";
   std::cin.ignore(10, '\n');
   std::getline(std::cin, patronName);
   std::cout << "The Patron's name is " << patronName << "... is that right?\n";
   std::cout << "Enter yes or no: ";
   std::cin >> verification;
   std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
   while (verification != "yes" && verification != "no") {
      std::cout << "\nI'm sorry... I didn't understand you...\n";
      std::cout << "The Patron's name is " << patronName << "... is that right?\n";
      std::cout << "Enter yes or no: ";
      std::cin >> verification;
      std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
   };
   while (verification == "no") {
      std::cout << "\nOh, okay... did you want to continue adding a patron?\n";
      std::cout << "Enter yes or no: ";
      std::cin >> verification;
      std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
      if (verification == "no") {
         return;
      };
      std::cout << "What is the Patron's name then? ";
      std::cin.ignore(10, '\n');
      std::getline(std::cin, patronName);
      std::cout << "The Patron's name is " << patronName << "... is that right?\n";
      std::cout << "Enter yes or no: ";
      std::cin >> verification;
      std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
      while (verification != "yes" && verification != "no") {
         std::cout << "\nI'm sorry... I didn't understand you...\n";
         std::cout << "Patron's name is " << patronName << "... is that right?\n";
         std::cout << "Enter yes or no: ";
         std::cin >> verification;
         std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
      };
   };
   instream.open("users.txt");
   if (instream.fail()) {
      std::cerr << "instream.open failed... ermahgerd!\n";
      return;
   };
   std::getline(instream, fileContents);
   instream.close();
   ID = controller.RNG();
   convert << ID;
   IDString = convert.str();
   index = fileContents.find(IDString);
   while (!(index < 0)) {          // Check for duplicity
      ID = controller.RNG();
      convert << ID;
      IDString = convert.str();
      index = fileContents.find(IDString);
   };
   identification += IDString;
   std::cout << "The Patron's User ID is " << identification << "\nPlease write it down as they will need it to log in.\n";
   insert = fileContents + identification + ":" + patronName + ":A:0.00|";
   outStream.open("users.txt");
   outStream << insert;
   outStream.close();

   return;
};

void Employee::freezeAccount() {
   Banners banner;
   std::string freezeID;
   std::cout << "Please enter the userID of the account you would like to freeze: ";
   std::cin >> freezeID;
   std::cin.ignore(10, '\n');
   
   std::ifstream instream;
   std::string fileContents;
   instream.open("users.txt");
   if (instream.fail()) {
      std::cout << "instream.open failed... ehrmahgerd!\n";
      return;
   };
   
   std::getline(instream, fileContents);
   instream.close();
   int IDLoc = fileContents.find(freezeID);
   while (IDLoc < 0) {
      banner.failure("Not a valid userID!");
      std::cout << "Please enter a valid userID: ";
      std::cin >> freezeID;
      std::cin.ignore(10, '\n');
      IDLoc = fileContents.find(freezeID);
   };
   if (freezeID.substr(0,1) == "3") {
      banner.failure("Employees cannot freeze Owners' account!");
      return;
   }
   int statusLoc = fileContents.find(":", IDLoc + 10);
   std::string status = fileContents.substr(statusLoc + 1 , 1);
   
   if (banner.confirm("freeze " + freezeID + "'s account...")) {
      if (status == "A") {
         changeStatus(statusLoc, fileContents, "F");
         std::cout << freezeID << "'s account is now frozen.\n";
      }
      else
      {
         std::cout << "The account is already frozen.\n";
      };
   };
   return;
};

void Employee::changeStatus(int statusLoc, std::string fileContents, std::string newStatus) {
   std::ofstream outstream;
   
   outstream.open("users.txt");
   if (outstream.fail()) {
      std::cout << "outstream.open failed... ehrmahgerd!\n";
   };
   
   outstream << fileContents.substr(0, statusLoc + 1) << newStatus << fileContents.substr(statusLoc + 2);
   outstream.close();
      
   return;
};
