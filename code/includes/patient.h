#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>

class Patient {
private:
    std::string name;
    int age;
    char gender;
    std::string disease;

public:
    // Constructor
    Patient(std::string name, int age, char gender, std::string disease);

    std::string const& getName() const;
    std::string const& getDisease() const;
    void updateDisease(const std::string& newDisease);
    void printInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif // PATIENT_H
