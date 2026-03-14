#include "Appointment.h"
#include <iostream>
#include <iomanip>
using namespace std;

Appointment::Appointment() {
    appointmentID     = "AP000";
    patientID         = "NONE";
    patientName       = "Unknown";
    assignedDoctor    = nullptr;
    appointmentDate   = "0000-00-00";
    appointmentTime   = "00:00";
    visitReason       = "Not specified";
    appointmentStatus = "Scheduled";
}

Appointment::Appointment(string apptID, string patID, string patName, Doctor* doctor,
                         string date, string time, string reason) {
    appointmentID     = apptID;
    patientID         = patID;
    patientName       = patName;
    assignedDoctor    = doctor;
    appointmentDate   = date;
    appointmentTime   = time;
    visitReason       = reason;
    appointmentStatus = "Scheduled";
}

Appointment::Appointment(const Appointment& other) {
    appointmentID     = other.appointmentID;
    patientID         = other.patientID;
    patientName       = other.patientName;
    assignedDoctor    = other.assignedDoctor;
    appointmentDate   = other.appointmentDate;
    appointmentTime   = other.appointmentTime;
    visitReason       = other.visitReason;
    appointmentStatus = other.appointmentStatus;
}

Appointment::~Appointment() { assignedDoctor = nullptr; }

string  Appointment::getAppointmentID()     const { return appointmentID; }
string  Appointment::getPatientID()         const { return patientID; }
string  Appointment::getPatientName()       const { return patientName; }
Doctor* Appointment::getAssignedDoctor()    const { return assignedDoctor; }
string  Appointment::getAppointmentDate()   const { return appointmentDate; }
string  Appointment::getAppointmentTime()   const { return appointmentTime; }
string  Appointment::getVisitReason()       const { return visitReason; }
string  Appointment::getAppointmentStatus() const { return appointmentStatus; }

void Appointment::setAppointmentDate(const string& date)     { appointmentDate = date; }
void Appointment::setAppointmentTime(const string& time)     { appointmentTime = time; }
void Appointment::setVisitReason(const string& reason)       { visitReason = reason; }
void Appointment::setAppointmentStatus(const string& status) { appointmentStatus = status; }

bool Appointment::cancelAppointment() {
    if (appointmentStatus == "Scheduled") {
        appointmentStatus = "Cancelled";
        return true;
    }
    return false;
}

bool Appointment::completeAppointment() {
    if (appointmentStatus == "Scheduled") {
        appointmentStatus = "Completed";
        return true;
    }
    return false;
}

void Appointment::displayDetails() const {
    string doctorDisplay = assignedDoctor ? ("Dr. " + assignedDoctor->getDoctorName()) : "Not Assigned";
    string specDisplay   = assignedDoctor ? assignedDoctor->getSpecialization() : "N/A";
    cout << "\n  +------------------------------------------+\n";
    cout << "  |          APPOINTMENT DETAILS             |\n";
    cout << "  +------------------------------------------+\n";
    cout << "  | Appointment ID : " << left << setw(24) << appointmentID    << "|\n";
    cout << "  | Patient ID     : " << left << setw(24) << patientID        << "|\n";
    cout << "  | Patient Name   : " << left << setw(24) << patientName      << "|\n";
    cout << "  | Doctor         : " << left << setw(24) << doctorDisplay    << "|\n";
    cout << "  | Specialization : " << left << setw(24) << specDisplay      << "|\n";
    cout << "  | Date           : " << left << setw(24) << appointmentDate  << "|\n";
    cout << "  | Time           : " << left << setw(24) << appointmentTime  << "|\n";
    cout << "  | Reason         : " << left << setw(24) << visitReason      << "|\n";
    cout << "  | Status         : " << left << setw(24) << appointmentStatus << "|\n";
    cout << "  +------------------------------------------+\n";
}

void Appointment::displayRow() const {
    string doctorName = assignedDoctor ? assignedDoctor->getDoctorName() : "N/A";
    cout << "  | " << left << setw(7)  << appointmentID
         << "| " << setw(7)  << patientID
         << "| " << setw(16) << patientName
         << "| " << setw(16) << doctorName
         << "| " << setw(11) << appointmentDate
         << "| " << setw(6)  << appointmentTime
         << "| " << setw(10) << appointmentStatus << "|\n";
}
