#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>
#include <vector>

class Doctor {
private:
    std::string name;
    std::string specialty;
    std::vector<std::string> availableDays;  // Days when the doctor is available

public:
    // Constructor
    Doctor(std::string name, std::string specialty, std::vector<std::string> availableDays);

    // Copy Constructor
    Doctor(const Doctor& other);

    // Copy Assignment Operator
    Doctor& operator=(const Doctor& other);

    // Destructor
    ~Doctor();

    // Public member functions
    void changeSpecialty(const std::string& newSpecialty);
    void addAvailableDay(const std::string& day);
    void printInfo() const;
    bool isAvailableOn(const std::string& day) const;

    // Operator<< Overload
    friend std::ostream& operator<<(std::ostream& os, const Doctor& d);
};

#endif // DOCTOR_H
