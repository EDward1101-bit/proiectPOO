#ifndef INVENTORY_ITEM_H
#define INVENTORY_ITEM_H

#include <string>
#include <memory>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

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

    // Funcții virtuale pure sau overridable
    virtual std::unique_ptr<InventoryItem> clone() const = 0;
    virtual void display(std::ostream& os) const = 0;
    virtual bool isExpiringSoon() const { return false; }
    virtual double getRentabilityScore() const { return 0; }

    double priceValue() const;
    int getId() const;
    bool hasName(const std::string& query) const;
};

inline std::ostream& operator<<(std::ostream& os, const InventoryItem& item) {
    item.display(os);
    return os;
}

#endif // INVENTORY_ITEM_H
