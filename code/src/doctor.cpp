#include "../includes/doctor.h"
#include <iostream>

// Constructor
Doctor::Doctor(std::string name, std::string specialty)
    : name(std::move(name)), specialty(std::move(specialty)) {}

// Getters
std::string const& Doctor::getName() const {
    return name;
}

std::string const& Doctor::getSpecialty() const {
    return specialty;
}

// Add an appointment to the doctor's list
void Doctor::addAppointment(Appointment* appointment) {
    appointments.push_back(appointment);
}

// Get all appointments for this doctor
const std::vector<Appointment*>& Doctor::getAppointments() const {
    return appointments;
}

// Assign a patient to the doctor
void Doctor::assignPatient(Patient* p) {
    patients.push_back(p);
}

// Remove a patient from the doctor's list
void Doctor::removePatient(const Patient* p) {
    auto it = std::find_if(patients.begin(), patients.end(),
        [p](const Patient* patient) {
            return patient == p; // Compare pointers
        });

    if (it != patients.end()) {
        patients.erase(it); // Remove the patient if found
    } else {
        std::cerr << "Patient not found.\n";
    }
}

// Print the doctor's information
void Doctor::printInfo() const {
    std::cout << "Doctor: " << name << ", Specialty: " << specialty << "\n";
}

// Print the list of patients assigned to the doctor
void Doctor::printPatients() const {
    std::cout << "Patients assigned to Dr. " << name << ":\n";
    for (const auto* patient : patients) { // range-based loop with pointer
        std::cout << *patient << "\n";
    }
}

Doctor::~Doctor() {
    for (Appointment* appointment : appointments) {
        delete appointment;
    }
}

// Operator<< overload to print doctor's information
std::ostream& operator<<(std::ostream& os, const Doctor& d) {
    os << "Doctor: " << d.name << ", Specialty: " << d.specialty;
    return os;
}