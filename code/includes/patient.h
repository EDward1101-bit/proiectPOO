#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>

class Patient {
private:
    static int next_idPatient;
    int id;
    std::string name;
    std::string disease;
    int age;
    char gender;

public:
    // Constructor
    Patient(std::string name, int age, char gender, std::string disease);
    const int getId() const;
    void updateDisease(const std::string& newDisease);  // Update the disease info
    void printInfo() const;  // Print patient info
    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif // PATIENT_H
