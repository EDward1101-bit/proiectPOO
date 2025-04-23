#ifndef DOCTOR_H
#define DOCTOR_H

#include <algorithm>
#include <string>
#include <vector>
#include "patient.h"
#include "appointment.h"

class Patient;
class Appointment;

class Doctor {
private:
    std::string name;
    std::string specialty;
    std::vector<Patient*> patients;
    std::vector<Appointment*> appointments;

public:
    // Constructor
    Doctor(std::string name, std::string specialty);

    std::string const& getName() const;
    std::string const& getSpecialty() const;

    void addAppointment(Appointment* appointment);
    const std::vector<Appointment*>& getAppointments() const;

    void assignPatient(Patient* p);
    void removePatient(const Patient* p);

    void printInfo() const;
    void printPatients() const;

    ~Doctor();
    friend std::ostream& operator<<(std::ostream& os, const Doctor& d);

    // Validation
    static bool isValidSpecialty(const std::string& specialty);
};

#endif // DOCTOR_H