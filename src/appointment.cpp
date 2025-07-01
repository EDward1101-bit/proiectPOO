#include "../includes/appointment.h"
#include "../includes/doctor.h"
#include "../includes/patient.h"

#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <unordered_set>
#include <thread>
using namespace std::chrono;

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

    return !ss.fail();
}

bool Appointment::isInFuture() const {
    using namespace std::chrono;

    std::tm appointmentTm{};
    std::istringstream input(date + " " + time);
    input >> std::get_time(&appointmentTm, "%Y-%m-%d %H:%M");

    if (input.fail()) {
        return false;
    }

    appointmentTm.tm_isdst = -1;
    std::time_t appointmentTimeT = std::mktime(&appointmentTm);
    if (appointmentTimeT == -1) {
        return false;
    }

    system_clock::time_point now = system_clock::now();
    std::time_t nowT = system_clock::to_time_t(now);

    if (appointmentTimeT <= nowT) {
        return false;
    }

    if (system_clock::from_time_t(appointmentTimeT) - now < hours(24 * 7)) {
        return false;
    }

    const std::tm* appointmentLocalTm = std::localtime(&appointmentTimeT);
    int weekday = appointmentLocalTm->tm_wday;
    if (weekday == 0 || weekday == 6) {
        return false;
    }

    int hour = appointmentLocalTm->tm_hour;
    int minute = appointmentLocalTm->tm_min;
    int totalMinutes = hour * 60 + minute;
    int startMinutes = 8 * 60 + 30;
    int endMinutes = 18 * 60 + 45;

    if (totalMinutes < startMinutes || totalMinutes > endMinutes) {
        return false;
    }

    return true;
}

std::ostream& operator<<(std::ostream& os, const Appointment& appointment) {
    static thread_local std::unordered_set<const void*> visited;
    if (visited.count(&appointment)) {
        os << "[Info: Appointment already printed. Skipping repeated output.]\n";
        return os;
    }
    visited.insert(&appointment);

    os << "Appointment:\n";
    os << "  Date: " << appointment.date << "\n";
    os << "  Time: " << appointment.time << "\n";

    if (appointment.doctor) {
        os << "  Doctor: " << appointment.doctor->getName() << "\n";
    }

    if (appointment.patient) {
        os << "  Patient: " << appointment.patient->getName() << "\n";
    }

    visited.erase(&appointment);
    return os;
}



