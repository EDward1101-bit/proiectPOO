#ifndef MEDICATION_H
#define MEDICATION_H

#include "inventory_item.h"
#include <chrono>
#include <iomanip>
#include <sstream>


class Medication : public InventoryItem {
private:
    std::chrono::sys_days expiryDate;

public:
    Medication();
    Medication(const std::string& name, double price, const std::chrono::sys_days& expiryDate);
    Medication(const Medication& other);

    bool isExpiringSoon() const override;
    double getRentabilityScore() const override;
    void display(std::ostream& os) const override;
    std::unique_ptr<InventoryItem> clone() const override;


    static std::chrono::sys_days parseDate(const std::string& dateStr);
    static std::string formatDate(const std::chrono::sys_days& date);
};

#endif // MEDICATION_H
