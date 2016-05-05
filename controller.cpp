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


std::string Controller::startUp() {
        std::string userID;
        Banners banners;
        User user;
        banners.cls();
        banners.welcome();
        banners.buffer();
        userID = user.determineCurrentUser();
        return userID;
};

std::string Controller::setUp() {
        std::ofstream outstream;
        std::string name = "";
        std::string ownershipCheck;
        bool ownsSystem;
        std::locale loc;
        std::string insert = "";
        std::string userID = "3";
        int identifier;
        std::ostringstream convert;

        std::cout << "Hey there! I noticed this is your first time using the Library Information System!\n";
        std::cout << "So... I'm assuming that means you're the owner right?\n";
        std::cout << "Enter yes or no: ";
        std::cin >> ownershipCheck;
        std::transform(ownershipCheck.begin(), ownershipCheck.end(), ownershipCheck.begin(), ::tolower);
        while (ownershipCheck != "yes" && ownershipCheck != "no") {
                std::cout << "I didn't understand you... You're the owner right?\n";
                std::cout << "Enter yes or no: ";
                std::cin >> ownershipCheck;
                std::transform(ownershipCheck.begin(), ownershipCheck.end(), ownershipCheck.begin(), ::tolower);
        };
        if (ownershipCheck == "no") {
                std::cout << "Please get the owner of the Library and have them set up the Library Information System... Terminating...\n\n";
                return name;
        };
        std::cout << "Okay great! So, tell me, what's your name: ";
        std::cin.ignore(10, '\n');
        std::getline(std::cin, name);
        std::cout << "It's nice to meet you, " << name << "!\n";
        identifier = RNG();
        convert << identifier;
        userID += convert.str();
        std::cout << "Your User ID is " << userID << "\nPlease write it down as you will need it to log in.\n";
        insert += "|" + userID + ":" + name + ":A:0.00|";
        outstream.open("users.txt");
        outstream << insert;
        outstream.close();
        outstream.open("items.txt");
        outstream.close();
        outstream.open("history.txt");
        outstream.close();
        return userID;
};

int Controller::RNG() {
        int number = rand()%9999999 + 1111111;
        return number;
};
