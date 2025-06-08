#include "../includes/inventory_item.h"

InventoryItem::InventoryItem() : id(++current_id), name("Unnamed"), price(0.0) {}

InventoryItem::InventoryItem(const std::string& name, double price)
    : id(++current_id), name(name), price(price) {}

InventoryItem::InventoryItem(const InventoryItem& other)
    : id(++current_id), name(other.name), price(other.price) {}

int InventoryItem::getId() const {
    return id;
}

double InventoryItem::priceValue() const {
    return price;
}
