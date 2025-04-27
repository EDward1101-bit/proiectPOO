#include "../includes/appointment.h"
#include "../includes/doctor.h"
#include "../includes/patient.h"

#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
using namespace std::chrono;

Appointment::Appointment(const std::string& date, const std::string& time, Doctor* doctor, Patient* patient)
    : date(date), time(time), doctor(doctor), patient(patient) {}

const std::string& Appointment::getDate() const { return date; }
const std::string& Appointment::getTime() const { return time; }

bool Appointment::isValidDateTime() const {
    std::tm tm{};
    std::istringstream ss(date + " " + time);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");

    return !ss.fail();
}

bool Appointment::isInFuture() const {

    std::tm appointmentTm{};
    std::istringstream input(date + " " + time);
    input >> std::get_time(&appointmentTm, "%Y-%m-%d %H:%M");

    std::time_t appointmentTimeT = std::mktime(&appointmentTm);
    if (appointmentTimeT == -1) {
        return false;
    }

    std::time_t currentTimeT = std::time(nullptr);
    system_clock::time_point now = system_clock::from_time_t(currentTimeT);
    system_clock::time_point appointmentTime = system_clock::from_time_t(appointmentTimeT);

    if (appointmentTime <= now) {
        return false;
    }

    std::tm currentTm = *std::localtime(&currentTimeT);
    currentTm.tm_year += 1;
    std::time_t nextYearTimeT = std::mktime(&currentTm);
    system_clock::time_point oneYearLater = system_clock::from_time_t(nextYearTimeT);

    if (appointmentTime > oneYearLater) {
        return false;
    }

    return true;
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
