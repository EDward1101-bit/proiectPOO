#include "../includes/reusable_equipment.h"
#include <iostream>

ReusableEquipment::ReusableEquipment()
    : MedicalEquipment(), usageLimit(10), currentUsage(0) {}

ReusableEquipment::ReusableEquipment(const std::string& name, double price, int warranty, int usageLimit, int currentUsage)
    : InventoryItem(name, price),  // ADĂUGAT
      MedicalEquipment(name, price, warranty),
      usageLimit(usageLimit),
      currentUsage(currentUsage) {}

ReusableEquipment::ReusableEquipment(const ReusableEquipment& other)
    : InventoryItem(other),
      MedicalEquipment(other),
      usageLimit(other.usageLimit),
      currentUsage(other.currentUsage) {}

bool ReusableEquipment::isExpiringSoon() const {
    return currentUsage >= usageLimit;
}

double ReusableEquipment::getRentabilityScore() const {
    int remainingUses = usageLimit - currentUsage;
    return (remainingUses > 0 && price > 0) ? static_cast<double>(remainingUses * getWarrantyMonths()) / price : 0;
}

void ReusableEquipment::display(std::ostream& os) const {
    os << "[ReusableEquipment] ID: " << getId()
       << " | Name: " << getName()
       << " | Price: $" << priceValue()
       << " | Warranty: " << getWarrantyMonths() << " months"
       << " | Usage: " << currentUsage << "/" << usageLimit;
    if (isExpiringSoon()) os << " ⚠️ MAX USAGE REACHED";
}

std::unique_ptr<InventoryItem> ReusableEquipment::clone() const {
    return std::make_unique<ReusableEquipment>(*this);
}

int ReusableEquipment::getUsageLeft() const {
    return usageLimit - currentUsage;
}

