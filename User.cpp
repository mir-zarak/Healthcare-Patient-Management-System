#include "User.h"
#include <iostream>
#include <iomanip>
using namespace std;

User::User() {
    username     = "guest";
    userPassword = "";
    userRole     = "none";
    isLoggedIn   = false;
}

User::User(string name, string password, string role) {
    username     = name;
    userPassword = password;
    userRole     = role;
    isLoggedIn   = false;
}

User::User(const User& other) {
    username     = other.username;
    userPassword = other.userPassword;
    userRole     = other.userRole;
    isLoggedIn   = other.isLoggedIn;
}

User::~User() {}

string User::getUsername()   const { return username; }
string User::getUserRole()   const { return userRole; }
bool   User::getIsLoggedIn() const { return isLoggedIn; }

void User::setUserPassword(const string& password) {
    if (!password.empty()) userPassword = password;
}

void User::setUserRole(const string& role) { userRole = role; }

bool User::login(const string& name, const string& password) {
    if (name == username && password == userPassword) {
        isLoggedIn = true;
        cout << "\n  Login successful. Welcome, " << username << " [" << userRole << "]\n";
        return true;
    }
    cout << "\n  Incorrect username or password.\n";
    return false;
}

void User::logout() {
    isLoggedIn = false;
    cout << "\n  Logged out successfully. Goodbye, " << username << "\n";
}

bool User::hasAccess(const string& feature) const {
    if (userRole == "admin") return true;

    if (userRole == "doctor") {
        return feature == "view_patient"    ||
               feature == "update_patient"  ||
               feature == "add_record"      ||
               feature == "view_record"     ||
               feature == "update_record"   ||
               feature == "view_appt"       ||
               feature == "book_appt"       ||
               feature == "complete_appt";
    }

    if (userRole == "receptionist") {
        return feature == "add_patient"    ||
               feature == "view_patient"   ||
               feature == "update_patient" ||
               feature == "book_appt"      ||
               feature == "view_appt"      ||
               feature == "cancel_appt"    ||
               feature == "generate_bill"  ||
               feature == "process_payment"||
               feature == "view_bill";
    }

    return false;
}

void User::displayDetails() const {
    cout << "\n  +--------------------------+\n";
    cout << "  |       USER DETAILS       |\n";
    cout << "  +--------------------------+\n";
    cout << "  | Username : " << left << setw(14) << username   << "|\n";
    cout << "  | Role     : " << left << setw(14) << userRole   << "|\n";
    cout << "  | Status   : " << left << setw(14) << (isLoggedIn ? "Logged In" : "Logged Out") << "|\n";
    cout << "  +--------------------------+\n";
}
