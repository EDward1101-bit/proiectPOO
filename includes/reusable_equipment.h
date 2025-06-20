#ifndef REUSABLE_EQUIPMENT_H
#define REUSABLE_EQUIPMENT_H

#include "medical_equipment.h"

class ReusableEquipment : public MedicalEquipment {
private:
    int usageLimit;
    int currentUsage;

public:
    ReusableEquipment();
    ReusableEquipment(const std::string& name, double price, int warranty, int usageLimit, int currentUsage = 0);
    ReusableEquipment(const ReusableEquipment& other);

    bool isExpiringSoon() const override;
    double getRentabilityScore() const override;
    void display(std::ostream& os) const override;
    std::unique_ptr<InventoryItem> clone() const override;

    int getUsageLeft() const;
};

#endif // REUSABLE_EQUIPMENT_H
