#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/appointment.h"
#include "../includes/patient.h"
#include <algorithm> // pentru std::sort


Hospital::Hospital(const std::string& name)
    : name(name) {}


Hospital::Hospital(const Hospital& other)
    : name(other.name) {
    for (const auto& doc : other.doctors) {
        doctors.push_back(std::make_unique<Doctor>(*doc));
    }
    for (const auto& app : other.appointments) {
        appointments.push_back(std::make_unique<Appointment>(*app));
    }
}


Hospital& Hospital::operator=(const Hospital& other) {
    if (this != &other) {
        name = other.name;
        doctors.clear();
        appointments.clear();
        for (const auto& doc : other.doctors) {
            doctors.push_back(std::make_unique<Doctor>(*doc));
        }
        for (const auto& app : other.appointments) {
            appointments.push_back(std::make_unique<Appointment>(*app));
        }
    }
    return *this;
}


Hospital::~Hospital() = default;


const std::string& Hospital::getName() const {
    return name;
}

const std::vector<std::unique_ptr<Doctor>>& Hospital::getDoctors() const {
    return doctors;
}

const std::vector<std::unique_ptr<Appointment>>& Hospital::getAppointments() const {
    return appointments;
}

// Funcții utile
void Hospital::addDoctor(std::unique_ptr<Doctor> doctor) {
    doctors.push_back(std::move(doctor));
}

void Hospital::addAppointment(std::unique_ptr<Appointment> appointment) {
    appointments.push_back(std::move(appointment));
}

Doctor* Hospital::findDoctorByName(const std::string& doctorName) const {
    for (const auto& doc : doctors) {
        if (doc && doc->getName() == doctorName) {
            return doc.get();
        }
    }
    return nullptr;
}

void Hospital::listAllDoctors() const {
    if (doctors.empty()) {
        std::cout << "No doctors available.\n";
        return;
    }
    for (const auto& doc : doctors) {
        if (doc) {
            std::cout << *doc << "\n";
        }
    }
}

void Hospital::listAllAppointments() const {
    if (appointments.empty()) {
        std::cout << "No appointments scheduled.\n";
        return;
    }

    std::vector<Appointment*> sortedAppointments;
    for (const auto& app : appointments) {
        if (app) {
            sortedAppointments.push_back(app.get());
        }
    }

    std::sort(sortedAppointments.begin(), sortedAppointments.end(),
        [](const Appointment* a, const Appointment* b) {
            if (a->getDate() != b->getDate())
                return a->getDate() < b->getDate();
            return a->getTime() < b->getTime();
        });

    for (const auto& app : sortedAppointments) {
        std::cout << *app << "\n"; // ✨ Compunere reală
    }
}

std::ostream& operator<<(std::ostream& os, const Hospital& hospital) {
    os << "Hospital: " << hospital.name << "\n"
       << "Doctors:\n";
    if (hospital.doctors.empty()) {
        os << "None\n";
    } else {
        for (const auto& doc : hospital.doctors) {
            if (doc) {
                os << *doc << "\n";
            }
        }
    }
    os << "Appointments:\n";
    if (hospital.appointments.empty()) {
        os << "None\n";
    } else {
        for (const auto& app : hospital.appointments) {
            if (app) {
                os << *app << "\n";
            }
        }
    }
    return os;
}
