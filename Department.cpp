#include "Department.h"
#include <iostream>
#include <iomanip>
using namespace std;

Department::Department() {
    departmentID       = "DP000";
    departmentName     = "Unknown";
    floorLocation      = "N/A";
    headDoctorID       = "NONE";
    doctorCapacity     = 10;
    currentDoctorCount = 0;
}

Department::Department(string id, string name, string floor, int capacity) {
    departmentID       = id;
    departmentName     = name;
    floorLocation      = floor;
    headDoctorID       = "NONE";
    doctorCapacity     = (capacity > 0) ? capacity : 10;
    currentDoctorCount = 0;
}

Department::Department(const Department& other) {
    departmentID       = other.departmentID;
    departmentName     = other.departmentName;
    floorLocation      = other.floorLocation;
    headDoctorID       = other.headDoctorID;
    doctorCapacity     = other.doctorCapacity;
    currentDoctorCount = other.currentDoctorCount;
}

Department::~Department() {}

string Department::getDepartmentID()       const { return departmentID; }
string Department::getDepartmentName()     const { return departmentName; }
string Department::getFloorLocation()      const { return floorLocation; }
string Department::getHeadDoctorID()       const { return headDoctorID; }
int    Department::getDoctorCapacity()     const { return doctorCapacity; }
int    Department::getCurrentDoctorCount() const { return currentDoctorCount; }

void Department::setDepartmentName(const string& name) {
    if (!name.empty()) departmentName = name;
    else cout << "  [Error] Department name cannot be empty.\n";
}

void Department::setFloorLocation(const string& floor) { floorLocation = floor; }

void Department::setHeadDoctorID(const string& id) { headDoctorID = id; }

void Department::addDoctor() {
    if (currentDoctorCount < doctorCapacity) currentDoctorCount++;
    else cout << "  [Error] Department has reached its capacity.\n";
}

void Department::removeDoctor() {
    if (currentDoctorCount > 0) currentDoctorCount--;
}

void Department::displayDetails() const {
    cout << "\n  +-----------------------------------------+\n";
    cout << "  |          DEPARTMENT DETAILS             |\n";
    cout << "  +-----------------------------------------+\n";
    cout << "  | Dept ID      : " << left << setw(25) << departmentID   << "|\n";
    cout << "  | Name         : " << left << setw(25) << departmentName << "|\n";
    cout << "  | Floor        : " << left << setw(25) << floorLocation  << "|\n";
    cout << "  | Head Doctor  : " << left << setw(25) << headDoctorID   << "|\n";
    cout << "  | Capacity     : " << left << setw(25) << doctorCapacity << "|\n";
    cout << "  | Doctors      : " << left << setw(25) << currentDoctorCount << "|\n";
    cout << "  +-----------------------------------------+\n";
}

void Department::displayRow() const {
    cout << "  | " << left << setw(7)  << departmentID
         << "| " << setw(20) << departmentName
         << "| " << setw(10) << floorLocation
         << "| " << currentDoctorCount << "/" << doctorCapacity << "\n";
}
