#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <ostream>
#include "doctor.h"

class Doctor; // Forward declaration of the Doctor class

class Appointment {
private:
    std::string date;
    std::string time;
    Doctor* doctor; // Pointer to the associated doctor

public:
    // Constructor
    Appointment(const std::string& date, const std::string& time, Doctor* doctor);

    // Getter functions
    std::string const& getDate() const;
    std::string const& getTime() const;
    Doctor* getDoctor() const;

    // Static and member functions
    static bool isValidDateTime(const std::string& date, const std::string& time);
    bool isDoctorAvailable(const std::string& date, const std::string& time) const;

    // Print appointment details
    void printInfo() const;

    // Operator overload to print appointment details
    friend std::ostream& operator<<(std::ostream& os, const Appointment& appointment);
};

#endif // APPOINTMENT_H