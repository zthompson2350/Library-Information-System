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
#include <ctime>




std::string User::determineCurrentUser() {
   std::ifstream instream;
   std::string userID;
   Controller controller;
   std::string selection;
   int count = 0;
   instream.open("users.txt");

   if (instream.fail()) {
      userID = controller.setUp();
      currentUserID = userID;
      return userID;
   }
   
   std::cout << "\nChoose an option from the following list...\n\n"
        << "Login (1), Exit System(2)\n\n"
        << "Make your selection now: ";
   std::cin >>  selection;  
   
   while (selection != "1" && selection != "2") {
      std::cout << "\nI'm sorry... I didn't understand you...\n"
                << "Choose an option from the following list...\n\n"
                << "Login (1), Exit System(2)\n\n"
                << "Make your selection now: ";
      std::cin >> selection;
   };
   
   if (selection == "1") {
      while (count < 3 && !verifyUser(userID)) {
         std::cout << "Enter your User ID: ";
         std::cin >> userID;
         instream.close();
      
         if (!verifyUser(userID)){
            std::cout << "Login Failed... Sorry...\n";
            count++;
            userID = "";
         }
         else {
            currentUserID = userID;
         };
      }
   }
   else if (selection == "2") {
      userID = "quit";
   };
   
  


   return userID;
}

bool User::verifyUser(std::string userID) {
   std::string fileContents;
   int index;
   std::ifstream instream;

   if (userID.length() < 8) {
      return false;
   }
   instream.open("users.txt");
   if (instream.fail()) {
      std::cerr << ("ifstream.open failed... ermahgerd");
      return false;
   };
   std::getline(instream, fileContents);
   instream.close();
   index = fileContents.find(userID);
   if (index > 0) {
      return true;
   };
   return false;
};

void User::setUserID(std::string userID) {
   currentUserID = userID;
   if (userID[0] == '1') {
      userType = P;
   }
   else if (userID[0] == '2') {
      userType = E;
   }
   else if (userID[0] == '3') {
      userType = O;
   }
   else {
      std::cout << "Something went wrong...\n";
   };
   return;
};

std::string User::getName() {
   return name;
};

void User::setName(std::string userID) {
   std::ifstream instream;
   std::string fileContents;


   instream.open("users.txt");
   if (instream.fail()) {
      std::cout << "instream.open failed... ehrmahgerd!\n";
      return;
   };
   std::getline(instream, fileContents);
   int IDLoc = fileContents.find(userID);
   int startName = fileContents.find(":", IDLoc) + 1;
   int endName = fileContents.find(":", startName) - 1;
   std::string userName = fileContents.substr(startName, endName - startName + 1);
   name = userName;
   return;
};

Mode User::getMode() {
   return userType;
};

void User::renew(std::string userID, std::string itemInfo) {
   std::string date;
   time_t now = time(0);
   tm *newDate = localtime(&now);
   int beginTitle;
   int endTitle;
   int IDLoc;
   int dateLoc;
   int month;
   int day;
   std::ifstream instream;
   std::string fileContents;
   std::ofstream outstream;
   std::string entry;
   bool found = false;
   
   instream.open("history.txt");
   if (instream.fail()) {
      std::cout << "Oh no...history.txt failed to open";
      return;
   };
   
   std::getline(instream, fileContents);
   instream.close();
   
   IDLoc = fileContents.find(userID);
   if (IDLoc > 0 && fileContents.substr(IDLoc, 8) == userID) {
      beginTitle = fileContents.find(":", IDLoc);
      endTitle = fileContents.find(":", beginTitle + 1);
      entry = fileContents.substr(beginTitle + 1, endTitle - beginTitle - 1);
      
      while (!found) {
         if (entry == itemInfo) {
            std::cout << "found it! renewing...\n";
            date = fileContents.substr(endTitle + 1, 5);   
            std::istringstream (date.substr(0,2)) >> month;
            std::istringstream (date.substr(3, 2)) >> day;
            
            if (((1 + newDate->tm_mon) > month) || (newDate->tm_mday > day)) {
               //charge fee
               outstream.open("history.txt");
               if (outstream.fail()) {
                  std::cout << "Uh oh. it didn't open";
                  return;
               };
               if ((1+newDate->tm_mon) < 10 && (newDate->tm_mday < 10))
               {
                  outstream << fileContents.substr(0, endTitle + 1) << "0" <<2 + newDate->tm_mon << "/0"
                         << newDate->tm_mday << fileContents.substr(endTitle + 6);
               }
               else if(((1+newDate->tm_mon) < 10 ) && (newDate->tm_mday > 9)) {
                  outstream << fileContents.substr(0, endTitle+1) << "0" << 2 + newDate->tm_mon << "/"
                         << newDate->tm_mday << fileContents.substr(endTitle + 6);
               }
               else {
                  outstream << fileContents.substr(0, endTitle+1) << 2 + newDate->tm_mon << "/"
                         << newDate->tm_mday << fileContents.substr(endTitle + 6);
               
               };
               
               outstream.close();
            } 
            found = true;
         }
         else {
            IDLoc = fileContents.find(userID, endTitle);
            if (IDLoc > 0) {
               beginTitle = fileContents.find(":", IDLoc);
               endTitle = fileContents.find(":", beginTitle + 1);
               entry = fileContents.substr(beginTitle + 1, endTitle - beginTitle - 1);
               std::cout << "looking..." << "\n";
            }
            else {
               std::cout << "could not find the item related to the user\n";
               found = true;
            };
         }
      };
   };
   return;
};


void User::checkHistory(std::string userID) {
   std::ifstream instream;
   std::ostringstream convert;
   std::string fileContents;
   std::string buffer = "|";
   std::string title;
   std::string date;
   int IDLoc;
   int beginPipe;
   int endPipe;
   int hits = 0;
   int resultCounter = 1;
   int index1 = 0;
   int index2;
   std::string output = "";
   
   instream.open("history.txt");
   if (instream.fail()) {
      std::cout << "history.txt did not open -_-";
      return;
   };
   
   std::getline(instream, fileContents);
   IDLoc = fileContents.find(userID);
   while (IDLoc > 0) {
      beginPipe = fileContents.rfind("|", IDLoc);
      endPipe = fileContents.find("|", IDLoc);
      buffer += fileContents.substr(beginPipe + 1, endPipe - beginPipe);
      hits++;
      IDLoc = fileContents.find(userID, IDLoc + 1);
   };
   
   
   if (hits == 0) {
      std::cout << "No items checked out...\n";
      return;
   };
   
   std::cout << "\nI was able to find " << hits << " results matching your criteria.\n";
   index1 = buffer.find(":");
   while (index1 > 0) {
      index2 = buffer.find(":", index1 + 1);
      title = buffer.substr(index1 + 1, index2 - index1 - 1);
      index1 = index2;
      index2 = buffer.find("|", index1 + 1);
      date = buffer.substr(index1 + 1, index2 - index1 - 1);
      index1 = buffer.find(":", index2);
      // index2 = buffer.find("|", index1 + 1);
      // status = buffer.substr(index1 + 1, index2 - index1 - 1);
      output += "\nResult ";
      convert.str("");
      convert.clear();
      convert << resultCounter;
      output += convert.str();
      output += ":\nTitle: " + title + "\nDue Date: " + date;
      resultCounter++;
   };
   std::cout << output;
   return;
};
