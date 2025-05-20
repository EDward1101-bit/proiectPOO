#ifndef INTERVENTIE_CHIRURGICALA_H
#define INTERVENTIE_CHIRURGICALA_H

#include "ServiciuMedical.h"

class InterventieChirurgicala : public ServiciuMedical {
private:
    std::string tip;
    int durataOre;
    double costPeOra;
public:
    InterventieChirurgicala(const std::string& data,
                            const std::string& ora,
                            Doctor* doctor,
                            Patient* pacient,
                            const std::string& tip,
                            int durataOre,
                            double costPeOra = 500.0);

    double getCost() const override;
    void print(std::ostream& os) const override;
    std::unique_ptr<ServiciuMedical> clone() const override;
};

#endif // INTERVENTIE_CHIRURGICALA_H
