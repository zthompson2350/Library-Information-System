#ifndef BANNERS_H
#define BANNERS_H
#include <string>

class Banners {
        public:
                void cls();
                void welcome();
                void welcomeBack(std::string userName);
                void buffer();
                void ownerOptions();
                void employeeOptions();
                void patronOptions();
		bool confirm(std::string message);
		void failure(std::string message);
        private:
        protected:
};

#endif
