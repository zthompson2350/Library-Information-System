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

int main() {
        std::string currentUser;
        Mode currentUserMode;
        User user;
        Patron patron;
        Employee employee;
        Owner owner;
        Banners banner;
        Controller controller;
        bool quit = false;
        bool superquit = false;
        int selection;

        srand(time(NULL));
        currentUser = controller.startUp();

        if (currentUser == "") {
                std::cout << "Login Failed... Sorry...\n";
                return -1;
        };

        user.setUserID(currentUser);
        user.setName(currentUser);
        banner.cls();
        banner.welcomeBack(user.getName());
        banner.buffer();
        switch (user.getMode()) {
                case P:
                        patron.setUserID(currentUser);
                        patron.setName(currentUser);
			while (!quit) {
				banner.patronOptions();
				std::cin >> selection;
				switch (selection) {
					case 1:
						patron.search(currentUser);
						break;
					case 2:
						break;
					case 3:
						quit = true;
						break;
					default:
						break;
				};
			};
                        break;
                case E:
                        employee.setUserID(currentUser);
                        employee.setName(currentUser);
			while (!quit) {
				banner.employeeOptions();
				std::cin >> selection;
				switch (selection) {
					case 1:
						employee.createAccount();
						break;
					case 2:
						employee.addItem();
						break;
					case 3:
						employee.search(currentUser);
						break;
					case 4:
						employee.freezeAccount();
						break;
					case 5:
						break;
					case 6:
						break;
					case 7:
						quit = true;
						break;
					default:
						break;
				};
			}
                        break;
                case O:
                        owner.setUserID(currentUser);
                        owner.setName(currentUser);
                        while (!quit) {
                                banner.ownerOptions();
                                std::cin >> selection;
                                switch (selection) {
                                        case 1:
						owner.createAccount();
                                                break;
                                        case 2:
                                                owner.addEmployee();
                                                break;
                                        case 3:
						owner.addItem();
                                                break;
                                        case 4:
						owner.removeItem();
                                                break;
                                        case 5:
						owner.search(currentUser);
                                                break;
                                        case 6:
						owner.freezeAccount();
                                                break;
                                        case 7:
                                                break;
                                        case 8:
                                                break;
                                        case 9:
                                                quit = true;
                                                break;
                                        default:
                                                break;
                                };
                        };
                        break;
                default:
                        break;
        };
	return 0;
};
