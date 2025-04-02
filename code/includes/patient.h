#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>

class Patient {
private:
    std::string name;
    int age;
    char gender;
    std::string disease;

public:
    // Constructor
    Patient(std::string name, int age, char gender, std::string disease);
    void updateDisease(const std::string& newDisease);  // Update the disease info
    void printInfo() const;  // Print patient info
    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif // PATIENT_H
