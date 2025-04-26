#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/appointment.h"
#include <algorithm>

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
const std::vector<std::unique_ptr<Appointment>>& Hospital::getAppointments() const { return appointments; }

void Hospital::addDoctor(std::unique_ptr<Doctor> doctor) {
    doctors.push_back(std::move(doctor));
}

void Hospital::addAppointment(std::unique_ptr<Appointment> appointment) {
    appointments.push_back(std::move(appointment));
}

Doctor* Hospital::findDoctorByName(const std::string& name) const {
    for (const auto& doctor : doctors) {
        if (doctor && doctor->getName() == name) {
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
    for (const auto& app : appointments) {
        sortedAppointments.push_back(app.get());
    }

    std::sort(sortedAppointments.begin(), sortedAppointments.end(), [](const Appointment* a, const Appointment* b) {
        return a->getDate() < b->getDate() || (a->getDate() == b->getDate() && a->getTime() < b->getTime());
    });

    for (const auto& app : sortedAppointments) {
        if (app) {
            std::cout << *app << "\n";
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Hospital& hospital) {
    os << "Hospital Name: " << hospital.name;
    return os;
}
