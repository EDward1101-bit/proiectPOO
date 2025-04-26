#include "../includes/appointment.h"
#include "../includes/doctor.h"
#include "../includes/patient.h"

#include <sstream>
#include <iomanip>
#include <ctime>

Appointment::Appointment(const std::string& date, const std::string& time, Doctor* doctor, Patient* patient)
    : date(date), time(time), doctor(doctor), patient(patient) {}

const std::string& Appointment::getDate() const { return date; }
const std::string& Appointment::getTime() const { return time; }
Doctor* Appointment::getDoctor() const { return doctor; }
Patient* Appointment::getPatient() const { return patient; }

bool Appointment::isValidDateTime() const {
    std::tm tm{};
    std::istringstream ss(date + " " + time);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");

    if (ss.fail()) {
        return false;
    }

    std::time_t appointmentTime = std::mktime(&tm);
    if (appointmentTime == -1) {
        return false;
    }

    std::time_t now = std::time(nullptr);

    return difftime(appointmentTime, now) > 0;
}

bool Appointment::isInFuture() const {
    std::tm tm{};
    std::istringstream ss(date + " " + time);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");

    if (ss.fail()) {
        return false;
    }

    std::time_t appointmentTime = std::mktime(&tm);
    std::time_t now = std::time(nullptr);

    return difftime(appointmentTime, now) > 0;
}

std::ostream& operator<<(std::ostream& os, const Appointment& appointment) {
    os << "Date: " << appointment.date << ", Time: " << appointment.time;
    if (appointment.doctor) {
        os << ", Doctor: " << appointment.doctor->getName();
    }
    if (appointment.patient) {
        os << ", Patient: " << appointment.patient->getName();
    }
    return os;
}
