#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <vector>
#include <algorithm>
#include "patient.h"
#include "appointment.h"

class Patient; // Forward declaration of the Patient class
class Appointment; // Forward declaration of the Appointment class

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

    // Add an appointment to the doctor's list
    void addAppointment(Appointment* appointment);

    // Get all appointments for this doctor
    const std::vector<Appointment*>& getAppointments() const;

    // Assign a patient to the doctor
    void assignPatient(Patient* p);

    // Remove a patient from the doctor's list
    void removePatient(const Patient* p);

    // Print the doctor's information
    void printInfo() const;

    // Print the list of patients assigned to the doctor
    void printPatients() const;

    // Operator<< overload to print doctor's information
    friend std::ostream& operator<<(std::ostream& os, const Doctor& d);
};

#endif // DOCTOR_H
