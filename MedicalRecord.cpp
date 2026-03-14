#include "MedicalRecord.h"
#include <iostream>
#include <iomanip>
using namespace std;

MedicalRecord::MedicalRecord() {
    recordID           = "RC000";
    patientID          = "NONE";
    doctorID           = "NONE";
    visitDate          = "0000-00-00";
    diagnosisDetails   = "Not provided";
    prescribedMedicine = "None";
    doctorNotes        = "None";
    followUpDate       = "N/A";
}

MedicalRecord::MedicalRecord(string recID, string patID, string docID, string date,
                             string diagnosis, string medicine, string notes, string followUp) {
    recordID           = recID;
    patientID          = patID;
    doctorID           = docID;
    visitDate          = date;
    diagnosisDetails   = diagnosis;
    prescribedMedicine = medicine;
    doctorNotes        = notes;
    followUpDate       = followUp;
}

MedicalRecord::MedicalRecord(const MedicalRecord& other) {
    recordID           = other.recordID;
    patientID          = other.patientID;
    doctorID           = other.doctorID;
    visitDate          = other.visitDate;
    diagnosisDetails   = other.diagnosisDetails;
    prescribedMedicine = other.prescribedMedicine;
    doctorNotes        = other.doctorNotes;
    followUpDate       = other.followUpDate;
}

MedicalRecord::~MedicalRecord() {}

string MedicalRecord::getRecordID()           const { return recordID; }
string MedicalRecord::getPatientID()          const { return patientID; }
string MedicalRecord::getDoctorID()           const { return doctorID; }
string MedicalRecord::getVisitDate()          const { return visitDate; }
string MedicalRecord::getDiagnosisDetails()   const { return diagnosisDetails; }
string MedicalRecord::getPrescribedMedicine() const { return prescribedMedicine; }
string MedicalRecord::getDoctorNotes()        const { return doctorNotes; }
string MedicalRecord::getFollowUpDate()       const { return followUpDate; }

void MedicalRecord::setDiagnosisDetails(const string& diagnosis) {
    if (!diagnosis.empty()) diagnosisDetails = diagnosis;
    else cout << "  [Error] Diagnosis cannot be empty.\n";
}

void MedicalRecord::setPrescribedMedicine(const string& medicine) {
    prescribedMedicine = medicine;
}

void MedicalRecord::setDoctorNotes(const string& notes) {
    doctorNotes = notes;
}

void MedicalRecord::setFollowUpDate(const string& date) {
    followUpDate = date;
}

void MedicalRecord::displayDetails() const {
    cout << "\n  +------------------------------------------+\n";
    cout << "  |          MEDICAL RECORD DETAILS          |\n";
    cout << "  +------------------------------------------+\n";
    cout << "  | Record ID   : " << left << setw(27) << recordID           << "|\n";
    cout << "  | Patient ID  : " << left << setw(27) << patientID          << "|\n";
    cout << "  | Doctor ID   : " << left << setw(27) << doctorID           << "|\n";
    cout << "  | Visit Date  : " << left << setw(27) << visitDate          << "|\n";
    cout << "  | Diagnosis   : " << left << setw(27) << diagnosisDetails   << "|\n";
    cout << "  | Medicine    : " << left << setw(27) << prescribedMedicine << "|\n";
    cout << "  | Notes       : " << left << setw(27) << doctorNotes        << "|\n";
    cout << "  | Follow Up   : " << left << setw(27) << followUpDate       << "|\n";
    cout << "  +------------------------------------------+\n";
}

void MedicalRecord::displayRow() const {
    cout << "  | " << left << setw(7)  << recordID
         << "| " << setw(8)  << patientID
         << "| " << setw(22) << diagnosisDetails
         << "| " << setw(11) << visitDate
         << "| " << setw(11) << followUpDate << "|\n";
}
