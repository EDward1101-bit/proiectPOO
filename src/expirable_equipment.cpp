#include "../includes/expirable_equipment.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

ExpirableEquipment::ExpirableEquipment()
    : Medication(), MedicalEquipment() {}

ExpirableEquipment::ExpirableEquipment(const std::string& name, double price,
                                       const std::chrono::sys_days& expiryDate, int warrantyMonths)
    : InventoryItem(name, price),
      Medication(name, price, expiryDate),
      MedicalEquipment(name, price, warrantyMonths) {}


ExpirableEquipment::ExpirableEquipment(const ExpirableEquipment& other)
    : InventoryItem(other),
      Medication(other),
      MedicalEquipment(other) {}

bool ExpirableEquipment::isExpiringSoon() const {
    return Medication::isExpiringSoon();  // delegare
}

double ExpirableEquipment::getRentabilityScore() const {
    auto today = floor<days>(system_clock::now());
    auto daysLeft = duration_cast<days>(
        Medication::getExpiryDate() - today).count();

    return (daysLeft + getWarrantyMonths() * 30) / priceValue();
}

void ExpirableEquipment::display(std::ostream& os) const {
    os << "[ExpirableEquipment] ID: " << getId()
       << " | Name: " << InventoryItem::name
       << " | Price: $" << InventoryItem::price
       << " | Expiry: " << Medication::formatDate(getExpiryDate())
       << " | Warranty: " << getWarrantyMonths() << " months";
    if (isExpiringSoon()) os << " ⚠️ EXPIRING SOON";
}

std::unique_ptr<InventoryItem> ExpirableEquipment::clone() const {
    return std::make_unique<ExpirableEquipment>(*this);
}

void ExpirableEquipment::saveToCSV(std::ostream& out) const {
    out << "ExpirableEquipment," << getName() << "," << priceValue()
        << "," << Medication::formatDate(getExpiryDate())
        << "," << getWarrantyMonths() << "\n";
}
