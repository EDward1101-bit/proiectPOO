#ifndef MEDICAL_EQUIPMENT_H
#define MEDICAL_EQUIPMENT_H

#include "inventory_item.h"

class MedicalEquipment : virtual public InventoryItem {
protected:
    int warrantyMonths;

public:
    MedicalEquipment();
    MedicalEquipment(const std::string& name, double price, int warrantyMonths);
    MedicalEquipment(const MedicalEquipment& other);

    bool isExpiringSoon() const override;  // echipamentele nu expiră, doar se strică
    double getRentabilityScore() const override;
    void display(std::ostream& os) const override;
    std::unique_ptr<InventoryItem> clone() const override;

    int getWarrantyMonths() const;
};

#endif // MEDICAL_EQUIPMENT_H
