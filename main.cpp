#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "Patient.h"
#include "Doctor.h"
#include "Appointment.h"
#include "MedicalRecord.h"
#include "Bill.h"
#include "Department.h"
#include "User.h"
using namespace std;

const int MAX_RECORDS = 50;

Patient*      patientList[MAX_RECORDS];
Doctor*       doctorList[MAX_RECORDS];
Appointment*  appointmentList[MAX_RECORDS];
MedicalRecord* medicalRecordList[MAX_RECORDS];
Bill*         billList[MAX_RECORDS];
Department*   departmentList[MAX_RECORDS];
User*         userList[MAX_RECORDS];

int totalPatients     = 0;
int totalDoctors      = 0;
int totalAppointments = 0;
int totalRecords      = 0;
int totalBills        = 0;
int totalDepartments  = 0;
int totalUsers        = 0;

int patientCounter     = 1;
int doctorCounter      = 1;
int appointmentCounter = 1;
int recordCounter      = 1;
int billCounter        = 1;
int departmentCounter  = 1;

User* currentUser = nullptr;

string generateID(const string& prefix, int counter) {
    string num = to_string(counter);
    while ((int)num.size() < 3) num = "0" + num;
    return prefix + num;
}

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void waitForEnter() {
    cout << "\n  Press Enter to continue...";
    clearInputBuffer();
}

int readInteger(const string& prompt) {
    int value;
    while (true) {
        cout << "  " << prompt;
        if (cin >> value) { clearInputBuffer(); return value; }
        cout << "  [Error] Please enter a valid number.\n";
        cin.clear(); clearInputBuffer();
    }
}

double readDouble(const string& prompt) {
    double value;
    while (true) {
        cout << "  " << prompt;
        if (cin >> value && value >= 0) { clearInputBuffer(); return value; }
        cout << "  [Error] Please enter a valid non-negative number.\n";
        cin.clear(); clearInputBuffer();
    }
}

string readString(const string& prompt) {
    string value;
    cout << "  " << prompt;
    getline(cin, value);
    return value;
}

void printSectionHeader(const string& title) {
    int width = 48;
    int padding = (width - (int)title.size()) / 2;
    cout << "\n  +" << string(width, '-') << "+\n";
    cout << "  |" << string(padding, ' ') << title
         << string(width - padding - (int)title.size(), ' ') << "|\n";
    cout << "  +" << string(width, '-') << "+\n";
}

bool checkUserAccess(const string& feature) {
    if (!currentUser || !currentUser->getIsLoggedIn()) {
        cout << "\n  [Access Denied] You must be logged in first.\n";
        return false;
    }
    if (!currentUser->hasAccess(feature)) {
        cout << "\n  [Access Denied] Your role (" << currentUser->getUserRole()
             << ") cannot perform this action.\n";
        return false;
    }
    return true;
}

Patient* findPatientByID(const string& patientID) {
    for (int i = 0; i < totalPatients; i++)
        if (patientList[i]->getPatientID() == patientID && patientList[i]->getIsActive())
            return patientList[i];
    return nullptr;
}

Doctor* findDoctorByID(const string& doctorID) {
    for (int i = 0; i < totalDoctors; i++)
        if (doctorList[i]->getDoctorID() == doctorID)
            return doctorList[i];
    return nullptr;
}

Department* findDepartmentByID(const string& departmentID) {
    for (int i = 0; i < totalDepartments; i++)
        if (departmentList[i]->getDepartmentID() == departmentID)
            return departmentList[i];
    return nullptr;
}

Bill* findBillByID(const string& billID) {
    for (int i = 0; i < totalBills; i++)
        if (billList[i]->getBillID() == billID)
            return billList[i];
    return nullptr;
}

void freeAllMemory() {
    for (int i = 0; i < totalPatients; i++)     { delete patientList[i];       patientList[i]       = nullptr; }
    for (int i = 0; i < totalDoctors; i++)      { delete doctorList[i];        doctorList[i]        = nullptr; }
    for (int i = 0; i < totalAppointments; i++) { delete appointmentList[i];   appointmentList[i]   = nullptr; }
    for (int i = 0; i < totalRecords; i++)      { delete medicalRecordList[i]; medicalRecordList[i] = nullptr; }
    for (int i = 0; i < totalBills; i++)        { delete billList[i];          billList[i]          = nullptr; }
    for (int i = 0; i < totalDepartments; i++)  { delete departmentList[i];    departmentList[i]    = nullptr; }
    for (int i = 0; i < totalUsers; i++)        { delete userList[i];          userList[i]          = nullptr; }
}

void loadInitialData() {
    userList[totalUsers++] = new User("admin",   "admin123", "admin");
    userList[totalUsers++] = new User("drali",   "doc123",   "doctor");
    userList[totalUsers++] = new User("rfront",  "rec123",   "receptionist");

    departmentList[totalDepartments++] = new Department("DP001", "Cardiology",   "Block A, Floor 2", 8);
    departmentList[totalDepartments++] = new Department("DP002", "Orthopedics",  "Block B, Floor 1", 6);
    departmentList[totalDepartments++] = new Department("DP003", "General Ward", "Block A, Floor 1", 12);

    doctorList[totalDoctors++] = new Doctor("DR001", "Ali Raza",    "Cardiologist",       "0300-1234567", "DP001");
    doctorList[totalDoctors++] = new Doctor("DR002", "Sara Malik",  "Orthopedic Surgeon", "0311-9876543", "DP002");
    doctorList[totalDoctors++] = new Doctor("DR003", "Hamza Tariq", "General Physician",  "0321-5556677", "DP003");

    for (int i = 0; i < totalDepartments; i++) departmentList[i]->addDoctor();

    patientList[totalPatients++] = new Patient("PT001", "Ahmed Khan",  32, "0333-1234567", "B+", "Hypertension");
    patientList[totalPatients++] = new Patient("PT002", "Fatima Noor", 25, "0344-2345678", "A+", "None");
    patientList[totalPatients++] = new Patient("PT003", "Usman Ghani", 48, "0355-3456789", "O-", "Diabetes");

    patientCounter = 4; doctorCounter = 4; departmentCounter = 4;

    appointmentList[totalAppointments] = new Appointment(
        "AP001", "PT001", "Ahmed Khan", doctorList[0], "2026-02-25", "09:00", "Chest pain checkup");
    doctorList[0]->incrementAppointments(); totalAppointments++;

    appointmentList[totalAppointments] = new Appointment(
        "AP002", "PT002", "Fatima Noor", doctorList[1], "2026-02-25", "11:00", "Knee pain");
    doctorList[1]->incrementAppointments(); totalAppointments++;

    appointmentCounter = 3;

    medicalRecordList[totalRecords++] = new MedicalRecord(
        "RC001", "PT001", "DR001", "2026-01-10",
        "Hypertension Stage 1", "Amlodipine 5mg", "Monitor BP daily", "2026-02-10");
    recordCounter = 2;

    billList[totalBills++] = new Bill("BL001", "PT001", "Ahmed Khan",  1200.0, 800.0, 500.0, "2026-01-10");
    billList[0]->recordPayment(1500.0);
    billList[totalBills++] = new Bill("BL002", "PT003", "Usman Ghani", 1000.0, 1500.0, 700.0, "2026-02-01");
    billCounter = 3;
}

void handleLogin() {
    printSectionHeader("USER LOGIN");
    string enteredUsername = readString("Username : ");
    string enteredPassword = readString("Password : ");
    for (int i = 0; i < totalUsers; i++) {
        if (userList[i]->getUsername() == enteredUsername) {
            if (userList[i]->login(enteredUsername, enteredPassword))
                currentUser = userList[i];
            return;
        }
    }
    cout << "\n  User not found in the system.\n";
}

void handleLogout() {
    if (currentUser && currentUser->getIsLoggedIn()) {
        currentUser->logout();
        currentUser = nullptr;
    } else {
        cout << "\n  No user is currently logged in.\n";
    }
}

void showValidationDemo() {
    printSectionHeader("DATA VALIDATION DEMO");
    cout << "\n  Testing validation rules:\n\n";
    Patient tempPatient;
    cout << "  setPatientAge(-5)       -> "; tempPatient.setPatientAge(-5);
    cout << "  setPatientPhone(\"12\")   -> "; tempPatient.setPatientPhone("12");
    Bill tempBill;
    cout << "  setConsultationFee(-100)-> "; tempBill.setConsultationFee(-100);
    cout << "\n  All validations are working correctly.\n";
    waitForEnter();
}

void showPrivacyInfo() {
    printSectionHeader("PRIVACY & ENCAPSULATION INFO");
    cout << "\n  All class data members are declared private.\n";
    cout << "  External access is only through validated public getters/setters.\n\n";
    cout << "  Example:\n";
    cout << "    patient.patientID         <- NOT ALLOWED (private member)\n";
    cout << "    patient.getPatientID()    <- ALLOWED (public getter)\n";
    cout << "    patient.setPatientAge(-5) <- REJECTED by setter validation\n\n";
    cout << "  Role-based access control:\n";
    cout << "    admin        -> Full access to all features\n";
    cout << "    doctor       -> Patients, records, appointments\n";
    cout << "    receptionist -> Patients, appointments, billing\n";
    waitForEnter();
}

void addNewPatient() {
    if (!checkUserAccess("add_patient")) return;
    printSectionHeader("ADD NEW PATIENT");
    string newID    = generateID("PT", patientCounter++);
    string name     = readString("Full Name    : ");
    int    age      = readInteger("Age          : ");
    string phone    = readString("Phone        : ");
    string blood    = readString("Blood Group  : ");
    string cond     = readString("Condition    : ");
    if (totalPatients >= MAX_RECORDS) { cout << "  Patient list is full.\n"; return; }
    patientList[totalPatients++] = new Patient(newID, name, age, phone, blood, cond);
    cout << "\n  Patient added successfully. Assigned ID: " << newID << "\n";
    waitForEnter();
}

void viewPatientDetails() {
    if (!checkUserAccess("view_patient")) return;
    printSectionHeader("VIEW PATIENT DETAILS");
    string searchID = readString("Enter Patient ID : ");
    Patient* found = findPatientByID(searchID);
    if (found) found->displayDetails();
    else cout << "\n  No active patient found with ID: " << searchID << "\n";
    waitForEnter();
}

void updatePatientInfo() {
    if (!checkUserAccess("update_patient")) return;
    printSectionHeader("UPDATE PATIENT INFO");
    string searchID = readString("Enter Patient ID : ");
    Patient* found = findPatientByID(searchID);
    if (!found) { cout << "\n  Patient not found.\n"; waitForEnter(); return; }
    cout << "\n  1. Name    2. Age    3. Phone    4. Blood Group    5. Condition\n";
    int choice = readInteger("Choose field to update : ");
    switch (choice) {
        case 1: found->setPatientName(readString("New Name        : ")); break;
        case 2: found->setPatientAge(readInteger("New Age         : ")); break;
        case 3: found->setPatientPhone(readString("New Phone       : ")); break;
        case 4: found->setBloodGroup(readString("New Blood Group : ")); break;
        case 5: found->setCurrentCondition(readString("New Condition   : ")); break;
        default: cout << "  Invalid option.\n"; return;
    }
    cout << "\n  Patient record updated successfully.\n";
    waitForEnter();
}

void removePatient() {
    if (!checkUserAccess("add_patient")) return;
    printSectionHeader("REMOVE PATIENT");
    string searchID = readString("Enter Patient ID : ");
    Patient* found = findPatientByID(searchID);
    if (!found) { cout << "\n  Patient not found.\n"; waitForEnter(); return; }
    found->setIsActive(false);
    cout << "\n  Patient " << searchID << " has been deactivated.\n";
    waitForEnter();
}

void searchForPatient() {
    if (!checkUserAccess("view_patient")) return;
    printSectionHeader("SEARCH PATIENT");
    cout << "\n  1. Search by ID    2. Search by Name\n";
    int choice  = readInteger("Choice : ");
    string term = readString("Search term : ");
    cout << "\n  +---------+---------------------+-----+-------+---------------+----------+\n";
    cout << "  | Pat. ID | Name                | Age | Blood | Phone         | Status   |\n";
    cout << "  +---------+---------------------+-----+-------+---------------+----------+\n";
    bool anyFound = false;
    for (int i = 0; i < totalPatients; i++) {
        bool matched = (choice == 1 && patientList[i]->getPatientID() == term) ||
                       (choice == 2 && patientList[i]->getPatientName().find(term) != string::npos);
        if (matched && patientList[i]->getIsActive()) {
            patientList[i]->displayRow();
            anyFound = true;
        }
    }
    cout << "  +---------+---------------------+-----+-------+---------------+----------+\n";
    if (!anyFound) cout << "\n  No matching patients found.\n";
    waitForEnter();
}

void listAllPatients() {
    if (!checkUserAccess("view_patient")) return;
    printSectionHeader("ALL PATIENTS");
    cout << "\n  +---------+---------------------+-----+-------+---------------+----------+\n";
    cout << "  | Pat. ID | Name                | Age | Blood | Phone         | Status   |\n";
    cout << "  +---------+---------------------+-----+-------+---------------+----------+\n";
    int activeCount = 0;
    for (int i = 0; i < totalPatients; i++) {
        if (patientList[i]->getIsActive()) { patientList[i]->displayRow(); activeCount++; }
    }
    cout << "  +---------+---------------------+-----+-------+---------------+----------+\n";
    cout << "  Total active patients: " << activeCount << "\n";
    waitForEnter();
}

void addNewDoctor() {
    if (!checkUserAccess("add_patient")) return;
    printSectionHeader("ADD NEW DOCTOR");
    string newID  = generateID("DR", doctorCounter++);
    string name   = readString("Full Name       : ");
    string spec   = readString("Specialization  : ");
    string phone  = readString("Phone           : ");
    string deptID = readString("Department ID   : ");
    if (totalDoctors >= MAX_RECORDS) { cout << "  Doctor list is full.\n"; return; }
    doctorList[totalDoctors++] = new Doctor(newID, name, spec, phone, deptID);
    Department* dept = findDepartmentByID(deptID);
    if (dept) dept->addDoctor();
    cout << "\n  Doctor added successfully. Assigned ID: " << newID << "\n";
    waitForEnter();
}

void viewDoctorDetails() {
    if (!checkUserAccess("view_patient")) return;
    printSectionHeader("VIEW DOCTOR DETAILS");
    string searchID = readString("Enter Doctor ID : ");
    Doctor* found = findDoctorByID(searchID);
    if (found) found->displayDetails();
    else cout << "\n  Doctor not found with ID: " << searchID << "\n";
    waitForEnter();
}

void updateDoctorInfo() {
    if (!checkUserAccess("add_patient")) return;
    printSectionHeader("UPDATE DOCTOR INFO");
    string searchID = readString("Enter Doctor ID : ");
    Doctor* found = findDoctorByID(searchID);
    if (!found) { cout << "\n  Doctor not found.\n"; waitForEnter(); return; }
    cout << "\n  1. Name    2. Specialization    3. Phone    4. Availability\n";
    int choice = readInteger("Choose field to update : ");
    switch (choice) {
        case 1: found->setDoctorName(readString("New Name           : ")); break;
        case 2: found->setSpecialization(readString("New Specialization : ")); break;
        case 3: found->setDoctorPhone(readString("New Phone          : ")); break;
        case 4: {
            int val = readInteger("Available? (1 = Yes, 0 = No) : ");
            found->setIsAvailable(val == 1);
            break;
        }
        default: cout << "  Invalid option.\n"; return;
    }
    cout << "\n  Doctor record updated successfully.\n";
    waitForEnter();
}

void removeDoctor() {
    if (!checkUserAccess("add_patient")) return;
    printSectionHeader("REMOVE DOCTOR");
    string searchID = readString("Enter Doctor ID : ");
    for (int i = 0; i < totalDoctors; i++) {
        if (doctorList[i]->getDoctorID() == searchID) {
            Department* dept = findDepartmentByID(doctorList[i]->getDepartmentID());
            if (dept) dept->removeDoctor();
            cout << "\n  Removed Dr. " << doctorList[i]->getDoctorName() << " from the system.\n";
            delete doctorList[i];
            for (int j = i; j < totalDoctors - 1; j++) doctorList[j] = doctorList[j + 1];
            doctorList[--totalDoctors] = nullptr;
            waitForEnter(); return;
        }
    }
    cout << "\n  Doctor not found.\n";
    waitForEnter();
}

void searchForDoctor() {
    if (!checkUserAccess("view_patient")) return;
    printSectionHeader("SEARCH DOCTOR");
    cout << "\n  1. By ID    2. By Name    3. By Specialization\n";
    int choice  = readInteger("Choice : ");
    string term = readString("Search term : ");
    cout << "\n  +---------+---------------------+-----------------------+--------------+-----------+\n";
    cout << "  | Doc. ID | Name                | Specialization        | Phone        | Status    |\n";
    cout << "  +---------+---------------------+-----------------------+--------------+-----------+\n";
    bool anyFound = false;
    for (int i = 0; i < totalDoctors; i++) {
        bool matched = (choice == 1 && doctorList[i]->getDoctorID() == term) ||
                       (choice == 2 && doctorList[i]->getDoctorName().find(term) != string::npos) ||
                       (choice == 3 && doctorList[i]->getSpecialization().find(term) != string::npos);
        if (matched) { doctorList[i]->displayRow(); anyFound = true; }
    }
    cout << "  +---------+---------------------+-----------------------+--------------+-----------+\n";
    if (!anyFound) cout << "\n  No matching doctors found.\n";
    waitForEnter();
}

void listAllDoctors() {
    if (!checkUserAccess("view_patient")) return;
    printSectionHeader("ALL DOCTORS");
    cout << "\n  +---------+---------------------+-----------------------+--------------+-----------+\n";
    cout << "  | Doc. ID | Name                | Specialization        | Phone        | Status    |\n";
    cout << "  +---------+---------------------+-----------------------+--------------+-----------+\n";
    for (int i = 0; i < totalDoctors; i++) doctorList[i]->displayRow();
    cout << "  +---------+---------------------+-----------------------+--------------+-----------+\n";
    cout << "  Total doctors: " << totalDoctors << "\n";
    waitForEnter();
}

void checkDoctorAvailability() {
    if (!checkUserAccess("view_patient")) return;
    printSectionHeader("CHECK DOCTOR AVAILABILITY");
    string searchID = readString("Enter Doctor ID : ");
    Doctor* found = findDoctorByID(searchID);
    if (!found) { cout << "\n  Doctor not found.\n"; waitForEnter(); return; }
    cout << "\n  Dr. " << found->getDoctorName() << " (" << found->getSpecialization() << ")\n";
    cout << "  Status: " << (found->getIsAvailable() ? "AVAILABLE" : "NOT AVAILABLE") << "\n";
    waitForEnter();
}

void bookNewAppointment() {
    if (!checkUserAccess("book_appt")) return;
    printSectionHeader("BOOK APPOINTMENT");
    string patientID = readString("Patient ID         : ");
    Patient* patient = findPatientByID(patientID);
    if (!patient) { cout << "\n  Patient not found.\n"; waitForEnter(); return; }

    string doctorID = readString("Doctor ID          : ");
    Doctor* doctor = findDoctorByID(doctorID);
    if (!doctor) { cout << "\n  Doctor not found.\n"; waitForEnter(); return; }
    if (!doctor->getIsAvailable()) {
        cout << "\n  Dr. " << doctor->getDoctorName() << " is currently not available.\n";
        waitForEnter(); return;
    }

    string apptDate   = readString("Date (YYYY-MM-DD)  : ");
    string apptTime   = readString("Time (HH:MM)       : ");
    string visitReason = readString("Reason for Visit   : ");

    if (totalAppointments >= MAX_RECORDS) { cout << "  Appointment list is full.\n"; return; }
    string newID = generateID("AP", appointmentCounter++);
    appointmentList[totalAppointments++] = new Appointment(
        newID, patientID, patient->getPatientName(), doctor, apptDate, apptTime, visitReason);
    doctor->incrementAppointments();
    cout << "\n  Appointment booked successfully. ID: " << newID << "\n";
    waitForEnter();
}

void viewAppointmentDetails() {
    if (!checkUserAccess("view_appt")) return;
    printSectionHeader("VIEW APPOINTMENT DETAILS");
    string searchID = readString("Enter Appointment ID : ");
    for (int i = 0; i < totalAppointments; i++) {
        if (appointmentList[i]->getAppointmentID() == searchID) {
            appointmentList[i]->displayDetails();
            waitForEnter(); return;
        }
    }
    cout << "\n  Appointment not found with ID: " << searchID << "\n";
    waitForEnter();
}

void rescheduleAppointment() {
    if (!checkUserAccess("book_appt")) return;
    printSectionHeader("RESCHEDULE APPOINTMENT");
    string searchID = readString("Enter Appointment ID : ");
    for (int i = 0; i < totalAppointments; i++) {
        if (appointmentList[i]->getAppointmentID() == searchID) {
            if (appointmentList[i]->getAppointmentStatus() != "Scheduled") {
                cout << "\n  Cannot reschedule. Current status: "
                     << appointmentList[i]->getAppointmentStatus() << "\n";
                waitForEnter(); return;
            }
            appointmentList[i]->setAppointmentDate(readString("New Date (YYYY-MM-DD) : "));
            appointmentList[i]->setAppointmentTime(readString("New Time (HH:MM)      : "));
            cout << "\n  Appointment rescheduled successfully.\n";
            waitForEnter(); return;
        }
    }
    cout << "\n  Appointment not found.\n";
    waitForEnter();
}

void cancelAppointment() {
    if (!checkUserAccess("cancel_appt")) return;
    printSectionHeader("CANCEL APPOINTMENT");
    string searchID = readString("Enter Appointment ID : ");
    for (int i = 0; i < totalAppointments; i++) {
        if (appointmentList[i]->getAppointmentID() == searchID) {
            if (appointmentList[i]->cancelAppointment())
                cout << "\n  Appointment " << searchID << " has been cancelled.\n";
            else
                cout << "\n  Cannot cancel. Status: "
                     << appointmentList[i]->getAppointmentStatus() << "\n";
            waitForEnter(); return;
        }
    }
    cout << "\n  Appointment not found.\n";
    waitForEnter();
}

void listPatientAppointments() {
    if (!checkUserAccess("view_appt")) return;
    printSectionHeader("PATIENT APPOINTMENTS");
    string searchID = readString("Enter Patient ID : ");
    cout << "\n  +---------+---------+-----------------+-----------------+------------+-------+-----------+\n";
    cout << "  | Appt ID | Pat. ID | Patient Name    | Doctor Name     | Date       | Time  | Status    |\n";
    cout << "  +---------+---------+-----------------+-----------------+------------+-------+-----------+\n";
    bool anyFound = false;
    for (int i = 0; i < totalAppointments; i++)
        if (appointmentList[i]->getPatientID() == searchID) {
            appointmentList[i]->displayRow(); anyFound = true;
        }
    cout << "  +---------+---------+-----------------+-----------------+------------+-------+-----------+\n";
    if (!anyFound) cout << "\n  No appointments found for patient " << searchID << "\n";
    waitForEnter();
}

void listDoctorAppointments() {
    if (!checkUserAccess("view_appt")) return;
    printSectionHeader("DOCTOR APPOINTMENTS");
    string searchID = readString("Enter Doctor ID : ");
    cout << "\n  +---------+---------+-----------------+-----------------+------------+-------+-----------+\n";
    cout << "  | Appt ID | Pat. ID | Patient Name    | Doctor Name     | Date       | Time  | Status    |\n";
    cout << "  +---------+---------+-----------------+-----------------+------------+-------+-----------+\n";
    bool anyFound = false;
    for (int i = 0; i < totalAppointments; i++) {
        Doctor* assignedDoc = appointmentList[i]->getAssignedDoctor();
        if (assignedDoc && assignedDoc->getDoctorID() == searchID) {
            appointmentList[i]->displayRow(); anyFound = true;
        }
    }
    cout << "  +---------+---------+-----------------+-----------------+------------+-------+-----------+\n";
    if (!anyFound) cout << "\n  No appointments found for doctor " << searchID << "\n";
    waitForEnter();
}

void viewDailySchedule() {
    if (!checkUserAccess("view_appt")) return;
    printSectionHeader("DAILY SCHEDULE");
    string targetDate = readString("Enter Date (YYYY-MM-DD) : ");
    cout << "\n  +---------+---------+-----------------+-----------------+------------+-------+-----------+\n";
    cout << "  | Appt ID | Pat. ID | Patient Name    | Doctor Name     | Date       | Time  | Status    |\n";
    cout << "  +---------+---------+-----------------+-----------------+------------+-------+-----------+\n";
    bool anyFound = false;
    for (int i = 0; i < totalAppointments; i++)
        if (appointmentList[i]->getAppointmentDate() == targetDate) {
            appointmentList[i]->displayRow(); anyFound = true;
        }
    cout << "  +---------+---------+-----------------+-----------------+------------+-------+-----------+\n";
    if (!anyFound) cout << "\n  No appointments scheduled for " << targetDate << "\n";
    waitForEnter();
}

void addMedicalRecord() {
    if (!checkUserAccess("add_record")) return;
    printSectionHeader("ADD MEDICAL RECORD");
    string patientID = readString("Patient ID          : ");
    if (!findPatientByID(patientID)) { cout << "\n  Patient not found.\n"; waitForEnter(); return; }
    string doctorID   = readString("Doctor ID           : ");
    string visitDate  = readString("Visit Date          : ");
    string diagnosis  = readString("Diagnosis           : ");
    string medicine   = readString("Prescribed Medicine : ");
    string notes      = readString("Doctor Notes        : ");
    string followUp   = readString("Follow-up Date      : ");
    if (totalRecords >= MAX_RECORDS) { cout << "  Records list is full.\n"; return; }
    string newID = generateID("RC", recordCounter++);
    medicalRecordList[totalRecords++] = new MedicalRecord(
        newID, patientID, doctorID, visitDate, diagnosis, medicine, notes, followUp);
    cout << "\n  Medical record added successfully. ID: " << newID << "\n";
    waitForEnter();
}

void viewPatientMedicalHistory() {
    if (!checkUserAccess("view_record")) return;
    printSectionHeader("PATIENT MEDICAL HISTORY");
    string patientID = readString("Enter Patient ID : ");
    bool anyFound = false;
    for (int i = 0; i < totalRecords; i++)
        if (medicalRecordList[i]->getPatientID() == patientID) {
            medicalRecordList[i]->displayDetails(); anyFound = true;
        }
    if (!anyFound) cout << "\n  No medical records found for patient " << patientID << "\n";
    waitForEnter();
}

void updateMedicalRecord() {
    if (!checkUserAccess("update_record")) return;
    printSectionHeader("UPDATE MEDICAL RECORD");
    string searchID = readString("Enter Record ID : ");
    for (int i = 0; i < totalRecords; i++) {
        if (medicalRecordList[i]->getRecordID() == searchID) {
            cout << "\n  1. Diagnosis    2. Medicine    3. Notes    4. Follow-up Date\n";
            int choice = readInteger("Choose field to update : ");
            switch (choice) {
                case 1: medicalRecordList[i]->setDiagnosisDetails(readString("New Diagnosis    : ")); break;
                case 2: medicalRecordList[i]->setPrescribedMedicine(readString("New Medicine     : ")); break;
                case 3: medicalRecordList[i]->setDoctorNotes(readString("New Notes        : ")); break;
                case 4: medicalRecordList[i]->setFollowUpDate(readString("New Follow-up    : ")); break;
                default: cout << "  Invalid option.\n"; return;
            }
            cout << "\n  Medical record updated successfully.\n";
            waitForEnter(); return;
        }
    }
    cout << "\n  Record not found.\n";
    waitForEnter();
}

void searchMedicalRecords() {
    if (!checkUserAccess("view_record")) return;
    printSectionHeader("SEARCH MEDICAL RECORDS");
    cout << "\n  1. By Diagnosis    2. By Visit Date\n";
    int choice  = readInteger("Choice : ");
    string term = readString("Search term : ");
    cout << "\n  +---------+---------+-----------------------+------------+------------+\n";
    cout << "  | Rec. ID | Pat. ID | Diagnosis             | Visit Date | Follow-Up  |\n";
    cout << "  +---------+---------+-----------------------+------------+------------+\n";
    bool anyFound = false;
    for (int i = 0; i < totalRecords; i++) {
        bool matched = (choice == 1 && medicalRecordList[i]->getDiagnosisDetails().find(term) != string::npos) ||
                       (choice == 2 && medicalRecordList[i]->getVisitDate() == term);
        if (matched) { medicalRecordList[i]->displayRow(); anyFound = true; }
    }
    cout << "  +---------+---------+-----------------------+------------+------------+\n";
    if (!anyFound) cout << "\n  No matching records found.\n";
    waitForEnter();
}

void generateNewBill() {
    if (!checkUserAccess("generate_bill")) return;
    printSectionHeader("GENERATE BILL");
    string patientID = readString("Patient ID           : ");
    Patient* patient = findPatientByID(patientID);
    if (!patient) { cout << "\n  Patient not found.\n"; waitForEnter(); return; }
    double consultationFee = readDouble("Consultation Fee (Rs.) : ");
    double labTestFee      = readDouble("Lab Test Fee     (Rs.) : ");
    double medicineFee     = readDouble("Medicine Fee     (Rs.) : ");
    string billDate        = readString("Bill Date              : ");
    if (totalBills >= MAX_RECORDS) { cout << "  Bill list is full.\n"; return; }
    string newID = generateID("BL", billCounter++);
    billList[totalBills++] = new Bill(
        newID, patientID, patient->getPatientName(),
        consultationFee, labTestFee, medicineFee, billDate);
    billList[totalBills - 1]->displayDetails();
    waitForEnter();
}

void viewBillDetails() {
    if (!checkUserAccess("view_bill")) return;
    printSectionHeader("VIEW BILL DETAILS");
    string searchID = readString("Enter Bill ID : ");
    Bill* found = findBillByID(searchID);
    if (found) found->displayDetails();
    else cout << "\n  Bill not found with ID: " << searchID << "\n";
    waitForEnter();
}

void processPayment() {
    if (!checkUserAccess("process_payment")) return;
    printSectionHeader("PROCESS PAYMENT");
    string searchID = readString("Enter Bill ID : ");
    Bill* found = findBillByID(searchID);
    if (!found) { cout << "\n  Bill not found.\n"; waitForEnter(); return; }
    cout << fixed << setprecision(2);
    cout << "\n  Remaining Balance: Rs. " << found->getRemainingBalance() << "\n";
    double paymentAmount = readDouble("Payment Amount (Rs.) : ");
    if (found->recordPayment(paymentAmount)) {
        cout << "\n  Payment of Rs. " << fixed << setprecision(2) << paymentAmount << " recorded.\n";
        cout << "  Remaining: Rs. " << found->getRemainingBalance()
             << "  |  Status: " << found->getPaymentStatus() << "\n";
    }
    waitForEnter();
}

void viewPatientPaymentHistory() {
    if (!checkUserAccess("view_bill")) return;
    printSectionHeader("PAYMENT HISTORY");
    string patientID = readString("Enter Patient ID : ");
    cout << "\n  +---------+---------+-----------------+----------+----------+----------+\n";
    cout << "  | Bill ID | Pat. ID | Patient Name    | Total    | Paid     | Status   |\n";
    cout << "  +---------+---------+-----------------+----------+----------+----------+\n";
    bool anyFound = false;
    double totalAmountPaid = 0;
    for (int i = 0; i < totalBills; i++) {
        if (billList[i]->getPatientID() == patientID) {
            billList[i]->displayRow();
            totalAmountPaid += billList[i]->getAmountPaid();
            anyFound = true;
        }
    }
    cout << "  +---------+---------+-----------------+----------+----------+----------+\n";
    if (anyFound)
        cout << "  Total amount paid: Rs. " << fixed << setprecision(2) << totalAmountPaid << "\n";
    else
        cout << "\n  No billing records found for patient " << patientID << "\n";
    waitForEnter();
}

void calculateTotalRevenue() {
    if (!checkUserAccess("add_patient")) return;
    printSectionHeader("TOTAL REVENUE");
    double totalBilled = 0, totalCollected = 0, totalPending = 0;
    for (int i = 0; i < totalBills; i++) {
        totalBilled    += billList[i]->getTotalBillAmount();
        totalCollected += billList[i]->getAmountPaid();
        totalPending   += billList[i]->getRemainingBalance();
    }
    cout << fixed << setprecision(2);
    cout << "\n  Total Billed    : Rs. " << totalBilled    << "\n";
    cout << "  Total Collected : Rs. " << totalCollected << "\n";
    cout << "  Total Pending   : Rs. " << totalPending   << "\n";
    waitForEnter();
}

void showPendingBills() {
    if (!checkUserAccess("view_bill")) return;
    printSectionHeader("PENDING BILLS");
    cout << "\n  +---------+---------+-----------------+----------+----------+----------+\n";
    cout << "  | Bill ID | Pat. ID | Patient Name    | Total    | Paid     | Status   |\n";
    cout << "  +---------+---------+-----------------+----------+----------+----------+\n";
    bool anyFound = false;
    for (int i = 0; i < totalBills; i++) {
        if (billList[i]->getPaymentStatus() != "Paid") { billList[i]->displayRow(); anyFound = true; }
    }
    cout << "  +---------+---------+-----------------+----------+----------+----------+\n";
    if (!anyFound) cout << "\n  No pending bills found.\n";
    waitForEnter();
}

void addNewDepartment() {
    if (!checkUserAccess("add_patient")) return;
    printSectionHeader("ADD DEPARTMENT");
    string newID    = generateID("DP", departmentCounter++);
    string name     = readString("Department Name : ");
    string floor    = readString("Floor Location  : ");
    int    capacity = readInteger("Doctor Capacity : ");
    if (totalDepartments >= MAX_RECORDS) { cout << "  Department list is full.\n"; return; }
    departmentList[totalDepartments++] = new Department(newID, name, floor, capacity);
    cout << "\n  Department added successfully. Assigned ID: " << newID << "\n";
    waitForEnter();
}

void assignDoctorToDepartment() {
    if (!checkUserAccess("add_patient")) return;
    printSectionHeader("ASSIGN DOCTOR TO DEPARTMENT");
    string doctorID     = readString("Doctor ID     : ");
    string departmentID = readString("Department ID : ");
    Doctor*     doctor = findDoctorByID(doctorID);
    Department* dept   = findDepartmentByID(departmentID);
    if (!doctor) { cout << "\n  Doctor not found.\n"; waitForEnter(); return; }
    if (!dept)   { cout << "\n  Department not found.\n"; waitForEnter(); return; }
    doctor->setDepartmentID(departmentID);
    dept->addDoctor();
    cout << "\n  Dr. " << doctor->getDoctorName()
         << " has been assigned to " << dept->getDepartmentName() << "\n";
    waitForEnter();
}

void viewDepartmentDetails() {
    if (!checkUserAccess("view_patient")) return;
    printSectionHeader("VIEW DEPARTMENT DETAILS");
    string searchID = readString("Enter Department ID : ");
    Department* found = findDepartmentByID(searchID);
    if (!found) { cout << "\n  Department not found.\n"; waitForEnter(); return; }
    found->displayDetails();
    cout << "\n  Doctors in this department:\n";
    cout << "  +---------+---------------------+-----------------------+--------------+-----------+\n";
    cout << "  | Doc. ID | Name                | Specialization        | Phone        | Status    |\n";
    cout << "  +---------+---------------------+-----------------------+--------------+-----------+\n";
    bool anyFound = false;
    for (int i = 0; i < totalDoctors; i++)
        if (doctorList[i]->getDepartmentID() == searchID) { doctorList[i]->displayRow(); anyFound = true; }
    cout << "  +---------+---------------------+-----------------------+--------------+-----------+\n";
    if (!anyFound) cout << "\n  No doctors assigned to this department.\n";
    waitForEnter();
}

void listAllDepartments() {
    if (!checkUserAccess("view_patient")) return;
    printSectionHeader("ALL DEPARTMENTS");
    cout << "\n  +---------+---------------------+-----------+--------+\n";
    cout << "  | Dept ID | Name                | Floor     | Docs   |\n";
    cout << "  +---------+---------------------+-----------+--------+\n";
    for (int i = 0; i < totalDepartments; i++) departmentList[i]->displayRow();
    cout << "  +---------+---------------------+-----------+--------+\n";
    cout << "  Total departments: " << totalDepartments << "\n";
    waitForEnter();
}

void generatePatientReport() {
    if (!checkUserAccess("view_patient")) return;
    printSectionHeader("PATIENT SUMMARY REPORT");
    int activeCount = 0, inactiveCount = 0;
    for (int i = 0; i < totalPatients; i++)
        patientList[i]->getIsActive() ? activeCount++ : inactiveCount++;
    cout << "\n  Total Registered : " << totalPatients  << "\n";
    cout << "  Active           : " << activeCount    << "\n";
    cout << "  Inactive         : " << inactiveCount  << "\n\n";
    cout << "  +---------+---------------------+-----+-------+---------------+----------+\n";
    cout << "  | Pat. ID | Name                | Age | Blood | Phone         | Status   |\n";
    cout << "  +---------+---------------------+-----+-------+---------------+----------+\n";
    for (int i = 0; i < totalPatients; i++) patientList[i]->displayRow();
    cout << "  +---------+---------------------+-----+-------+---------------+----------+\n";
    waitForEnter();
}

void generateDoctorReport() {
    if (!checkUserAccess("view_patient")) return;
    printSectionHeader("DOCTOR PERFORMANCE REPORT");
    cout << "\n  +---------+---------------------+-----------------------+--------------+\n";
    cout << "  | Doc. ID | Name                | Specialization        | Appointments |\n";
    cout << "  +---------+---------------------+-----------------------+--------------+\n";
    for (int i = 0; i < totalDoctors; i++) {
        cout << "  | " << left << setw(7)  << doctorList[i]->getDoctorID()
             << "| "   << setw(20) << doctorList[i]->getDoctorName()
             << "| "   << setw(22) << doctorList[i]->getSpecialization()
             << "| "   << setw(13) << doctorList[i]->getTotalAppointments() << "|\n";
    }
    cout << "  +---------+---------------------+-----------------------+--------------+\n";
    waitForEnter();
}

void generateFinancialReport() {
    if (!checkUserAccess("add_patient")) return;
    printSectionHeader("FINANCIAL SUMMARY REPORT");
    double totalBilled = 0, totalCollected = 0, totalPending = 0;
    int paidCount = 0, partialCount = 0, unpaidCount = 0;
    for (int i = 0; i < totalBills; i++) {
        totalBilled    += billList[i]->getTotalBillAmount();
        totalCollected += billList[i]->getAmountPaid();
        totalPending   += billList[i]->getRemainingBalance();
        string status = billList[i]->getPaymentStatus();
        if      (status == "Paid")    paidCount++;
        else if (status == "Partial") partialCount++;
        else                          unpaidCount++;
    }
    cout << "\n  Total Bills     : " << totalBills    << "\n";
    cout << "  Paid            : " << paidCount      << "\n";
    cout << "  Partially Paid  : " << partialCount   << "\n";
    cout << "  Unpaid          : " << unpaidCount    << "\n";
    cout << fixed << setprecision(2);
    cout << "\n  Total Billed    : Rs. " << totalBilled    << "\n";
    cout << "  Total Collected : Rs. " << totalCollected << "\n";
    cout << "  Total Pending   : Rs. " << totalPending   << "\n";
    waitForEnter();
}

void generateAppointmentStats() {
    if (!checkUserAccess("view_appt")) return;
    printSectionHeader("APPOINTMENT STATISTICS");
    int scheduledCount = 0, completedCount = 0, cancelledCount = 0;
    for (int i = 0; i < totalAppointments; i++) {
        string status = appointmentList[i]->getAppointmentStatus();
        if      (status == "Scheduled")  scheduledCount++;
        else if (status == "Completed")  completedCount++;
        else if (status == "Cancelled")  cancelledCount++;
    }
    cout << "\n  Total Appointments : " << totalAppointments << "\n";
    cout << "  Scheduled          : " << scheduledCount   << "\n";
    cout << "  Completed          : " << completedCount   << "\n";
    cout << "  Cancelled          : " << cancelledCount   << "\n";
    waitForEnter();
}

void patientMenu() {
    int choice;
    do {
        printSectionHeader("PATIENT MANAGEMENT");
        cout << "\n  1. Add New Patient\n  2. View Patient Details\n  3. Update Patient Info\n";
        cout << "  4. Remove Patient\n  5. Search Patient\n  6. List All Patients\n  0. Back\n";
        choice = readInteger("\n  Choice : ");
        switch (choice) {
            case 1: addNewPatient();      break;
            case 2: viewPatientDetails(); break;
            case 3: updatePatientInfo();  break;
            case 4: removePatient();      break;
            case 5: searchForPatient();   break;
            case 6: listAllPatients();    break;
        }
    } while (choice != 0);
}

void doctorMenu() {
    int choice;
    do {
        printSectionHeader("DOCTOR MANAGEMENT");
        cout << "\n  1. Add New Doctor\n  2. View Doctor Details\n  3. Update Doctor Info\n";
        cout << "  4. Remove Doctor\n  5. Search Doctor\n  6. List All Doctors\n  7. Check Availability\n  0. Back\n";
        choice = readInteger("\n  Choice : ");
        switch (choice) {
            case 1: addNewDoctor();          break;
            case 2: viewDoctorDetails();     break;
            case 3: updateDoctorInfo();      break;
            case 4: removeDoctor();          break;
            case 5: searchForDoctor();       break;
            case 6: listAllDoctors();        break;
            case 7: checkDoctorAvailability(); break;
        }
    } while (choice != 0);
}

void appointmentMenu() {
    int choice;
    do {
        printSectionHeader("APPOINTMENT MANAGEMENT");
        cout << "\n  1. Book Appointment\n  2. View Appointment\n  3. Reschedule\n  4. Cancel\n";
        cout << "  5. Patient Appointments\n  6. Doctor Appointments\n  7. Daily Schedule\n  0. Back\n";
        choice = readInteger("\n  Choice : ");
        switch (choice) {
            case 1: bookNewAppointment();      break;
            case 2: viewAppointmentDetails();  break;
            case 3: rescheduleAppointment();   break;
            case 4: cancelAppointment();       break;
            case 5: listPatientAppointments(); break;
            case 6: listDoctorAppointments();  break;
            case 7: viewDailySchedule();       break;
        }
    } while (choice != 0);
}

void medicalRecordsMenu() {
    int choice;
    do {
        printSectionHeader("MEDICAL RECORDS");
        cout << "\n  1. Add Medical Record\n  2. View Patient History\n  3. Update Record\n  4. Search Records\n  0. Back\n";
        choice = readInteger("\n  Choice : ");
        switch (choice) {
            case 1: addMedicalRecord();           break;
            case 2: viewPatientMedicalHistory();  break;
            case 3: updateMedicalRecord();        break;
            case 4: searchMedicalRecords();       break;
        }
    } while (choice != 0);
}

void billingMenu() {
    int choice;
    do {
        printSectionHeader("BILLING MANAGEMENT");
        cout << "\n  1. Generate Bill\n  2. View Bill\n  3. Process Payment\n";
        cout << "  4. Payment History\n  5. Total Revenue\n  6. Pending Bills\n  0. Back\n";
        choice = readInteger("\n  Choice : ");
        switch (choice) {
            case 1: generateNewBill();          break;
            case 2: viewBillDetails();          break;
            case 3: processPayment();           break;
            case 4: viewPatientPaymentHistory(); break;
            case 5: calculateTotalRevenue();    break;
            case 6: showPendingBills();         break;
        }
    } while (choice != 0);
}

void departmentMenu() {
    int choice;
    do {
        printSectionHeader("DEPARTMENT MANAGEMENT");
        cout << "\n  1. Add Department\n  2. Assign Doctor to Department\n  3. View Department\n  4. List All Departments\n  0. Back\n";
        choice = readInteger("\n  Choice : ");
        switch (choice) {
            case 1: addNewDepartment();        break;
            case 2: assignDoctorToDepartment(); break;
            case 3: viewDepartmentDetails();   break;
            case 4: listAllDepartments();      break;
        }
    } while (choice != 0);
}

void reportsMenu() {
    int choice;
    do {
        printSectionHeader("REPORTS & ANALYTICS");
        cout << "\n  1. Patient Summary\n  2. Doctor Performance\n  3. Financial Summary\n  4. Appointment Statistics\n  0. Back\n";
        choice = readInteger("\n  Choice : ");
        switch (choice) {
            case 1: generatePatientReport();     break;
            case 2: generateDoctorReport();      break;
            case 3: generateFinancialReport();   break;
            case 4: generateAppointmentStats();  break;
        }
    } while (choice != 0);
}

void securityMenu() {
    int choice;
    do {
        printSectionHeader("SECURITY & ACCESS CONTROL");
        cout << "\n  1. Login\n  2. Logout\n  3. Data Validation Demo\n  4. Privacy Info\n  0. Back\n";
        choice = readInteger("\n  Choice : ");
        switch (choice) {
            case 1: handleLogin();        break;
            case 2: handleLogout(); waitForEnter(); break;
            case 3: showValidationDemo(); break;
            case 4: showPrivacyInfo();    break;
        }
    } while (choice != 0);
}

int main() {
    loadInitialData();

    cout << "\n  +==============================================+\n";
    cout << "  |   HEALTHCARE & PATIENT MANAGEMENT SYSTEM   |\n";
    cout << "  |   Object-Oriented Programming Assignment   |\n";
    cout << "  +==============================================+\n";
    cout << "\n  System initialized. Sample data loaded.\n\n";
    cout << "  Default Login Credentials:\n";
    cout << "    admin   / admin123  (Full Access)\n";
    cout << "    drali   / doc123    (Doctor)\n";
    cout << "    rfront  / rec123    (Receptionist)\n";
    waitForEnter();

    int choice;
    do {
        printSectionHeader("MAIN MENU");
        if (currentUser && currentUser->getIsLoggedIn())
            cout << "\n  Logged in as: " << currentUser->getUsername()
                 << " [" << currentUser->getUserRole() << "]\n";
        else
            cout << "\n  Status: Not logged in\n";
        cout << "\n  1. Patient Management\n  2. Doctor Management\n  3. Appointment Management\n";
        cout << "  4. Medical Records\n  5. Billing\n  6. Department Management\n";
        cout << "  7. Reports & Analytics\n  8. Security & Access Control\n  0. Exit\n";
        choice = readInteger("\n  Choice : ");
        switch (choice) {
            case 1: patientMenu();     break;
            case 2: doctorMenu();      break;
            case 3: appointmentMenu(); break;
            case 4: medicalRecordsMenu(); break;
            case 5: billingMenu();     break;
            case 6: departmentMenu();  break;
            case 7: reportsMenu();     break;
            case 8: securityMenu();    break;
            case 0: cout << "\n  Goodbye!\n"; break;
            default: cout << "\n  Invalid option. Try again.\n";
        }
    } while (choice != 0);

    freeAllMemory();
    return 0;
}
