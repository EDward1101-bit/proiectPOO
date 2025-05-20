#ifndef TRATAMENT_SPECIALIZAT_H
#define TRATAMENT_SPECIALIZAT_H

#include "ServiciuMedical.h"

class TratamentSpecializat : public ServiciuMedical {
private:
    std::string boala;
    double cost;
public:
    TratamentSpecializat(const std::string& data,
                         const std::string& ora,
                         Doctor* doctor,
                         Patient* pacient,
                         const std::string& boala,
                         double cost);

    double getCost() const override;
    void print(std::ostream& os) const override;
    std::unique_ptr<ServiciuMedical> clone() const override;
};

#endif // TRATAMENT_SPECIALIZAT_H
