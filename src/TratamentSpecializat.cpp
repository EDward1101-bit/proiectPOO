#include "../includes/TratamentSpecializat.h"
#include "../includes/Doctor.h"
#include "../includes/Patient.h"
#include <iostream>

TratamentSpecializat::TratamentSpecializat(const std::string& data,
                                           const std::string& ora,
                                           Doctor* doctor,
                                           Patient* pacient,
                                           const std::string& boala,
                                           double cost)
    : ServiciuMedical(data, ora, doctor, pacient),
      boala(boala), cost(cost) {}

double TratamentSpecializat::getCost() const {
    return cost;
}

void TratamentSpecializat::print(std::ostream& os) const {
    os << "[TRATAMENT] "
       << "Data: " << data
       << ", Ora: " << ora
       << ", Boala: " << boala
       << ", Cost: " << cost
       << ", Doctor: " << (doctor ? doctor->getName() : "N/A")
       << ", Pacient: " << (pacient ? pacient->getName() : "N/A");
}

std::unique_ptr<ServiciuMedical> TratamentSpecializat::clone() const {
    return std::make_unique<TratamentSpecializat>(*this);
}
