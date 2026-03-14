#ifndef USER_H
#define USER_H
#include <string>
using namespace std;

class User {
private:
    string username;
    string userPassword;
    string userRole;
    bool   isLoggedIn;

public:
    User();
    User(string name, string password, string role);
    User(const User& other);
    ~User();

    string getUsername()   const;
    string getUserRole()   const;
    bool   getIsLoggedIn() const;

    void setUserPassword(const string& password);
    void setUserRole(const string& role);

    bool login(const string& name, const string& password);
    void logout();
    bool hasAccess(const string& feature) const;

    void displayDetails() const;
};

#endif
