#include "../includes/medical_equipment.h"
#include <iostream>

using namespace std;

MedicalEquipment::MedicalEquipment()
    : InventoryItem(), warrantyMonths(24) {}

MedicalEquipment::MedicalEquipment(const std::string& name, double price, int warrantyMonths)
    : InventoryItem(name, price), warrantyMonths(warrantyMonths) {}

MedicalEquipment::MedicalEquipment(const MedicalEquipment& other)
    : InventoryItem(other), warrantyMonths(other.warrantyMonths) {}


double MedicalEquipment::getRentabilityScore() const {
    return (warrantyMonths > 0 && price > 0) ? static_cast<double>(warrantyMonths) / price : 0;
}

void MedicalEquipment::display(std::ostream& os) const {
    os << "[Equipment] ID: " << id << " | Name: " << name
       << " | Price: $" << price << " | Warranty: " << warrantyMonths << " months";
}

std::unique_ptr<InventoryItem> MedicalEquipment::clone() const {
    return std::make_unique<MedicalEquipment>(*this);
}

int MedicalEquipment::getWarrantyMonths() const {
    return warrantyMonths;
}
