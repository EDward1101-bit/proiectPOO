#ifndef INTERNARE_H
#define INTERNARE_H

#include "ServiciuMedical.h"

class Internare : public ServiciuMedical {
private:
    int nrZile;
    double costPerZi;
public:
    Internare(const std::string& data,
              const std::string& ora,
              Doctor* doctor,
              Patient* pacient,
              int nrZile,
              double costPerZi = 300.0);

    double getCost() const override;
    void print(std::ostream& os) const override;
    std::unique_ptr<ServiciuMedical> clone() const override;
};

#endif // INTERNARE_H
