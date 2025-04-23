#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <vector>
#include "patient.h"
#include "appointment.h"

class Patient;
class Appointment;

class Doctor {
private:
    std::string name;
    std::string specialty;
    std::vector<Patient*> patients;
    std::vector<Appointment*> appointments;

public:
    Doctor(std::string name, std::string specialty);

    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getSpecialty() const;
    [[nodiscard]] const std::vector<Patient*>& getPatientList() const;
    [[nodiscard]] const std::vector<Appointment*>& getAppointments() const;

    void addAppointment(Appointment* appointment);
    void assignPatient(Patient* p);
    void removePatient(const Patient* p);

    void printInfo() const;
    void printPatients() const;

    ~Doctor();

    friend std::ostream& operator<<(std::ostream& os, const Doctor& d);

    static bool isValidSpecialty(const std::string& specialty);
};

#endif // DOCTOR_H