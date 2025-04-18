#include "../includes/appointment.h"
#include <iostream>
#include <regex>
#include <stdexcept>

Appointment::Appointment(Doctor* doctor, Patient* patient, const std::string& date, const std::string& time)
    : doctor(doctor), patient(patient), date(date), time(time) {
    if (!isValidDateTime(date, time)) {
        throw std::invalid_argument("Invalid date or time format.");
    }
}

bool Appointment::isValidDate(const std::string& date) const {
    std::regex dateRegex(R"(\d{4}-\d{2}-\d{2})");
    return std::regex_match(date, dateRegex);
}

bool Appointment::isValidTime(const std::string& time) const {
    std::regex timeRegex(R"(\d{2}:\d{2})");
    return std::regex_match(time, timeRegex);
}

bool Appointment::isValidDateTime(const std::string& date, const std::string& time) const {
    return isValidDate(date) && isValidTime(time);
}

std::string Appointment::getDoctorName() const {
    return doctor->getName();
}

std::string Appointment::getDate() const {
    return date;
}

std::string Appointment::getTime() const {
    return time;
}

void Appointment::printInfo() const {
    std::cout << "Appointment: " << *doctor << " with " << *patient << " on " << date << " at " << time << "\n";
}

std::ostream& operator<<(std::ostream& os, const Appointment& a) {
    os << *a.doctor << " with " << *a.patient << " on " << a.date << " at " << a.time;
    return os;
}
