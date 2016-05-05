#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee : public User {
        public:
                void createAccount();
		void addItem();
		void freezeAccount();
		void changeStatus(int statusLoc, std::string fileContents, std::string newStatus);
        private:
        protected:
};

#endif
