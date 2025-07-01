#ifndef INVENTORY_ITEM_TEMPLATE_H
#define INVENTORY_ITEM_TEMPLATE_H

#include "inventory_item.h"
#include <string>
#include <iostream>
#include <memory>

template<typename T>
class InventoryItemTemplate : public InventoryItem {
private:
    T extraInfo;

public:
    InventoryItemTemplate(const std::string& name, double price, const T& extraInfo)
        : InventoryItem(name, price), extraInfo(extraInfo) {}

    const T& getExtraInfo() const {
        return extraInfo;
    }

    void display(std::ostream& os) const override {
        os << "[Item] ID: " << getId()
           << " | Name: " << getName()
           << " | Price: $" << priceValue()
           << " | Extra: " << extraInfo;
    }

    std::unique_ptr<InventoryItem> clone() const override {
        return std::make_unique<InventoryItemTemplate<T>>(*this);
    }

    void saveToCSV(std::ostream& out) const override {
        out << "InventoryItemTemplate," << getName() << "," << priceValue() << "," << extraInfo << "\n";
    }
};

#endif // INVENTORY_ITEM_TEMPLATE_H
