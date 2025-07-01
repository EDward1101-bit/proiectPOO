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
    bool isValidDateTime() const;

    Appointment(const Appointment&) = delete;
    Appointment& operator=(const Appointment&) = delete;
    ~Appointment() = default;
    friend std::ostream& operator<<(std::ostream& os, const Appointment& appointment);



};

#endif // APPOINTMENT_H
