#include "Doctor.h"
#include <iostream>
#include <iomanip>
using namespace std;

Doctor::Doctor() {
    doctorID           = "DR000";
    doctorName         = "Unknown";
    specialization     = "General";
    doctorPhone        = "N/A";
    departmentID       = "NONE";
    isAvailable        = true;
    totalAppointments  = 0;
}

Doctor::Doctor(string id, string name, string spec, string phone, string deptID) {
    doctorID           = id;
    doctorName         = name;
    specialization     = spec;
    doctorPhone        = phone;
    departmentID       = deptID;
    isAvailable        = true;
    totalAppointments  = 0;
}

Doctor::Doctor(const Doctor& other) {
    doctorID           = other.doctorID;
    doctorName         = other.doctorName;
    specialization     = other.specialization;
    doctorPhone        = other.doctorPhone;
    departmentID       = other.departmentID;
    isAvailable        = other.isAvailable;
    totalAppointments  = other.totalAppointments;
}

Doctor::~Doctor() {}

string Doctor::getDoctorID()          const { return doctorID; }
string Doctor::getDoctorName()        const { return doctorName; }
string Doctor::getSpecialization()    const { return specialization; }
string Doctor::getDoctorPhone()       const { return doctorPhone; }
string Doctor::getDepartmentID()      const { return departmentID; }
bool   Doctor::getIsAvailable()       const { return isAvailable; }
int    Doctor::getTotalAppointments() const { return totalAppointments; }

void Doctor::setDoctorName(const string& name) {
    if (!name.empty()) doctorName = name;
    else cout << "  [Error] Name cannot be empty.\n";
}

void Doctor::setSpecialization(const string& spec) {
    if (!spec.empty()) specialization = spec;
}

void Doctor::setDoctorPhone(const string& phone) {
    if (phone.length() >= 7) doctorPhone = phone;
    else cout << "  [Error] Phone number is too short.\n";
}

void Doctor::setDepartmentID(const string& deptID) { departmentID = deptID; }

void Doctor::setIsAvailable(bool status) { isAvailable = status; }

void Doctor::incrementAppointments() { totalAppointments++; }

void Doctor::displayDetails() const {
    cout << "\n  +-----------------------------------------+\n";
    cout << "  |            DOCTOR DETAILS               |\n";
    cout << "  +-----------------------------------------+\n";
    cout << "  | Doctor ID     : " << left << setw(24) << doctorID                              << "|\n";
    cout << "  | Name          : " << left << setw(24) << ("Dr. " + doctorName)                 << "|\n";
    cout << "  | Specialization: " << left << setw(24) << specialization                        << "|\n";
    cout << "  | Phone         : " << left << setw(24) << doctorPhone                           << "|\n";
    cout << "  | Department    : " << left << setw(24) << departmentID                          << "|\n";
    cout << "  | Availability  : " << left << setw(24) << (isAvailable ? "Available" : "Busy") << "|\n";
    cout << "  | Appointments  : " << left << setw(24) << totalAppointments                     << "|\n";
    cout << "  +-----------------------------------------+\n";
}

void Doctor::displayRow() const {
    cout << "  | " << left << setw(7)  << doctorID
         << "| " << setw(20) << doctorName
         << "| " << setw(22) << specialization
         << "| " << setw(13) << doctorPhone
         << "| " << setw(9)  << (isAvailable ? "Available" : "Busy") << "|\n";
}
