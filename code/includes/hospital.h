#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "doctor.h"
#include "nurse.h"
#include <vector>
#include <iostream>

class Spital {
private:
    std::string name;
    std::vector<Doctor*> doctors;
    std::vector<Nurse*> nurses;

public:
    explicit Spital(std::string name);

    void assignDoctor(Doctor* doc);
    void assignNurse(Nurse* nurse);
    void printDoctors() const;
    void printNurses() const;

    Spital& operator=(const Spital& other);

    friend std::ostream& operator<<(std::ostream& os, const Spital& spital);

    ~Spital();
};

#endif // HOSPITAL_H
