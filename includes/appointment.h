#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <iostream>

class Doctor;
class Patient;

class Appointment {
private:
    std::string date;
    std::string time;
    Doctor* doctor;
    Patient* patient;

public:

    Appointment(const std::string& date, const std::string& time, Doctor* doctor, Patient* patient);


    const std::string& getDate() const;
    const std::string& getTime() const;
    Doctor* getDoctor() const;
    Patient* getPatient() const;


    bool isInFuture() const;
    static bool isValidDateTime(const std::string& date, const std::string& time);


    friend std::ostream& operator<<(std::ostream& os, const Appointment& appointment);
};

#endif // APPOINTMENT_H
