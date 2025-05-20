#ifndef CONSULTATIE_H
#define CONSULTATIE_H

#include "ServiciuMedical.h"

class Consultatie : public ServiciuMedical {
private:
    double cost;
public:
    Consultatie(const std::string& data,
                const std::string& ora,
                Doctor* doctor,
                Patient* pacient,
                double cost = 100.0);

    double getCost() const override;
    void print(std::ostream& os) const override;
    std::unique_ptr<ServiciuMedical> clone() const override;
};

#endif // CONSULTATIE_H
