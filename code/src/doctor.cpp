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
    for (auto it = patients.begin(); it != patients.end(); ++it) {
        if (*it == p) {
            patients.erase(it);
            break;
        }
    }
}

// Print the doctor's information
void Doctor::printInfo() const {
    std::cout << "Doctor: " << name << ", Specialty: " << specialty << "\n";
}

// Print the list of patients assigned to the doctor
void Doctor::printPatients() const {
    std::cout << "Patients assigned to Dr. " << name << ":\n";
    for (const auto& patient : patients) {
        std::cout << *patient << "\n";
    }
}

// Operator<< overload to print doctor's information
std::ostream& operator<<(std::ostream& os, const Doctor& d) {
    os << "Doctor: " << d.name << ", Specialty: " << d.specialty;
    return os;
}
