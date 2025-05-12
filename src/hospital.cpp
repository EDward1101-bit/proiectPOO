#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/appointment.h"
#include "../includes/patient.h"
#include <algorithm>
#include <fstream>
#include <string>

Hospital::Hospital(const std::string& name) : name(name) {}

Hospital::Hospital(const Hospital& other)
    : name(other.name) {
    for (const auto& doctor : other.doctors) {
        doctors.push_back(std::make_unique<Doctor>(*doctor));
    }
    for (const auto& appointment : other.appointments) {
        appointments.push_back(std::make_unique<Appointment>(*appointment));
    }
}

Hospital& Hospital::operator=(const Hospital& other) {
    if (this != &other) {
        name = other.name;
        doctors.clear();
        appointments.clear();
        for (const auto& doctor : other.doctors) {
            doctors.push_back(std::make_unique<Doctor>(*doctor));
        }
        for (const auto& appointment : other.appointments) {
            appointments.push_back(std::make_unique<Appointment>(*appointment));
        }
    }
    return *this;
}

Hospital::~Hospital() {}

const std::string& Hospital::getName() const { return name; }
const std::vector<std::unique_ptr<Doctor>>& Hospital::getDoctors() const { return doctors; }

void Hospital::addDoctor(std::unique_ptr<Doctor> doctor) {
    doctors.push_back(std::move(doctor));
}

void Hospital::addAppointment(std::unique_ptr<Appointment> appointment) {
    appointments.push_back(std::move(appointment));
}

Doctor* Hospital::findDoctorByName(const std::string& doctorName) const {
    for (const auto& doctor : doctors) {
        if (doctor && doctor->getName() == doctorName) {
            return doctor.get();
        }
    }
    return nullptr;
}


void Hospital::listAllDoctors() const {
    for (const auto& doctor : doctors) {
        if (doctor) {
            std::cout << *doctor << "\n";
        }
    }
}

void Hospital::listAllAppointments() const {
    std::vector<const Appointment*> sortedAppointments;
    for (const auto& appt : appointments) {
        sortedAppointments.push_back(appt.get());
    }

    std::sort(sortedAppointments.begin(), sortedAppointments.end(), [](const Appointment* a, const Appointment* b) {
        return a->getDate() < b->getDate() || (a->getDate() == b->getDate() && a->getTime() < b->getTime());
    });

    for (const auto& appt : sortedAppointments) {
        if (appt) {
            std::cout << *appt << "\n";
        }
    }
}

bool Hospital::isDoctorAvailable(const Doctor* doctor, const std::string& date, const std::string& time) const {
    for (const auto& appointment : appointments) {
        if (appointment && appointment->getDoctor() == doctor) {
            if (appointment->getDate() == date && appointment->getTime() == time) {
                return false;
            }
        }
    }
    return true; // Doctorul e liber
}

void Hospital::saveAppointmentsToCSV(const std::string& filename) const {
    std::ofstream fout(filename, std::ios::trunc); // suprascrie fisierul
    if (!fout.is_open()) {
        std::cerr << "Error opening appointments file for writing.\n";
        return;
    }

    for (const auto& appointment : appointments) {
        if (appointment) {
            fout << appointment->getDoctor()->getName() << ","
                 << appointment->getPatient()->getName() << ","
                 << appointment->getDate() << ","
                 << appointment->getTime() << "\n";
        }
    }
    fout.close();
}

void Hospital::savePatientsToCSV(const std::vector<std::unique_ptr<Patient>>& patients, const std::string& filename) {
    std::ofstream fout(filename, std::ios::trunc); // ștergem și rescriem

    if (!fout.is_open()) {
        std::cerr << "Error opening patients file for writing.\n";
        return;
    }

    for (const auto& patientPtr : patients) {
        if (patientPtr) {
            fout << patientPtr->getName() << ","
                 << patientPtr->getCNP() << ","
                 << patientPtr->getAge() << ","
                 << patientPtr->getGender() << ",";

            if (!patientPtr->getDiseases().empty()) {
                auto it = patientPtr->getDiseases().begin();
                fout << *it;
                ++it;
                for (; it != patientPtr->getDiseases().end(); ++it) {
                    fout << "|" << *it;
                }
            } else {
                fout << "Healthy";
            }

            fout << "\n";
        }
    }
    fout.close();
}

std::ostream& operator<<(std::ostream& os, const Hospital& hospital) {
    os << "Hospital Name: " << hospital.name;
    return os;
}
