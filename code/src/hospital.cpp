#include "../includes/hospital.h"
#include <iostream>
#include <stdexcept>

Hospital::Hospital(std::string name, std::string location)
    : name(std::move(name)), location(std::move(location)) {}

void Hospital::addDoctor(Doctor* doctor) {
    doctors.push_back(doctor);
}

void Hospital::addPatientToDoctor(const std::string& doctorName, Patient* p) {
    for (auto& doctor : doctors) {
        if (doctor->getName() == doctorName) {
            doctor->assignPatient(p);
            break;
        }
    }
}

bool Hospital::isDoctorAvailable(const std::string& doctorName, const std::string& date, const std::string& time) const {
    for (const auto& appointment : appointments) {
        if (appointment->getDoctorName() == doctorName && appointment->getDate() == date && appointment->getTime() == time) {
            return false;  // Doctorul nu este disponibil la acea oră
        }
    }
    return true;  // Doctorul este disponibil
}

void Hospital::scheduleAppointment(const std::string& doctorName, Patient* patient, const std::string& date, const std::string& time) {
    if (isDoctorAvailable(doctorName, date, time)) {
        for (auto& doctor : doctors) {
            if (doctor->getName() == doctorName) {
                appointments.push_back(new Appointment(doctor, patient, date, time));
                std::cout << "Appointment scheduled for Dr. " << doctorName << " on " << date << " at " << time << "\n";
                break;
            }
        }
    } else {
        std::cout << "Doctor " << doctorName << " is not available on " << date << " at " << time << "\n";
    }
}

void Hospital::printInfo() const {
    std::cout << "Hospital: " << name << ", Location: " << location << "\n";
}

void Hospital::printDoctors() const {
    std::cout << "Doctors in " << name << ":\n";
    for (const auto& doctor : doctors) {
        std::cout << *doctor << "\n";
    }
}

void Hospital::printAppointments() const {
    std::cout << "Appointments:\n";
    for (const auto& appointment : appointments) {
        std::cout << *appointment << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Hospital& h) {
    os << "Hospital: " << h.name << ", Location: " << h.location;
    return os;
}
