#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include <vector>
#include "doctor.h"
#include "appointment.h"
#include "patient.h"

class Doctor;
class Appointment;
class Patient;

class Hospital {
private:
    std::string name;
    std::string location;
    std::vector<Doctor*> doctors;
    std::vector<Appointment*> appointments;

public:
    // Constructor
    Hospital(std::string name, std::string location);
    void addDoctor(Doctor* doctor);
    void addAppointment(Appointment* appointment);
    void addPatientToDoctor(const std::string& doctorName, Patient* patient);
    bool isDoctorAvailable(const std::string& doctorName, const std::string& date, const std::string& time) const;
    void scheduleAppointment(const std::string& doctorName, Patient* patient, const std::string& date, const std::string& time);
    void printInfo() const;
    void printDoctors() const;
    void printAppointments() const;

    friend std::ostream& operator<<(std::ostream& os, const Hospital& hospital);
};

#endif // HOSPITAL_H