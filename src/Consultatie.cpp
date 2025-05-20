#include "../includes/Consultatie.h"
#include "../includes/Doctor.h"
#include "../includes/Patient.h"
#include <iostream>

Consultatie::Consultatie(const std::string& data,
                         const std::string& ora,
                         Doctor* doctor,
                         Patient* pacient,
                         double cost)
    : ServiciuMedical(data, ora, doctor, pacient), cost(cost) {}

double Consultatie::getCost() const {
    return cost;
}

void Consultatie::print(std::ostream& os) const {
    os << "[CONSULTATIE] "
       << "Data: " << data
       << ", Ora: " << ora
       << ", Doctor: " << (doctor ? doctor->getName() : "N/A")
       << ", Pacient: " << (pacient ? pacient->getName() : "N/A");
}

std::unique_ptr<ServiciuMedical> Consultatie::clone() const {
    return std::make_unique<Consultatie>(*this);
}
