#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Doctor;
class Appointment;
class Patient;

class Hospital {
private:
    std::string name;
    std::vector<std::unique_ptr<Doctor>> doctors;
    std::vector<std::unique_ptr<Appointment>> appointments;

public:
    explicit Hospital(const std::string& name);

    Hospital(const Hospital& other);
    Hospital& operator=(const Hospital& other);
    ~Hospital();

    const std::string& getName() const;
    const std::vector<std::unique_ptr<Doctor>>& getDoctors() const;

    void addDoctor(std::unique_ptr<Doctor> doctor);
    void addAppointment(std::unique_ptr<Appointment> appointment);
    Doctor* findDoctorByName(const std::string& name) const;
    bool isDoctorAvailable(const Doctor* doctor, const std::string& date, const std::string& time) const;

    void listAllDoctors() const;
    void listAllAppointments() const;

    friend std::ostream& operator<<(std::ostream& os, const Hospital& hospital);
};

#endif // HOSPITAL_H
