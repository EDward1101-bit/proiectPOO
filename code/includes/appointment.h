#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <string>
#include <iostream>
class Doctor;

class Appointment {
private:
    std::string date;
    std::string time;
    Doctor* doctor;
    int timezoneOffset;

public:
    Appointment(const std::string& date, const std::string& time, Doctor* doctor, int timezoneOffset);
    Appointment(const Appointment& other);
    Appointment& operator=(const Appointment& other);
    ~Appointment();

    [[nodiscard]] const std::string& getDate() const;
    [[nodiscard]] const std::string& getTime() const;
    [[nodiscard]] int getTimezoneOffset() const;
    [[nodiscard]] bool isDoctorAvailable(const std::string& checkDate, const std::string& checkTime, int tzOffset) const;

    static bool isValidDateTime(const std::string& inputDate, const std::string& inputTime, int timezoneOffset);

    void printInfo() const;
    friend std::ostream& operator<<(std::ostream& os, const Appointment& app);
};

#endif // APPOINTMENT_H