#include "../includes/appointment.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

// Constructor
Appointment::Appointment(const std::string& date, const std::string& time, Doctor* doctor)
    : date(date), time(time), doctor(doctor) {}

const std::string& Appointment::getDate() const {
    return date;
}

const std::string& Appointment::getTime() const {
    return time;
}

Doctor* Appointment::getDoctor() const {
    return doctor;
}

// Verifies if the date and time are valid
bool Appointment::isValidDateTime(const std::string& inputDate, const std::string& inputTime) {
    if (inputDate.size() != 10 || inputDate[4] != '-' || inputDate[7] != '-') {
        std::cerr << "Invalid date format. Expected format: YYYY-MM-DD\n";
        return false;
    }

    if (inputTime.size() != 5 || inputTime[2] != ':') {
        std::cerr << "Invalid time format. Expected format: HH:MM\n";
        return false;
    }

    int year, month, day;
    try {
        year = std::stoi(inputDate.substr(0, 4));
        month = std::stoi(inputDate.substr(5, 2));
        day = std::stoi(inputDate.substr(8, 2));
    } catch (const std::exception&) {
        std::cerr << "Invalid date value.\n";
        return false;
    }

    if (year <= 0 || month < 1 || month > 12 || day < 1 || day > 31) {
        std::cerr << "Invalid date: year, month, or day out of range.\n";
        return false;
    }

    const int days_in_month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)))
        ? (day > 29) : (day > days_in_month[month - 1])) {
        std::cerr << "Invalid day for the given month.\n";
        return false;
    }

    int hour, minute;
    try {
        hour = std::stoi(inputTime.substr(0, 2));
        minute = std::stoi(inputTime.substr(3, 2));
    } catch (const std::exception&) {
        std::cerr << "Invalid time value.\n";
        return false;
    }

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        std::cerr << "Invalid time: hour or minute out of range.\n";
        return false;
    }

    return true;
}

bool Appointment::isDoctorAvailable(const std::string& checkDate, const std::string& checkTime) const {
    for (const auto* appointment : doctor->getAppointments()) {
        if (appointment->getDate() == checkDate && appointment->getTime() == checkTime) {
            return false;
        }
    }
    return true;
}

// Print appointment information
void Appointment::printInfo() const {
    std::cout << "Appointment with Dr. " << doctor->getName()
              << " on " << date << " at " << time << "\n";
}

// Operator overload to print appointment details
std::ostream& operator<<(std::ostream& os, const Appointment& app) {
    os << "Appointment with Dr. " << app.doctor->getName()
       << " on " << app.date << " at " << app.time;
    return os;
}
