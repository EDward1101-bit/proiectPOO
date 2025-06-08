#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include "inventory_item.h"

#include <unordered_map>
#include <map>

class InventoryManager {
private:
    std::vector<std::unique_ptr<InventoryItem>> items;
    double budget;

    // Preset
    std::map<std::string, int> presetLimits;
    std::map<std::string, int> presetCount;

    std::unique_ptr<InventoryItem> parseCSVLine(const std::string& line) const;

public:
    InventoryManager();

    void loadFromCSV(const std::string& filename);
    void saveToCSV(const std::string& filename) const;

    void loadBudget(const std::string& filename);
    void saveBudget(const std::string& filename) const;

    void addItem(std::unique_ptr<InventoryItem> item);
    void addItemFromPreset();

    void removeItemById(int id);
    void listAll() const;
    void listSortedByRentability() const;
    void listExpiringSoon() const;

    void autoManage();
    void showMenu();
};
#endif // INVENTORY_MANAGER_H
