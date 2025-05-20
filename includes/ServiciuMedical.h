#ifndef SERVICIU_MEDICAL_H
#define SERVICIU_MEDICAL_H

#include <string>
#include <memory>
#include <iostream>


class Doctor;
class Patient;

class ServiciuMedical {
protected:
    std::string data;
    std::string ora;
    Doctor* doctor;
    Patient* pacient;

public:
    ServiciuMedical(const std::string& data,
                    const std::string& ora,
                    Doctor* doctor,
                    Patient* pacient)
        : data(data), ora(ora), doctor(doctor), pacient(pacient) {}

    virtual ~ServiciuMedical() = default;

    virtual double getCost() const = 0;
    virtual void print(std::ostream& os) const = 0;
    virtual std::unique_ptr<ServiciuMedical> clone() const = 0;

    void show() const {
        print(std::cout);
        std::cout << " → Cost: " << getCost() << " RON\n";
    }

    const std::string& getData() const { return data; }
    const std::string& getOra() const { return ora; }
    Doctor* getDoctor() const { return doctor; }
    Patient* getPatient() const { return pacient; }
};

#endif // SERVICIU_MEDICAL_H
