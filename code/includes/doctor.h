#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <vector>
#include <algorithm>
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

    // Getters
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
};

#endif // DOCTOR_H