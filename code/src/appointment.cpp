#include "../includes/appointment.h"
#include "../includes/doctor.h"
#include "../includes/patient.h"
#include <iomanip>
#include <sstream>
#include <ctime>


Appointment::Appointment(const std::string& date, const std::string& time, Doctor* doctor, Patient* patient)
    : date(date), time(time), doctor(doctor), patient(patient) {}


const std::string& Appointment::getDate() const {
    return date;
}

const std::string& Appointment::getTime() const {
    return time;
}

Doctor* Appointment::getDoctor() const {
    return doctor;
}

Patient* Appointment::getPatient() const {
    return patient;
}


bool Appointment::isValidDateTime(const std::string& date, const std::string& time) {
    std::istringstream ss(date + " " + time);
    std::tm tm = {};
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");

    if (ss.fail()) {
        return false;
    }

    return true;
}


bool Appointment::isInFuture() const {
    std::istringstream ss(date + " " + time);
    std::tm tm = {};
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");

    if (ss.fail()) {
        return false;
    }

    std::time_t appointmentTime = std::mktime(&tm);
    std::time_t now = std::time(nullptr);

    return appointmentTime > now;
}


std::ostream& operator<<(std::ostream& os, const Appointment& appointment) {
    os << "Appointment:\n"
       << " Date: " << appointment.date << "\n"
       << " Time: " << appointment.time << "\n"
       << " Doctor: ";
    if (appointment.doctor) {
        os << *appointment.doctor;
    } else {
        os << "None\n";
    }
    os << " Patient: ";
    if (appointment.patient) {
        os << *appointment.patient;
    } else {
        os << "None\n";
    }
    return os;
}
