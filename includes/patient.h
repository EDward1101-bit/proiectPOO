#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <set>
#include <iostream>
#include <set>
#include <vector>
#include <memory>
#include "ServiciuMedical.h"

class Patient {
private:
    std::string name;
    std::string cnp;
    int age;
    char gender;
    std::set<std::string> diseases;
    std::vector<std::shared_ptr<ServiciuMedical>> istoricServicii;
    bool esteExternat = false;
    bool esteHealthy = false;


public:
    Patient(const std::string& name, const std::string& cnp, int age, char gender);
    Patient(const Patient& other);

    const std::string& getName() const;
    const std::string& getCNP() const;
    int getAge() const;
    char getGender() const;
    const std::set<std::string>& getDiseases() const;

    void adaugaServiciu(const std::shared_ptr<ServiciuMedical>& serviciu);
    bool esteBolnav() const;
    bool esteProcesabil() const;
    void setExternat(bool);
    bool getExternat() const;
    void setHealthy(bool);
    bool getHealthy() const;
    double calculeazaCostTotal() const;
    const std::vector<std::shared_ptr<ServiciuMedical>>& getIstoric() const;


    Patient& operator=(const Patient& other);

    ~Patient();



    void addDisease(const std::string& disease);
    void removeDisease(const std::string& disease);
    static bool isValidCNP(const std::string& cnp);

    friend std::ostream& operator<<(std::ostream& os, const Patient& patient);
};

#endif // PATIENT_H
