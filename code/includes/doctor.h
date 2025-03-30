#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>

class Doctor {
private:
    std::string name;
    std::string specialty;

public:
    // Constructor
    explicit Doctor(std::string name, std::string specialty);

    // Getter for name (added)
    std::string getName() const;

    // Public member functions
    void changeSpecialty(const std::string& newSpecialty);
    void printInfo() const;

    // Operator<< Overload
    friend std::ostream& operator<<(std::ostream& os, const Doctor& d);
};

#endif // DOCTOR_H
