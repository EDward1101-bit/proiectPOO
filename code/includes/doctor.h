#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>
#include <vector>
#include "patient.h"  // Include the Patient class

class Doctor {
private:
    std::string name;
    std::string specialty;
    std::vector<Patient*> patients;  // Store pointers to patients

public:
    // Constructor
    explicit Doctor(std::string name, std::string specialty);

    std::string getName() const;
    std::string getSpecialty() const;
    void assignPatient(Patient* p);
    void removePatient(const Patient* p);
    void printInfo() const;
    void printPatients() const;
    friend std::ostream& operator<<(std::ostream& os, const Doctor& d);
};

#endif // DOCTOR_H
