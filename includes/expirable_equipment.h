#ifndef EXPIRABLE_EQUIPMENT_H
#define EXPIRABLE_EQUIPMENT_H

#include "medication.h"
#include "medical_equipment.h"

class ExpirableEquipment : public Medication, public MedicalEquipment {
public:
    ExpirableEquipment();
    ExpirableEquipment(const std::string& name, double price,
                       const std::chrono::sys_days& expiryDate, int warrantyMonths);
    ExpirableEquipment(const ExpirableEquipment& other);

    bool isExpiringSoon() const override;
    double getRentabilityScore() const override;
    void display(std::ostream& os) const override;
    std::unique_ptr<InventoryItem> clone() const override;
};

#endif // EXPIRABLE_EQUIPMENT_H
