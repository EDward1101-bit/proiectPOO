#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <iostream>
#include <map>

class Patient {
private:
    std::string name;
    int age;
    char gender;
    std::string cnp;
    double funds;
    std::map<std::string, double> diseases; // disease name -> treatment cost

public:
    // Constructor
    Patient(std::string name, int age, char gender, std::string cnp, double funds);

    // Accessors
    std::string const& getName() const;
    const std::map<std::string, double>& getDiseases() const;
    double getTotalTreatmentCost() const;
    double getFunds() const;
    std::string getCNP() const;

    // Mutators
    void addDisease(const std::string& disease, double cost);
    void removeDisease(const std::string& disease);
    void clearDiseases();
    bool isHealthy() const;
    void addFunds(double amount);
    void deductFunds(double amount);

    static bool isValidCNP(const std::string& cnp);

    void printInfo() const;

    // Rule of Three
    Patient(const Patient& other);
    Patient& operator=(const Patient& other);
    ~Patient();

    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif // PATIENT_H