#include "Bill.h"
#include <iostream>
#include <iomanip>
using namespace std;

Bill::Bill() {
    billID            = "BL000";
    patientID         = "NONE";
    patientName       = "Unknown";
    consultationFee   = 0.0;
    labTestFee        = 0.0;
    medicineFee       = 0.0;
    totalBillAmount   = 0.0;
    amountPaid        = 0.0;
    billDate          = "0000-00-00";
    paymentStatus     = "Unpaid";
}

Bill::Bill(string id, string patID, string patName,
           double consFee, double labFee, double medFee, string date) {
    billID          = id;
    patientID       = patID;
    patientName     = patName;
    consultationFee = (consFee >= 0) ? consFee : 0.0;
    labTestFee      = (labFee  >= 0) ? labFee  : 0.0;
    medicineFee     = (medFee  >= 0) ? medFee  : 0.0;
    amountPaid      = 0.0;
    billDate        = date;
    recalculateTotal();
    paymentStatus   = "Unpaid";
}

Bill::Bill(const Bill& other) {
    billID          = other.billID;
    patientID       = other.patientID;
    patientName     = other.patientName;
    consultationFee = other.consultationFee;
    labTestFee      = other.labTestFee;
    medicineFee     = other.medicineFee;
    totalBillAmount = other.totalBillAmount;
    amountPaid      = other.amountPaid;
    billDate        = other.billDate;
    paymentStatus   = other.paymentStatus;
}

Bill::~Bill() {}

string Bill::getBillID()          const { return billID; }
string Bill::getPatientID()       const { return patientID; }
string Bill::getPatientName()     const { return patientName; }
double Bill::getConsultationFee() const { return consultationFee; }
double Bill::getLabTestFee()      const { return labTestFee; }
double Bill::getMedicineFee()     const { return medicineFee; }
double Bill::getTotalBillAmount() const { return totalBillAmount; }
double Bill::getAmountPaid()      const { return amountPaid; }
double Bill::getRemainingBalance() const { return totalBillAmount - amountPaid; }
string Bill::getBillDate()        const { return billDate; }
string Bill::getPaymentStatus()   const { return paymentStatus; }

void Bill::setConsultationFee(double fee) {
    if (fee >= 0) { consultationFee = fee; recalculateTotal(); }
    else cout << "  [Error] Fee cannot be negative.\n";
}

void Bill::setLabTestFee(double fee) {
    if (fee >= 0) { labTestFee = fee; recalculateTotal(); }
    else cout << "  [Error] Fee cannot be negative.\n";
}

void Bill::setMedicineFee(double fee) {
    if (fee >= 0) { medicineFee = fee; recalculateTotal(); }
    else cout << "  [Error] Fee cannot be negative.\n";
}

void Bill::recalculateTotal() {
    totalBillAmount = consultationFee + labTestFee + medicineFee;
}

bool Bill::recordPayment(double amount) {
    if (amount <= 0) {
        cout << "  [Error] Payment must be greater than zero.\n";
        return false;
    }
    if (amount > getRemainingBalance()) {
        cout << fixed << setprecision(2);
        cout << "  [Error] Amount exceeds remaining balance of Rs. " << getRemainingBalance() << "\n";
        return false;
    }
    amountPaid += amount;
    if (amountPaid >= totalBillAmount) paymentStatus = "Paid";
    else paymentStatus = "Partial";
    return true;
}

void Bill::displayDetails() const {
    cout << "\n  +------------------------------------------+\n";
    cout << "  |             BILL DETAILS                 |\n";
    cout << "  +------------------------------------------+\n";
    cout << "  | Bill ID          : " << left << setw(22) << billID      << "|\n";
    cout << "  | Patient ID       : " << left << setw(22) << patientID   << "|\n";
    cout << "  | Patient Name     : " << left << setw(22) << patientName << "|\n";
    cout << "  | Bill Date        : " << left << setw(22) << billDate    << "|\n";
    cout << "  +------------------------------------------+\n";
    cout << fixed << setprecision(2);
    cout << "  | Consultation Fee : Rs. " << left << setw(18) << consultationFee << "|\n";
    cout << "  | Lab Test Fee     : Rs. " << left << setw(18) << labTestFee      << "|\n";
    cout << "  | Medicine Fee     : Rs. " << left << setw(18) << medicineFee     << "|\n";
    cout << "  +------------------------------------------+\n";
    cout << "  | Total Amount     : Rs. " << left << setw(18) << totalBillAmount   << "|\n";
    cout << "  | Amount Paid      : Rs. " << left << setw(18) << amountPaid        << "|\n";
    cout << "  | Remaining Balance: Rs. " << left << setw(18) << getRemainingBalance() << "|\n";
    cout << "  | Payment Status   : " << left << setw(22) << paymentStatus << "|\n";
    cout << "  +------------------------------------------+\n";
}

void Bill::displayRow() const {
    cout << "  | " << left << setw(7)  << billID
         << "| " << setw(7)  << patientID
         << "| " << setw(16) << patientName
         << "| " << fixed << setprecision(2) << setw(10) << totalBillAmount
         << "| " << setw(10) << amountPaid
         << "| " << setw(8)  << paymentStatus << "|\n";
}
