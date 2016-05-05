#ifndef USER_H
#define USER_H
#include <string>


enum Mode { P, E, O };


class User {
        public:
                std::string determineCurrentUser();
                void setUserID(std::string userID);
                std::string getName();
                void setName(std::string userID);
                void setStatus(std::string userID);
                Mode getMode();
		void search(std::string userID);
		void checkHistory(std::string userID);
        private:
                bool verifyUser(std::string userID);
        protected:
                std::string currentUserID; // First number represents account type. 1: Patron; 2: Employee; 3: Owner
                std::string name;
                char status; // A: Active; F: Frozen
                std::string fine;
                Mode userType;
		void renew(std::string userID, std::string itemInfo);
		void checkOut(std::string userID, std::string itemInfo);
		void checkIn(std::string userID, std::string itemInfo);
};

#endif
