#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H
#include <string>
using namespace std;

class MedicalRecord {
private:
    string recordID;
    string patientID;
    string doctorID;
    string visitDate;
    string diagnosisDetails;
    string prescribedMedicine;
    string doctorNotes;
    string followUpDate;

public:
    MedicalRecord();
    MedicalRecord(string recID, string patID, string docID, string date,
                  string diagnosis, string medicine, string notes, string followUp);
    MedicalRecord(const MedicalRecord& other);
    ~MedicalRecord();

    string getRecordID()           const;
    string getPatientID()          const;
    string getDoctorID()           const;
    string getVisitDate()          const;
    string getDiagnosisDetails()   const;
    string getPrescribedMedicine() const;
    string getDoctorNotes()        const;
    string getFollowUpDate()       const;

    void setDiagnosisDetails(const string& diagnosis);
    void setPrescribedMedicine(const string& medicine);
    void setDoctorNotes(const string& notes);
    void setFollowUpDate(const string& date);

    void displayDetails() const;
    void displayRow()     const;
};

#endif
