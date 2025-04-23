#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/appointment.h"
#include "../includes/patient.h"
#include "../includes/medical_data.h"
#include <algorithm>

// Constructor
Hospital::Hospital(std::string name, Location location)
    : name(std::move(name)), location(std::move(location)) {}

// Copy constructor
Hospital::Hospital(const Hospital& other)
    : name(other.name), location(other.location), totalProfit(other.totalProfit) {
    for (Doctor* doc : other.doctors) {
        doctors.push_back(new Doctor(*doc));
    }
    for (Appointment* app : other.appointments) {
        appointments.push_back(new Appointment(*app));
    }
}

// Copy assignment operator
Hospital& Hospital::operator=(const Hospital& other) {
    if (this != &other) {
        for (Doctor* doc : doctors) delete doc;
        for (Appointment* app : appointments) delete app;

        doctors.clear();
        appointments.clear();

        name = other.name;
        location = other.location;
        totalProfit = other.totalProfit;

        for (Doctor* doc : other.doctors) {
            doctors.push_back(new Doctor(*doc));
        }
        for (Appointment* app : other.appointments) {
            appointments.push_back(new Appointment(*app));
        }
    }
    return *this;
}

Hospital::~Hospital() {
    for (Doctor* doc : doctors) delete doc;
    for (Appointment* app : appointments) delete app;
}

void Hospital::addDoctor(Doctor* doctor) {
    doctors.push_back(doctor);
}

void Hospital::addAppointment(Appointment* appointment) {
    appointments.push_back(appointment);
}

void Hospital::addPatientToDoctor(const std::string& doctorName, Patient* patient) {
    if (patient->getDiseases().empty()) return;

    const std::string& disease = patient->getDiseases().begin()->first;
    auto it = diseaseToSpecialty.find(disease);
    if (it == diseaseToSpecialty.end()) return;

    const std::string& requiredSpecialty = it->second;

    for (Doctor* doctor : doctors) {
        if (doctor->getName() == doctorName && doctor->getSpecialty() == requiredSpecialty) {
            doctor->assignPatient(patient);
            return;
        }
    }
}

bool Hospital::isDoctorAvailable(const std::string& doctorName, const std::string& date, const std::string& time) const {
    for (const Doctor* doctor : doctors) {
        if (doctor->getName() == doctorName) {
            for (const Appointment* appointment : doctor->getAppointments()) {
                if (appointment->getDate() == date && appointment->getTime() == time) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

void Hospital::scheduleAppointment(const std::string& doctorName, Patient* patient, const std::string& date, const std::string& time) {
    if (!isDoctorAvailable(doctorName, date, time)) {
        return;
    }

    for (Doctor* doctor : doctors) {
        if (doctor->getName() == doctorName) {
            Appointment* newAppointment = new Appointment(date, time, doctor, location.getTimezoneOffset());
            doctor->addAppointment(newAppointment);
            addAppointment(newAppointment);
            return;
        }
    }
}

void Hospital::dischargePatient(Patient* patient, Doctor* doctor) {
    if (!patient->isHealthy()) return;

    double cost = patient->getTotalTreatmentCost();
    if (patient->getFunds() < cost) return;

    patient->deductFunds(cost);
    totalProfit += cost;
    doctor->removePatient(patient);

    Appointment* recheck = new Appointment("2025-05-01", "09:00", doctor, location.getTimezoneOffset());
    doctor->addAppointment(recheck);
    addAppointment(recheck);
}

double Hospital::getProfit() const {
    return totalProfit;
}

void Hospital::printInfo() const {
    std::cout << "Hospital: " << name << "\nLocation: " << location << "\n";
}

void Hospital::printDoctors() const {
    std::cout << "Doctors in the hospital:\n";
    for (const Doctor* doctor : doctors) {
        std::cout << doctor->getName() << " - Specialty: " << doctor->getSpecialty() << "\n";
    }
}

void Hospital::printAppointments() const {
    std::cout << "Appointments in the hospital:\n";
    for (const Appointment* appointment : appointments) {
        std::cout << *appointment << "\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Hospital& h) {
    os << "Hospital: " << h.name << ", Location: " << h.location << ", Total Profit: $" << h.totalProfit << "\n";
    return os;
}