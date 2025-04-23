#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include <vector>
#include <memory>
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
    std::vector<std::unique_ptr<Doctor>> doctors;
    std::vector<std::unique_ptr<Appointment>> appointments;
    double totalProfit = 0.0;

public:
    Hospital(std::string name, Location location);
    // Copy operations are deleted to avoid issues with unique_ptr
    Hospital(const Hospital& other) = delete;
    Hospital& operator=(const Hospital& other) = delete;
    ~Hospital();

    void addDoctor(std::unique_ptr<Doctor> doctor);
    void addAppointment(std::unique_ptr<Appointment> appointment);
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