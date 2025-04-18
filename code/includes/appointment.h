#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <string>
#include "doctor.h"
#include "patient.h"

class Appointment {
private:
    Doctor* doctor;
    Patient* patient;
    std::string date;  // Format: YYYY-MM-DD
    std::string time;  // Format: HH:MM

    bool isValidDate(const std::string& date) const;
    bool isValidTime(const std::string& time) const;
    bool isValidDateTime(const std::string& date, const std::string& time) const;

public:
    Appointment(Doctor* doctor, Patient* patient, const std::string& date, const std::string& time);
    std::string getDoctorName() const;
    std::string getDate() const;
    std::string getTime() const;
    void printInfo() const;
    friend std::ostream& operator<<(std::ostream& os, const Appointment& a);
};

#endif // APPOINTMENT_H
