#include "../includes/InterventieChirurgicala.h"
#include "../includes/Doctor.h"
#include "../includes/Patient.h"
#include <iostream>

InterventieChirurgicala::InterventieChirurgicala(const std::string& data,
                                                 const std::string& ora,
                                                 Doctor* doctor,
                                                 Patient* pacient,
                                                 const std::string& tip,
                                                 int durataOre,
                                                 double costPeOra)
    : ServiciuMedical(data, ora, doctor, pacient),
      tip(tip), durataOre(durataOre), costPeOra(costPeOra) {}

double InterventieChirurgicala::getCost() const {
    return durataOre * costPeOra;
}

void InterventieChirurgicala::print(std::ostream& os) const {
    os << "[INTERVENȚIE CHIRURGICALĂ] "
       << "Tip: " << tip
       << ", Data: " << data
       << ", Ora: " << ora
       << ", Durata: " << durataOre << " ore"
       << ", Doctor: " << (doctor ? doctor->getName() : "N/A")
       << ", Pacient: " << (pacient ? pacient->getName() : "N/A");
}

std::unique_ptr<ServiciuMedical> InterventieChirurgicala::clone() const {
    return std::make_unique<InterventieChirurgicala>(*this);
}
