#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include <vector>
#include "doctor.h"
#include "appointment.h"
#include "patient.h"
#include "location.h"

class Doctor;
class Appointment;
class Patient;

class Hospital {
private:
    std::string name;
    Location location;
    std::vector<Doctor*> doctors;
    std::vector<Appointment*> appointments;
    double totalProfit = 0.0;

public:
    Hospital(std::string name, Location location);
    Hospital(const Hospital& other);
    Hospital& operator=(const Hospital& other);
    ~Hospital();

    void addDoctor(Doctor* doctor);
    void addAppointment(Appointment* appointment);
    void addPatientToDoctor(const std::string& doctorName, Patient* patient);
    bool isDoctorAvailable(const std::string& doctorName, const std::string& date, const std::string& time) const;
    void scheduleAppointment(const std::string& doctorName, Patient* patient, const std::string& date, const std::string& time);
    void dischargePatient(Patient* patient, Doctor* doctor);

    double getProfit() const;
    void printInfo() const;
    void printDoctors() const;
    void printAppointments() const;

    friend std::ostream& operator<<(std::ostream& os, const Hospital& hospital);
};

#endif // HOSPITAL_H
