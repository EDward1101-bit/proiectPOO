#include "../includes/Internare.h"
#include "../includes/Doctor.h"
#include "../includes/Patient.h"
#include <iostream>

Internare::Internare(const std::string& data,
                     const std::string& ora,
                     Doctor* doctor,
                     Patient* pacient,
                     int nrZile,
                     double costPerZi)
    : ServiciuMedical(data, ora, doctor, pacient),
      nrZile(nrZile), costPerZi(costPerZi) {}

double Internare::getCost() const {
    return nrZile * costPerZi;
}

void Internare::print(std::ostream& os) const {
    os << "[INTERNARE] "
       << "Data: " << data
       << ", Ora: " << ora
       << ", Zile: " << nrZile
       << ", Cost/zi: " << costPerZi
       << ", Doctor: " << (doctor ? doctor->getName() : "N/A")
       << ", Pacient: " << (pacient ? pacient->getName() : "N/A");
}

std::unique_ptr<ServiciuMedical> Internare::clone() const {
    return std::make_unique<Internare>(*this);
}
