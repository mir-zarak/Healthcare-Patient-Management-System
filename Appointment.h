#ifndef APPOINTMENT_H
#define APPOINTMENT_H
#include <string>
#include "Doctor.h"
using namespace std;

class Appointment {
private:
    string  appointmentID;
    string  patientID;
    string  patientName;
    Doctor* assignedDoctor;
    string  appointmentDate;
    string  appointmentTime;
    string  visitReason;
    string  appointmentStatus;

public:
    Appointment();
    Appointment(string apptID, string patID, string patName, Doctor* doctor,
                string date, string time, string reason);
    Appointment(const Appointment& other);
    ~Appointment();

    string  getAppointmentID()     const;
    string  getPatientID()         const;
    string  getPatientName()       const;
    Doctor* getAssignedDoctor()    const;
    string  getAppointmentDate()   const;
    string  getAppointmentTime()   const;
    string  getVisitReason()       const;
    string  getAppointmentStatus() const;

    void setAppointmentDate(const string& date);
    void setAppointmentTime(const string& time);
    void setVisitReason(const string& reason);
    void setAppointmentStatus(const string& status);

    bool cancelAppointment();
    bool completeAppointment();

    void displayDetails() const;
    void displayRow()     const;
};

#endif
