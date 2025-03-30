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
    const std::string& getName() const;  // Fixed: Return by const reference
    void changeSpecialty(const std::string& newSpecialty);
    void printInfo() const;
    friend std::ostream& operator<<(std::ostream& os, const Doctor& d);
};

#endif // DOCTOR_H
