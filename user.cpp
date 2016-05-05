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

std::string User::determineCurrentUser() {
        std::ifstream instream;
        std::string userID;
        Controller controller;
        instream.open("users.txt");

        if (instream.fail()) {
                userID = controller.setUp();
                currentUserID = userID;
                return userID;
        }

        std::cout << "Enter your User ID: ";
        std::cin >> userID;
        instream.close();

        if (!verifyUser(userID)){
                return "";
        };

        currentUserID = userID;


        return userID;
};

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


void User::search(std::string userID) {
	std::string selection;
	std::string searchCriteria;
	std::ifstream inStream;
	std::string fileContents;
	int currentLoc = 0;
	int hits = 0;
	std::string buffer = "|";
	int prevPipe;
	int nextPipe;
	std::string title;
	std::string author;
	std::string status;
	int index1 = 0;
	int index2;
	std::string output = "";
	int resultCounter = 1;
	std::ostringstream convert;
	int choice;


	std::cout << "How would you like to conduct your search?\n\n";
	std::cout << "(1) Search by Title\n";
	std::cout << "(2) Search by Author\n";
	std::cout << "(3) Search by ISBN\n\n";
	std::cout << "Make your selection now: ";
	std::cin >> selection;
 	while (selection != "1" && selection != "2" && selection != "3") {
		std::cout << "Invalid selection...\n";
	        std::cout << "How would you like to conduct your search?\n\n";
        	std::cout << "(1) Search by Title\n";
	        std::cout << "(2) Search by Author\n";
	        std::cout << "(3) Search by ISBN\n\n";
        	std::cout << "Make your selection now: ";
	        std::cin >> selection;
	};

	switch (selection[0]) {
		case '1':
			std::cout << "\nEnter the Title of the item you are looking for: ";
		        std::cin.ignore(10, '\n');
 		        std::getline(std::cin, searchCriteria);
			inStream.open("items.txt");
			if (inStream.fail()) {
				std::cout << "inStream.open() failed... ermahgerd!\n";
			};
			std::getline(inStream, fileContents);
			currentLoc = fileContents.find(searchCriteria);
			while (currentLoc > 0) {
				prevPipe = fileContents.rfind("|", currentLoc);	
				nextPipe = fileContents.find("|", currentLoc);
				buffer += fileContents.substr(prevPipe + 1, nextPipe - prevPipe);
				hits++;
				currentLoc = fileContents.find(searchCriteria, currentLoc + 1);
			};		
			break;
		case '2':
			std::cout << "\nEnter the Author/Director/Creator's name: ";
			std::cin.ignore(10, '\n');
			std::getline(std::cin, searchCriteria);
			inStream.open("items.txt");
                        if (inStream.fail()) {
                                std::cout << "inStream.open() failed... ermahgerd!\n";
                        };
                        std::getline(inStream, fileContents);
			currentLoc = fileContents.find(searchCriteria);
			while (currentLoc > 0) { 
                                prevPipe = fileContents.rfind("|", currentLoc);
                                nextPipe = fileContents.find("|", currentLoc);
                                buffer += fileContents.substr(prevPipe + 1, nextPipe - prevPipe);
				hits++;
				currentLoc = fileContents.find(searchCriteria, currentLoc + 1);
                        };
			break;
		case '3':
			std::cout << "\nEnter the ISBN of the item you are looking for: ";
			std::cin.ignore(10, '\n');
			std::getline(std::cin, searchCriteria);
			inStream.open("items.txt");
                        if (inStream.fail()) {
                                std::cout << "inStream.open() failed... ermahgerd!\n";
                        };
                        std::getline(inStream, fileContents);
			currentLoc = fileContents.find(searchCriteria);
			while (currentLoc > 0) { 
                                prevPipe = fileContents.rfind("|", currentLoc);
                                nextPipe = fileContents.find("|", currentLoc);
                                buffer += fileContents.substr(prevPipe + 1, nextPipe - prevPipe);
				hits++;
				currentLoc = fileContents.find(searchCriteria, currentLoc + 1);
                        };
			break;
		default:
			break;
	};

	if (hits == 0) {
		std::cout << "No items matched your search...\n";
		return;
	};

	std::cout << "\nI was able to find " << hits << " results matching your criteria.\n";
	index1 = buffer.find(":");
	while (index1 > 0) {
		index2 = buffer.find(":", index1 + 1);
		title = buffer.substr(index1 + 1, index2 - index1 - 1);
		index1 = index2;
		index2 = buffer.find(":", index1 + 1);
		author = buffer.substr(index1 + 1, index2 - index1 - 1);
		index1 = index2;
		index2 = buffer.find("|", index1 + 1);
		status = buffer.substr(index1 + 1, index2 - index1 - 1);
		output += "\nResult ";
		convert.str("");
		convert.clear();
		convert << resultCounter;
		output += convert.str();
		output += ":\nTitle: " + title + "\nAuthor: " + author + "\nStatus: ";
		if (status == "00000000") {
			status = "Checked In";
		}
		else if (status == "99999999") {
			status = "Reserved";
		}
		else {
			status = "Checked Out";
		};
		output += status + "\n";
		index1 = buffer.find(":", index2 + 1);
		resultCounter++;
	};
	std::cout << output;
	std::cout << "\nWould you like to continue with any of these results?\n";
	std::cout << "Please enter the number corresponding to the result you would like to continue with.\n";
	std::cout << "Or, if you're done, enter 0.\n\n";
	std::cout << "Make your selection now: ";
	std::cin >> selection;
	if (selection == "0") {
		return;
	};
	std::string::size_type sz;
	choice = std::atoi(selection.c_str()); 
	if (choice > resultCounter) {
		std::cout << "\nInvalid choice. Returning...\n";
		return;
	};
	index1 = 0;
	choice = 1;
	while (choice < std::atoi(selection.c_str())) {
		index1 = buffer.find("|", index1 + 1);
		choice++;
	};
	index2 = buffer.find("|", index1 + 1);
	buffer = buffer.substr(index1 + 1, index2 - index1 - 1);
	index1 = buffer.find(":");
	index2 = buffer.find(":", index1 + 1);
	buffer = buffer.substr(index1 + 1, index2 - index1 - 1);

	
	std::cout << "Okay, what would you like to do with your selection?\n";
	std::cout << "You can (1) Check Out, (2) Check In, or (3) Renew\n\n";
	std::cout << "Make your selection now: ";
	std::cin >> selection;
	switch (selection[0]) {
		case '1':
			checkOut(userID, buffer);
			break;
		case '2':
			checkIn(userID, buffer);
			break;
		case '3':
			renew(userID, buffer);
			break;
		default:
			std::cout << "Invalid selection. Returning...\n";
	};
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
   

	if (userID[0] != '1') {
		std::cout << "Please enter the Patron's User ID: ";
		std::cin >> userID;
	};
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

void User::updateItemStatus(std::string title, std::string newStatus) {
   int beginTitle;
   int IDLoc;
   int endPipe;
   std::string entry;
   std::string fileContents;
   std::ifstream instream;
   std::ofstream outstream;
   
   instream.open("items.txt");
   if (instream.fail()) {
      std::cout << "Damn it items.txt..\n";
      return;
   };
   std::getline(instream, fileContents);
   instream.close();
            
   beginTitle = fileContents.find(title);
   IDLoc = fileContents.find(":", beginTitle + title.length() + 1);
   endPipe = fileContents.find("|", IDLoc);
   entry = fileContents.substr(IDLoc + 1, endPipe - IDLoc - 1);
   
   outstream.open("items.txt");
   if (outstream.fail()) {
      std::cout << "noooo items.txt\n";
      return;
   };
   outstream << fileContents.substr(0, IDLoc + 1) << newStatus << fileContents.substr(endPipe);
   outstream.close();
   //std::cout << fileContents.substr(0, IDLoc + 1) << "00000000" << fileContents.substr(endPipe) << "\n";
   return;          
};

void User::checkOut(std::string userID, std::string itemInfo) {
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

   if (userID[0] != '1') {
      std::cout << "Please enter the Patron's User ID: ";
      std::cin >> userID;
   };
   instream.open("history.txt");
   if (instream.fail()) {
      std::cout << "Oh no...history.txt failed to open";
      return;
   };
   std::getline(instream, fileContents);
   instream.close();

   // std::cout <<fileContents << userID << ":" << itemInfo << ":" 
      //        << 2 + newDate->tm_mon << "/" << newDate->tm_mday << "|";
   outstream.open("history.txt");
   outstream << fileContents << userID << ":" << itemInfo << ":" 
             << 2 + newDate->tm_mon << "/" << newDate->tm_mday << "|";
   outstream.close();
   updateItemStatus(itemInfo, userID);
   //IDLoc = fileContents.find(userID);

   return;
}

void User::checkIn(std::string userID, std::string itemInfo) {
   std::string date;
   time_t now = time(0);
   tm *newDate = localtime(&now);
   int beginPipe;
   int endPipe;
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
   std::string checkID;
   bool found = false;

   if (userID[0] != '1') {
      std::cout << "Please enter the Patron's User ID: ";
      std::cin >> userID;
   };
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
            std::cout << "found it! checking in...\n";
            date = fileContents.substr(endTitle + 1, 5);   
            std::istringstream (date.substr(0,2)) >> month;
            std::istringstream (date.substr(3, 2)) >> day;
            
            if (((1 + newDate->tm_mon) > month) || (newDate->tm_mday > day)) {
               //charge fee
                               
            } 
            outstream.open("history.txt");
            if (outstream.fail()) {
               std::cout << "Uh oh. it didn't open";
               return;
            }; 
            beginPipe = fileContents.rfind("|", beginTitle);
            endPipe = fileContents.find("|", beginTitle);
            if (beginPipe == 0) {
               outstream << fileContents.substr(endPipe);
            }
            else {
               outstream << fileContents.substr(0, beginPipe) << fileContents.substr(endPipe);
            }
            outstream.close();
            updateItemStatus(itemInfo, "00000000");
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
