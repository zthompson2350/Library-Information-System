#ifndef OWNER_H
#define OWNER_H

class Owner : public User {
        public:
                void createAccount();
                void addEmployee();
		void addItem();
		void freezeAccount();
		void removeItem();
        private:
		void changeStatus(int statusLoc, std::string fileContents, std::string newStatus);
        protected:
};

#endif
