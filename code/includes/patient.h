#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>

class Patient {
private:
    std::string name;
    std::string disease;
    std::string CNP;
    int age;
    char gender;

public:
    // Constructor
    Patient(std::string name, int age, char gender, std::string disease);

    const std::string getCNP() const;
    void updateDisease(const std::string& newDisease);  // Update the disease info
    void printInfo() const;  // Print patient info

    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif // PATIENT_H
