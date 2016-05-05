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

void Banners::cls() {
        int i = 0;
        while (i < 500) {
                std::cout << "\n";
                i++;
        }
        return;
}

void Banners::welcome() {
        std::string printme;
        printme =  "                                              ================================================\n";
        printme += "                                              |                                              |\n";
        printme += "                                              |  Welcome to the Library Information System!  |\n";
        printme += "                                              |                                              |\n";
        printme += "                                              ================================================\n";
        printme += "\n\n";
        std::cout << printme;
        return;
}

void Banners::welcomeBack(std::string userName) {
        std::string printme;
        int i = 0;
        int strlen = userName.length();
        printme =  "                                              ================================================\n";
        printme += "                                              |                                              |\n";
        while (i < 46) {
                printme += " ";
                i++;
        };
        printme += "|";
        i = 0;
        while (i < 11) {
                printme += " ";
                i++;
        };
        printme += "Welcome back, " + userName + "!";
        i = 0;
        while (i <= (19 - (strlen))) {
                printme += " ";
                i++;
        };
        printme += "|\n";
        printme += "                                              |                                              |\n";
        printme += "                                              ================================================\n";
        printme += "\n\n";
        std::cout << printme;
        return;
};

void Banners::buffer() {
        int i = 0;
        while (i < 15) {
                std::cout << "\n";
                i++;
        };
        return;
};

void Banners::ownerOptions() {
        std::cout << "\nChoose an option from the following list...\n\n";
        std::cout << "(1) Create Account, (2) Add Employee, (3) Add Item, (4) Remove Item\n";
        std::cout << "(5) Search, (6) Freeze Account, (7) Purchase Item, (8) Pay Fine, (9) Logout\n\n";
        std::cout << "Make your selection now: ";
        return;
};

void Banners::employeeOptions() {
	std::cout << "\nChoose an option from the following list...\n\n";
	std::cout << "(1) Create Account, (2) Add Item, (3) Search, (4) Freeze Account,\n";
	std::cout << "(5) Purchase Item, (6) Pay Fine, (7) Logout\n\n";
	std::cout << "Make your selection now: ";
        return;
};

void Banners::patronOptions() {
	std::cout << "\nChoose an option from the following list...\n\n";
	std::cout << "(1) Search, (2) Check History, (3) Logout\n\n";
	std::cout << "Make your selection Now: ";
        return;
};


bool Banners::confirm(std::string message) {
   std::string answer;
   std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~WAIT~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
             << "You are about to " << message << "\n"
             << "Do you want to continue?\n"
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
             << "Enter yes or no: ";
   std::cin >> answer;
   std::cin.ignore(10, '\n'); 
   std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
   while (answer != "yes" && answer != "no") {
      std::cout << "I didn't understand you... Do you want to continue?\n";
      std::cout << "Enter yes or no: ";
      std::cin >> answer;
      std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);	
   };
   if (answer == "yes") {
      return true;
   }
   else {
      std::cout << "Cancelling...\n\n";
   };
   return false;
};

void Banners::failure(std::string message) {
   std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~ERROR~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
             << message << "\n"
             << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
   return; 

};
