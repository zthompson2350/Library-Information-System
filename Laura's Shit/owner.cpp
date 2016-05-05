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

void Owner::createAccount() {
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

void Owner::addEmployee() {
   Controller controller;
   Banners banner;
   std::string employeeName;
   std::string verification;
   std::string fileContents;
   std::ifstream instream;
   std::ofstream outStream;
   int ID;
   std::string IDString;
   std::string identification = "2";
   std::ostringstream convert;
   int index;
   std::string insert;


   std::cout << "What is your Employee's name? ";
   std::cin.ignore(10, '\n');
   std::getline(std::cin, employeeName);
   std::cout << "Your Employee's name is " << employeeName << "... is that right?\n";
   std::cout << "Enter yes or no: ";
   std::cin >> verification;
   std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
   while (verification != "yes" && verification != "no") {
      std::cout << "\nI'm sorry... I didn't understand you...\n";
      std::cout << "Your Employee's name is " << employeeName << "... is that right?\n";
      std::cout << "Enter yes or no: ";
      std::cin >> verification;
      std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
   };
   while (verification == "no") {
      std::cout << "\nOh, okay... did you want to continue adding an employee?\n";
      std::cout << "enter yes or no: ";
      std::cin >> verification;
      std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
      if (verification == "no") {
         return;
      };
      std::cout << "What is your Employee's name then? ";
      std::cin.ignore(10, '\n');
      std::getline(std::cin, employeeName);
      std::cout << "your Employee's name is " << employeeName << "... is that right?\n";
      std::cout << "Enter yes or no: ";
      std::cin >> verification;
      std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
      while (verification != "yes" && verification != "no") {
         std::cout << "\nI'm sorry... I didn't understand you...\n";
         std::cout << "Your Employee's name is " << employeeName << "... is that right?\n";
         std::cout << "Enter yes or no: ";
         std::cin >> verification;
         std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
      };
   };
   
   if (banner.confirm("add " + employeeName + " as an Employee")) {
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
      std::cout << "Your Employee's User ID is " << identification << "\nPlease write it down as they will need it to log in.\n";
      insert = fileContents + identification + ":" + employeeName + ":A:0.00|";
      outStream.open("users.txt");
      outStream << insert;
      outStream.close();
   }
   return;
};

void Owner::freezeAccount() {
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
   int statusLoc = fileContents.find(":", IDLoc + 10);
   std::string status = fileContents.substr(statusLoc + 1 , 1);
   int nameLocStart = fileContents.find(":", IDLoc);
   int nameLocEnd = fileContents.find(":", nameLocStart + 1);
   std::string freezeName = fileContents.substr(nameLocStart + 1, nameLocEnd - nameLocStart - 1);
   if (banner.confirm("freeze " + freezeName + "'s account...")) {
      if (status == "A") {
         changeStatus(statusLoc, fileContents, "F");
         std::cout << freezeName << "'s account is now frozen.\n";
      }
      else
      {
         std::cout << "The account is already frozen.\n";
      };
   };
   return;
};

void Owner::changeStatus(int statusLoc, std::string fileContents, std::string newStatus) {
   std::ofstream outstream;
   
   outstream.open("users.txt");
   if (outstream.fail()) {
      std::cout << "outstream.open failed... ehrmahgerd!\n";
   };
   
   outstream << fileContents.substr(0, statusLoc + 1) << newStatus << fileContents.substr(statusLoc + 2);
   outstream.close();
      
   return;
};

void Owner::addItem() {
   Controller controller;
   std::string itemName;
   std::string verification;
   std::string fileContents;
   std::ifstream instream;
   std::ofstream outStream;
   int ID;
   std::string IDString;
   std::string identification;
   std::ostringstream convert;
   int index;
   std::string insert;
   std::string itemType;
   std::string isbn10;
   std::string authorName;


   std::cout << "\nAre you adding a Book (B), Movie (M), or another type of material (O)?\n";
   std::cout << "Enter B, M, or O: ";
   std::cin >> itemType;
   std::transform(itemType.begin(), itemType.end(), itemType.begin(), ::toupper);
   while (itemType != "B" && itemType != "M" && itemType != "O") {
      std::cout << "\nI didn't understand your entry...\n";
      std::cout << "Are you adding a Book (B), Movie (M), or another type of material (O)?\n";
      std::cout << "Enter B, M, or O: ";
      std::cin >> itemType;
      std::transform(itemType.begin(), itemType.end(), itemType.begin(), ::toupper);
   };
   switch (itemType[0]) {
      case 'B':
         identification = "1";
         std::cout << "What is the title of your book? ";
         std::cin.ignore(10, '\n');
         std::getline(std::cin, itemName);
         std::cout << "Your book is called " << itemName << "... is that right?\n";
         std::cout << "Enter yes or no: ";
         std::cin >> verification;
         std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
         while (verification != "yes" && verification != "no") {
            std::cout << "\nI'm sorry... I didn't understand you...\n";
            std::cout << "Your book is called " << itemName << "... is that right?\n";
            std::cout << "Enter yes or no: ";
            std::cin >> verification;
            std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
         };
         while (verification == "no") {
            std::cout << "\nOh, okay... did you want to continue adding a book?\n";
            std::cout << "enter yes or no: ";
            std::cin >> verification;
            std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
            if (verification == "no") {
               return;
            };
            std::cout << "What is your book called then? ";
            std::cin.ignore(10, '\n');
            std::getline(std::cin, itemName);
            std::cout << "your book is called " << itemName << "... is that right?\n";
            std::cout << "Enter yes or no: ";
            std::cin >> verification;
            std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
            while (verification != "yes" && verification != "no") {
               std::cout << "\nI'm sorry... I didn't understand you...\n";
               std::cout << "Your book is called " << itemName << "... is that right?\n";
               std::cout << "Enter yes or no: ";
               std::cin >> verification;
               std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
            };
         };
         break;
      case 'M':
         identification = "2";
         std::cout << "What is the title of your movie? ";
         std::cin.ignore(10, '\n');
         std::getline(std::cin, itemName);
         std::cout << "Your movie is called " << itemName << "... is that right?\n";
         std::cout << "Enter yes or no: ";
         std::cin >> verification;
         std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
         while (verification != "yes" && verification != "no") {
            std::cout << "\nI'm sorry... I didn't understand you...\n";
            std::cout << "Your movie is called " << itemName << "... is that right?\n";
            std::cout << "Enter yes or no: ";
            std::cin >> verification;
            std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
         };
         while (verification == "no") {
            std::cout << "\nOh, okay... did you want to continue adding a movie?\n";
            std::cout << "enter yes or no: ";
            std::cin >> verification;
            std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
            if (verification == "no") {
               return;
            };
            std::cout << "What is your movie called then? ";
            std::cin.ignore(10, '\n');
            std::getline(std::cin, itemName);
            std::cout << "your movie is called " << itemName << "... is that right?\n";
            std::cout << "Enter yes or no: ";
            std::cin >> verification;
            std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
            while (verification != "yes" && verification != "no") {
               std::cout << "\nI'm sorry... I didn't understand you...\n";
               std::cout << "Your movie is called " << itemName << "... is that right?\n";
               std::cout << "Enter yes or no: ";
               std::cin >> verification;
               std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
            };
         };
         break;
      case 'O':
         identification = "3";
         std::cout << "What is the title of your item? ";
         std::cin.ignore(10, '\n');
         std::getline(std::cin, itemName);
         std::cout << "Your item is called " << itemName << "... is that right?\n";
         std::cout << "Enter yes or no: ";
         std::cin >> verification;
         std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
         while (verification != "yes" && verification != "no") {
            std::cout << "\nI'm sorry... I didn't understand you...\n";
            std::cout << "Your item is called " << itemName << "... is that right?\n";
            std::cout << "Enter yes or no: ";
            std::cin >> verification;
            std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
         };
         while (verification == "no") {
            std::cout << "\nOh, okay... did you want to continue adding an item?\n";
            std::cout << "enter yes or no: ";
            std::cin >> verification;
            std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
            if (verification == "no") {
               return;
            };
            std::cout << "What is your item called then? ";
            std::cin.ignore(10, '\n');
            std::getline(std::cin, itemName);
            std::cout << "your item is called " << itemName << "... is that right?\n";
            std::cout << "Enter yes or no: ";
            std::cin >> verification;
            std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
            while (verification != "yes" && verification != "no") {
               std::cout << "\nI'm sorry... I didn't understand you...\n";
               std::cout << "Your item is called " << itemName << "... is that right?\n";
               std::cout << "Enter yes or no: ";
               std::cin >> verification;
               std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
            };
         };
         break;
      default:
         break;
   };
   std::cout << "\nVery good. Now I need the item's isbn10.\n";
   std::cout << "If your item does not have an isbn, just enter ten 0s...\n";
   std::cout << "Enter the item's isbn10: ";
   std::cin >> isbn10;
   while (isbn10.length() != 10) {
      std::cout << "\nThe isbn10 you entered is not 10-digits long\n";
      std::cout << "Enter the item's isbn10: ";
      std::cin >> isbn10;
   };
   if (isbn10 != "0000000000") {
      std::cout << "The isbn10 for " << itemName << " is " << isbn10 << "... is that right?\n";
      std::cout << "Enter yes or no: ";
      std::cin >> verification;
      std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
      while (verification != "yes" && verification != "no") {
         std::cout << "\nI'm sorry... I didn't understand you...\n";
         std::cout << "The isbn10 for " << itemName << " is " << isbn10 << "... is that right?\n";
         std::cout << "Enter yes or no: ";
         std::cin >> verification;
         std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
      };
      while (verification == "no") {
         std::cout << "\nOh, okay... did you want to continue adding " << itemName << "?\n";
         std::cout << "enter yes or no: ";
         std::cin >> verification;
         std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
         if (verification == "no") {
            return;
         };
         std::cout << "What is " << itemName << "'s isbn10 then?\n";
         std::cin.ignore(10, '\n');
         std::cin >> isbn10;
         std::cout << "The isbn10 for " << itemName << " is " << isbn10 << "... is that right?\n";
         std::cout << "Enter yes or no: ";
         std::cin >> verification;
         std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
         while (verification != "yes" && verification != "no") {
            std::cout << "\nI'm sorry... I didn't understand you...\n";
            std::cout << "The isbn10 for " << itemName << " is " << isbn10 << "... is that right?\n";
            std::cout << "Enter yes or no: ";
            std::cin >> verification;
            std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
         };
      };
   };
   std::cout << "\nFantastic! I only need one more thing from you.\n";
   std::cout << "Tell me, who published/directed/created your item? ";
   std::cin.ignore(10, '\n');
   std::getline(std::cin, authorName);


   std::cout << "The creator of your item is " << authorName << "... is that right?\n";
   std::cout << "Enter yes or no: ";
   std::cin >> verification;
   std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
   while (verification != "yes" && verification != "no") {
      std::cout << "\nI'm sorry... I didn't understand you...\n";
      std::cout << "The creator of your item is " << authorName << "... is that right?\n";
      std::cout << "Enter yes or no: ";
      std::cin >> verification;
      std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
   };
   while (verification == "no") {
      std::cout << "\nOh, okay... did you want to continue adding an employee?\n";
      std::cout << "enter yes or no: ";
      std::cin >> verification;
      std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
      if (verification == "no") {
         return;
      };
      std::cout << "What is your item's creator's name then? ";
      std::cin.ignore(10, '\n');
      std::getline(std::cin, authorName);
      std::cout << "The creator of your item is " << authorName << "... is that right?\n";
      std::cout << "Enter yes or no: ";
      std::cin >> verification;
      std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
      while (verification != "yes" && verification != "no") {
         std::cout << "\nI'm sorry... I didn't understand you...\n";
         std::cout << "The creator of your item is " << authorName << "... is that right?\n";
         std::cout << "Enter yes or no: ";
         std::cin >> verification;
         std::transform(verification.begin(), verification.end(), verification.begin(), ::tolower);
      };
   };

   instream.open("items.txt");
   if (instream.fail()) {
      std::cout << "instream.open() failed... Ermahgerd!\n";
      return;
   };
   std::getline(instream, fileContents);
   instream.close();
   insert = fileContents;
   if (insert.length() == 0) {
      insert = "|";
   };
   insert += isbn10 + ":" + itemName + ":" + authorName + ":00000000|";
   outStream.open("items.txt");
   outStream << insert;
   outStream.close();
   return;
}

void Owner::removeItem() {
   std::string itemInfo;
   std::ifstream instream;
   std::ofstream outstream;
   std::string fileContents;
   std::string itemStatus;
   int statusLoc;
   int infoLoc;
   int beginItemInfo;
   int endItemInfo;
   Banners banner;
 
   std::cout << "Please enter either the Title, ISBN, or Creator \n"
             << "of the item you would like to remove: ";
   std::cin.ignore(10, '\n');
   std::getline(std::cin, itemInfo);
   
   instream.open("items.txt");
   if (instream.fail()) {
      std::cout << "Uhoh items.txt failed to open X_X";
      return;
   };
    
   std::getline(instream, fileContents);
   instream.close();
   
   infoLoc = fileContents.find(itemInfo);
   if (infoLoc < 0) {
      std::cout << "Item not found";
      return;
   }
   
   beginItemInfo = fileContents.rfind("|", infoLoc);
   endItemInfo = fileContents.find("|", infoLoc);
   
   statusLoc = fileContents.rfind(":", endItemInfo);
   itemStatus = fileContents.substr(statusLoc + 1, 8);
      
   if (itemStatus == "00000000") {
      if (banner.confirm("remove an item from the database")) {
         outstream.open("items.txt");
         if(outstream.fail()) {
            std::cout << "Items.txt did not open... X_X";
            return;
         };
      
         if (beginItemInfo == 0) {
            outstream << fileContents.substr(endItemInfo);
         }
         else {
            outstream << fileContents.substr(0, beginItemInfo + 1) << fileContents.substr(endItemInfo + 1);
            std::cout << fileContents.substr(0, beginItemInfo + 1) << " " << fileContents.substr(endItemInfo + 1) << "\n";
         };
         outstream.close();
      };
   }
   else {
      banner.failure("The item is not checked in to the library!");
   };
   return;
};
