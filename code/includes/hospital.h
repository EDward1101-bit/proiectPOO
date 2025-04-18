#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <iostream>
#include <string>
#include <vector>
#include "doctor.h"
#include "patient.h"
#include "appointment.h"

class Hospital {
private:
    std::string name;
    std::string location;
    std::vector<Doctor*> doctors;
    std::vector<Appointment*> appointments;

public:
    Hospital(std::string name, std::string location);
    void addDoctor(Doctor* doctor);
    void addPatientToDoctor(const std::string& doctorName, Patient* p);
    bool isDoctorAvailable(const std::string& doctorName, const std::string& date, const std::string& time) const;
    void scheduleAppointment(const std::string& doctorName, Patient* patient, const std::string& date, const std::string& time);
    void printInfo() const;
    void printDoctors() const;
    void printAppointments() const;
    friend std::ostream& operator<<(std::ostream& os, const Hospital& h);
};

#endif // HOSPITAL_H
