#ifndef DOCTOR_H
#define DOCTOR_H
#include <string>
using namespace std;

class Doctor {
private:
    string doctorID;
    string doctorName;
    string specialization;
    string doctorPhone;
    string departmentID;
    bool   isAvailable;
    int    totalAppointments;

public:
    Doctor();
    Doctor(string id, string name, string spec, string phone, string deptID);
    Doctor(const Doctor& other);
    ~Doctor();

    string getDoctorID()          const;
    string getDoctorName()        const;
    string getSpecialization()    const;
    string getDoctorPhone()       const;
    string getDepartmentID()      const;
    bool   getIsAvailable()       const;
    int    getTotalAppointments() const;

    void setDoctorName(const string& name);
    void setSpecialization(const string& spec);
    void setDoctorPhone(const string& phone);
    void setDepartmentID(const string& deptID);
    void setIsAvailable(bool status);
    void incrementAppointments();

    void displayDetails() const;
    void displayRow()     const;
};

#endif
