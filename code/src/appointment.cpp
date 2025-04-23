#include "../includes/appointment.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

// Constructor
Appointment::Appointment(const std::string& date, const std::string& time, Doctor* doctor, int timezoneOffset)
    : date(date), time(time), doctor(doctor), timezoneOffset(timezoneOffset) {}

const std::string& Appointment::getDate() const {
    return date;
}

const std::string& Appointment::getTime() const {
    return time;
}

int Appointment::getTimezoneOffset() const {
    return timezoneOffset;
}

Doctor* Appointment::getDoctor() const {
    return doctor;
}

// Verifies if the date and time are valid
bool Appointment::isValidDateTime(const std::string& inputDate, const std::string& inputTime, int timezoneOffset) {
    if (inputDate.size() != 10 || inputDate[4] != '-' || inputDate[7] != '-') {
        return false;
    }

    if (inputTime.size() != 5 || inputTime[2] != ':') {
        return false;
    }

    int year, month, day;
    try {
        year = std::stoi(inputDate.substr(0, 4));
        month = std::stoi(inputDate.substr(5, 2));
        day = std::stoi(inputDate.substr(8, 2));
    } catch (const std::exception&) {
        return false;
    }

    if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    const int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
        ? (day > 29) : (day > days_in_month[month - 1])) {
        return false;
    }

    int hour, minute;
    try {
        hour = std::stoi(inputTime.substr(0, 2));
        minute = std::stoi(inputTime.substr(3, 2));
    } catch (const std::exception&) {
        return false;
    }

    hour -= timezoneOffset; // convert to UTC hour for standardization

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        return false;
    }

    return true;
}

bool Appointment::isDoctorAvailable(const std::string& checkDate, const std::string& checkTime, int tzOffset) const {
    for (const auto* appointment : doctor->getAppointments()) {
        if (appointment->getDate() == checkDate &&
            appointment->getTime() == checkTime &&
            appointment->getTimezoneOffset() == tzOffset) {
            return false;
        }
    }
    return true;
}

// Print appointment information
void Appointment::printInfo() const {
    std::cout << "Appointment with Dr. " << doctor->getName()
              << " on " << date << " at " << time
              << " (UTC" << (timezoneOffset >= 0 ? "+" : "") << timezoneOffset << ")\n";
}

// Operator overload to print appointment details
std::ostream& operator<<(std::ostream& os, const Appointment& app) {
    os << "Appointment with Dr. " << app.doctor->getName()
       << " on " << app.date << " at " << app.time
       << " (UTC" << (app.timezoneOffset >= 0 ? "+" : "") << app.timezoneOffset << ")";
    return os;
}