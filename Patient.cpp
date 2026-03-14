#include "Patient.h"
#include <iostream>
#include <iomanip>
using namespace std;

Patient::Patient() {
    patientID        = "PT000";
    patientName      = "Unknown";
    patientAge       = 0;
    patientPhone     = "N/A";
    bloodGroup       = "N/A";
    currentCondition = "None";
    isActive         = true;
}

Patient::Patient(string id, string name, int age, string phone, string blood, string condition) {
    patientID        = id;
    patientName      = name;
    patientAge       = (age > 0 && age < 130) ? age : 0;
    patientPhone     = phone;
    bloodGroup       = blood;
    currentCondition = condition;
    isActive         = true;
}

Patient::Patient(const Patient& other) {
    patientID        = other.patientID;
    patientName      = other.patientName;
    patientAge       = other.patientAge;
    patientPhone     = other.patientPhone;
    bloodGroup       = other.bloodGroup;
    currentCondition = other.currentCondition;
    isActive         = other.isActive;
}

Patient::~Patient() {}

string Patient::getPatientID()        const { return patientID; }
string Patient::getPatientName()      const { return patientName; }
int    Patient::getPatientAge()       const { return patientAge; }
string Patient::getPatientPhone()     const { return patientPhone; }
string Patient::getBloodGroup()       const { return bloodGroup; }
string Patient::getCurrentCondition() const { return currentCondition; }
bool   Patient::getIsActive()         const { return isActive; }

void Patient::setPatientName(const string& name) {
    if (!name.empty()) patientName = name;
    else cout << "  [Error] Name cannot be empty.\n";
}

void Patient::setPatientAge(int age) {
    if (age > 0 && age < 130) patientAge = age;
    else cout << "  [Error] Age must be between 1 and 129.\n";
}

void Patient::setPatientPhone(const string& phone) {
    if (phone.length() >= 7) patientPhone = phone;
    else cout << "  [Error] Phone number is too short.\n";
}

void Patient::setBloodGroup(const string& blood) {
    if (!blood.empty()) bloodGroup = blood;
}

void Patient::setCurrentCondition(const string& condition) {
    currentCondition = condition;
}

void Patient::setIsActive(bool status) { isActive = status; }

void Patient::displayDetails() const {
    cout << "\n  +-----------------------------------------+\n";
    cout << "  |           PATIENT DETAILS               |\n";
    cout << "  +-----------------------------------------+\n";
    cout << "  | Patient ID   : " << left << setw(25) << patientID        << "|\n";
    cout << "  | Name         : " << left << setw(25) << patientName      << "|\n";
    cout << "  | Age          : " << left << setw(25) << patientAge       << "|\n";
    cout << "  | Phone        : " << left << setw(25) << patientPhone     << "|\n";
    cout << "  | Blood Group  : " << left << setw(25) << bloodGroup       << "|\n";
    cout << "  | Condition    : " << left << setw(25) << currentCondition << "|\n";
    cout << "  | Status       : " << left << setw(25) << (isActive ? "Active" : "Inactive") << "|\n";
    cout << "  +-----------------------------------------+\n";
}

void Patient::displayRow() const {
    cout << "  | " << left << setw(7)  << patientID
         << "| " << setw(20) << patientName
         << "| " << setw(4)  << patientAge
         << "| " << setw(6)  << bloodGroup
         << "| " << setw(14) << patientPhone
         << "| " << setw(9)  << (isActive ? "Active" : "Inactive") << "|\n";
}
