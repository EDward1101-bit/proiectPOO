#ifndef MEDICATION_H
#define MEDICATION_H

#include "inventory_item.h"
#include <chrono>

class Medication : virtual public InventoryItem {
protected:
    std::chrono::sys_days expiryDate;

public:
    Medication();
    Medication(const std::string& name, double price, const std::chrono::sys_days& expiryDate);
    Medication(const Medication& other);

    bool isExpiringSoon() const override;
    double getRentabilityScore() const override;
    void display(std::ostream& os) const override;
    std::unique_ptr<InventoryItem> clone() const override;

    std::chrono::sys_days getExpiryDate() const;

    static std::chrono::sys_days parseDate(const std::string& dateStr);
    static std::string formatDate(const std::chrono::sys_days& date);
};

#endif // MEDICATION_H
