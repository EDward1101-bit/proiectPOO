#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>
#include <vector>
#include "patient.h"

class Doctor {
private:
    std::string name;
    std::string specialty;
    std::vector<Patient*> patients;  // A doctor has multiple patients

public:
    explicit Doctor(std::string name, std::string specialty);
    const std::string& getName() const;  // Getter for name
    void printInfo() const;
    void assignPatient(Patient* p);  // Assign a patient to this doctor
    void removePatient(Patient* p);  // Remove a patient from this doctor
    void printPatients() const;  // Print all patients of this doctor
    friend std::ostream& operator<<(std::ostream& os, const Doctor& d);
};

#endif // DOCTOR_H
