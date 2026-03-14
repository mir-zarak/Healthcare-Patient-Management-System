#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <string>
using namespace std;

class Department {
private:
    string departmentID;
    string departmentName;
    string floorLocation;
    string headDoctorID;
    int    doctorCapacity;
    int    currentDoctorCount;

public:
    Department();
    Department(string id, string name, string floor, int capacity);
    Department(const Department& other);
    ~Department();

    string getDepartmentID()       const;
    string getDepartmentName()     const;
    string getFloorLocation()      const;
    string getHeadDoctorID()       const;
    int    getDoctorCapacity()     const;
    int    getCurrentDoctorCount() const;

    void setDepartmentName(const string& name);
    void setFloorLocation(const string& floor);
    void setHeadDoctorID(const string& id);
    void addDoctor();
    void removeDoctor();

    void displayDetails() const;
    void displayRow()     const;
};

#endif
