#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>

class Doctor {
private:
    std::string name;
    std::string specialty;

public:
    explicit Doctor(std::string name, std::string specialty);
    std::string getName() const;
    void changeSpecialty(const std::string& newSpecialty);
    void printInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const Doctor& d);
};

#endif // DOCTOR_H
