#ifndef NURSE_H
#define NURSE_H

#include <string>
#include <iostream>

class Nurse {
private:
    std::string name;
    std::string speciality;
    int age;
    int yearsWorked;

public:
    explicit Nurse(std::string name, std::string speciality, int age, int yearsWorked);

    const std::string& getName() const { return name; }
    const std::string& getSpeciality() const { return speciality; }
    int getAge() const { return age; }
    int getYearsWorked() const { return yearsWorked; }

    // Operator<< to print Nurse info
    friend std::ostream& operator<<(std::ostream& os, const Nurse& nurse) {
        os << "Nurse: " << nurse.name << ", Speciality: " << nurse.speciality
           << ", Age: " << nurse.age << ", Years Worked: " << nurse.yearsWorked;
        return os;
    }
};

#endif // NURSE_H
