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

    std::string const& getName() const;
    const std::map<std::string, double>& getDiseases() const;
    double getTotalTreatmentCost() const;
    double getFunds() const;

    void addDisease(const std::string& disease, double cost);
    void removeDisease(const std::string& disease);
    void clearDiseases();
    bool isHealthy() const;
    void addFunds(double amount);
    void deductFunds(double amount);

    static bool isValidCNP(const std::string& cnp);
    static bool isValidDisease(const std::string& disease);
    static bool isValidName(const std::string& name);

    void printInfo() const;

    Patient(const Patient& other);
    Patient& operator=(const Patient& other);
    ~Patient();

    friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif // PATIENT_H
