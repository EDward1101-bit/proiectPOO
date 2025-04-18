#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/appointment.h"
#include "../includes/patient.h"
#include <iostream>

// Constructor for the Hospital
Hospital::Hospital(std::string name, std::string location)
    : name(std::move(name)), location(std::move(location)) {}

// Add a doctor to the hospital
void Hospital::addDoctor(Doctor* doctor) {
    doctors.push_back(doctor);
}

// Add an appointment to the hospital
void Hospital::addAppointment(Appointment* appointment) {
    appointments.push_back(appointment);
}

// Assign a patient to a doctor in the hospital
void Hospital::addPatientToDoctor(const std::string& doctorName, Patient* patient) {
    for (Doctor* doctor : doctors) {
        if (doctor->getName() == doctorName) {
            doctor->assignPatient(patient);
            return;
        }
    }
    std::cerr << "Doctor not found.\n";
}

// Check if a doctor is available at a specific date and time
bool Hospital::isDoctorAvailable(const std::string& doctorName, const std::string& date, const std::string& time) const {
    for (const Doctor* doctor : doctors) {
        if (doctor->getName() == doctorName) {
            for (const Appointment* appointment : doctor->getAppointments()) {
                if (appointment->getDate() == date && appointment->getTime() == time) {
                    return false; // Doctor is not available
                }
            }
            return true; // Doctor is available
        }
    }
    return false; // Doctor not found
}

// Schedule an appointment for a patient with a doctor
void Hospital::scheduleAppointment(const std::string& doctorName, [[maybe_unused]] Patient* patient, const std::string& date, const std::string& time) {
    if (!isDoctorAvailable(doctorName, date, time)) {
        std::cout << "Doctor is not available at the given time.\n";
        return;
    }

    // Find the doctor and create a new appointment
    for (Doctor* doctor : doctors) {
        if (doctor->getName() == doctorName) {
            Appointment* newAppointment = new Appointment(date, time, doctor);
            doctor->addAppointment(newAppointment);
            addAppointment(newAppointment);
            std::cout << "Appointment scheduled with Dr. " << doctorName << " on " << date << " at " << time << "\n";
            return;
        }
    }

    std::cerr << "Doctor not found.\n";
}

// Print information about the hospital
void Hospital::printInfo() const {
    std::cout << "Hospital: " << name << "\nLocation: " << location << "\n";
}

// Print the list of doctors in the hospital
void Hospital::printDoctors() const {
    std::cout << "Doctors in the hospital:\n";
    for (const Doctor* doctor : doctors) {
        std::cout << doctor->getName() << " - Specialty: " << doctor->getSpecialty() << "\n";
    }
}

// Print the list of appointments in the hospital
void Hospital::printAppointments() const {
    std::cout << "Appointments in the hospital:\n";
    for (const Appointment* appointment : appointments) {
        std::cout << *appointment << "\n";
    }
}

// Operator<< to display the hospital information
std::ostream& operator<<(std::ostream& os, const Hospital& h) {
    os << "Hospital: " << h.name << ", Location: " << h.location << "\n";
    return os;
}
