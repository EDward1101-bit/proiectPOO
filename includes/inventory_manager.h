#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include <map>
#include "inventory_item.h"

class InventoryManager {
private:
    std::vector<std::unique_ptr<InventoryItem>> items;
    double budget;
    InventoryManager();

    std::unique_ptr<InventoryItem> parseCSVLine(const std::string& line) const;

public:

    static InventoryManager& getInstance();
    void loadFromCSV(const std::string& filename);
    void saveToCSV(const std::string& filename) const;

    void loadBudget(const std::string& filename);
    void saveBudget(const std::string& filename) const;

    void addItem(std::unique_ptr<InventoryItem> item);
    void addItemFromTemplate();

    void removeItemById(int id);
    void cloneMostRentableItem();

    void listAll() const;
    void listSortedByRentability() const;
    void listExpiringSoon() const;

    void autoManage();
    void showMenu();

    InventoryManager(const InventoryManager&) = delete;
    InventoryManager& operator=(const InventoryManager&) = delete;
    InventoryManager(InventoryManager&&) = delete;
    InventoryManager& operator=(InventoryManager&&) = delete;
};

#endif // INVENTORY_MANAGER_H
