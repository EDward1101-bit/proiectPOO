#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <set>
#include <iostream>
#include <set>

class Patient {
private:
    std::string name;
    std::string cnp;
    int age;
    char gender;
    std::set<std::string> diseases;

public:
    Patient(const std::string& name, const std::string& cnp, int age, char gender);
    Patient(const Patient& other);

    const std::string& getName() const;
    const std::string& getCNP() const;
    int getAge() const;
    char getGender() const;
    const std::set<std::string>& getDiseases() const;

    Patient& operator=(const Patient& other);

    ~Patient();



    void addDisease(const std::string& disease);
    void removeDisease(const std::string& disease);
    static bool isValidCNP(const std::string& cnp);
    std::string shortInfo() const;

    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);
};

#endif // PATIENT_H
