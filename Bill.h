#ifndef BILL_H
#define BILL_H
#include <string>
using namespace std;

class Bill {
private:
    string billID;
    string patientID;
    string patientName;
    double consultationFee;
    double labTestFee;
    double medicineFee;
    double totalBillAmount;
    double amountPaid;
    string billDate;
    string paymentStatus;

public:
    Bill();
    Bill(string id, string patID, string patName,
         double consFee, double labFee, double medFee, string date);
    Bill(const Bill& other);
    ~Bill();

    string getBillID()          const;
    string getPatientID()       const;
    string getPatientName()     const;
    double getConsultationFee() const;
    double getLabTestFee()      const;
    double getMedicineFee()     const;
    double getTotalBillAmount() const;
    double getAmountPaid()      const;
    double getRemainingBalance() const;
    string getBillDate()        const;
    string getPaymentStatus()   const;

    void setConsultationFee(double fee);
    void setLabTestFee(double fee);
    void setMedicineFee(double fee);

    void recalculateTotal();
    bool recordPayment(double amount);

    void displayDetails() const;
    void displayRow()     const;
};

#endif
