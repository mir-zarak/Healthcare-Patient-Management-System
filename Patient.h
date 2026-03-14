#ifndef PATIENT_H
#define PATIENT_H
#include <string>
using namespace std;

class Patient {
private:
    string patientID;
    string patientName;
    int    patientAge;
    string patientPhone;
    string bloodGroup;
    string currentCondition;
    bool   isActive;

public:
    Patient();
    Patient(string id, string name, int age, string phone, string blood, string condition);
    Patient(const Patient& other);
    ~Patient();

    string getPatientID()        const;
    string getPatientName()      const;
    int    getPatientAge()       const;
    string getPatientPhone()     const;
    string getBloodGroup()       const;
    string getCurrentCondition() const;
    bool   getIsActive()         const;

    void setPatientName(const string& name);
    void setPatientAge(int age);
    void setPatientPhone(const string& phone);
    void setBloodGroup(const string& blood);
    void setCurrentCondition(const string& condition);
    void setIsActive(bool status);

    void displayDetails() const;
    void displayRow()     const;
};

#endif
