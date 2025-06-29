#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <vector>
#include <iostream>

class Patient;

class Doctor {
private:
    std::string name;
    std::string specialty;
    std::vector<Patient*> patients;

public:
    Doctor(const std::string& name, const std::string& specialty);

    const std::string& getName() const;
    const std::string& getSpecialty() const;
    const std::vector<Patient*>& getPatients() const;
    bool dischargePatient(const std::string& patientName);
    void assignPatient(Patient* patient);

    Doctor(const Doctor&) = default;
    Doctor& operator=(const Doctor&) = default;
    ~Doctor() = default;
    friend std::ostream& operator<<(std::ostream& os, const Doctor& doctor);
};

#endif // DOCTOR_H