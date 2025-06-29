#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

#include <string>
#include <memory>
#include <iostream>

class InventoryItem {
protected:
    int id;
    std::string name;
    double price;
    static inline int current_id = 0;

public:
    InventoryItem();
    InventoryItem(const std::string& name, double price);
    InventoryItem(const InventoryItem& other);
    virtual ~InventoryItem() = default;

    virtual void saveToCSV(std::ostream& out) const = 0;

    virtual void display(std::ostream& os) const = 0;
    virtual std::unique_ptr<InventoryItem> clone() const = 0;

    virtual bool isExpiringSoon() const { return false; }
    virtual double getRentabilityScore() const { return 0; }

    int getId() const;
    const std::string& getName() const { return name; }
    double priceValue() const;
};

inline std::ostream& operator<<(std::ostream& os, const InventoryItem& item) {
    item.display(os);
    return os;
}

#endif // INVENTORY_ITEM_H
