#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include <vector>
#include <memory>
#include <map>
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
    Hospital(std::string name, const Location& location);
    Hospital(const Hospital& other) = delete;
    Hospital& operator=(const Hospital& other) = delete;
    ~Hospital();

    void addDoctor(std::unique_ptr<Doctor> doctor);
    void addAppointment(std::unique_ptr<Appointment> appointment);
    void addPatientToDoctor(const std::string& doctorName, Patient* patient);
    [[nodiscard]] bool isDoctorAvailable(const std::string& doctorName, const std::string& date, const std::string& time) const;
    void scheduleAppointment(const std::string& doctorName, Patient* patient, const std::string& date, const std::string& time);
    void dischargePatient(Patient* patient, Doctor* doctor);

    [[nodiscard]] double getProfit() const;
    void printInfo() const;
    void printDoctors() const;
    void printAppointments() const;

    [[nodiscard]] std::vector<std::pair<std::string, int>> getMostCommonDiseases(int topN = 5) const;
    [[nodiscard]] const std::vector<std::unique_ptr<Doctor>>& getDoctors() const;

    friend std::ostream& operator<<(std::ostream& os, const Hospital& hospital);
};

#endif // HOSPITAL_H
