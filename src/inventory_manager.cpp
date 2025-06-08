#include "../includes/inventory_manager.h"
#include "../includes/medication.h"
#include "../includes/medical_equipment.h"
#include "../includes/expirable_equipment.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

InventoryManager::InventoryManager() : budget(0.0) {
    presetLimits["Paracetamol"] = 3;
    presetLimits["Defibrillator"] = 3;
    presetLimits["BatteryDefibKit"] = 3;

    presetCount["Paracetamol"] = 0;
    presetCount["Defibrillator"] = 0;
    presetCount["BatteryDefibKit"] = 0;
}


void InventoryManager::loadFromCSV(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Error opening inventory file.\n";
        return;
    }

    string line;
    while (getline(fin, line)) {
        try {
            auto item = parseCSVLine(line);
            if (item) items.push_back(std::move(item));
        } catch (...) {
            cerr << "Failed to parse line: " << line << "\n";
        }
    }
}

void InventoryManager::saveToCSV(const string& filename) const {
    ofstream fout(filename, ios::trunc);
    for (const auto& item : items) {
        if (auto m = dynamic_cast<const Medication*>(item.get())) {
            fout << "Medication," << m->hasName("") << "," << m->priceValue() << ","
                 << Medication::formatDate(m->parseDate(Medication::formatDate(m->parseDate("2025-12-01")))) << "\n";
        } else if (auto e = dynamic_cast<const MedicalEquipment*>(item.get())) {
            fout << "Equipment," << e->hasName("") << "," << e->priceValue() << "," << e->getRentabilityScore() << "\n";
        } else if (auto x = dynamic_cast<const ExpirableEquipment*>(item.get())) {
            fout << "ExpirableEquipment," << x->hasName("") << "," << x->priceValue() << ","
                 << Medication::formatDate(x->parseDate("2025-12-01")) << "," << x->getRentabilityScore() << "\n";
        }
    }
}

std::unique_ptr<InventoryItem> InventoryManager::parseCSVLine(const string& line) const {
    istringstream iss(line);
    string type, name, priceStr, data1, data2;
    getline(iss, type, ',');
    getline(iss, name, ',');
    getline(iss, priceStr, ',');
    getline(iss, data1, ',');
    getline(iss, data2);

    double price = stod(priceStr);

    if (type == "Medication") {
        auto date = Medication::parseDate(data1);
        return make_unique<Medication>(name, price, date);
    } else if (type == "Equipment") {
        int warranty = stoi(data1);
        return make_unique<MedicalEquipment>(name, price, warranty);
    } else if (type == "ExpirableEquipment") {
        auto date = Medication::parseDate(data1);
        int warranty = stoi(data2);
        return make_unique<ExpirableEquipment>(name, price, date, warranty);
    }

    return nullptr;
}

void InventoryManager::loadBudget(const string& filename) {
    ifstream fin(filename);
    fin >> budget;
}

void InventoryManager::saveBudget(const string& filename) const {
    ofstream fout(filename, ios::trunc);
    fout << budget;
}

void InventoryManager::addItem(std::unique_ptr<InventoryItem> item) {
    if (item->priceValue() > budget) {
        cerr << "Insufficient funds for: ";
        item->display(cerr);
        cerr << "\n";
        return;
    }

    budget -= item->priceValue();
    items.push_back(std::move(item));
    cout << "Item added. Remaining budget: $" << budget << "\n";
}

void InventoryManager::removeItemById(int id) {
    auto it = remove_if(items.begin(), items.end(), [id](const auto& item) {
        return item->getId() == id;
    });

    if (it != items.end()) {
        items.erase(it, items.end());
        cout << "Item removed.\n";
    } else {
        cout << "Item not found.\n";
    }
}

void InventoryManager::listAll() const {
    cout << "--- INVENTORY ---\n";
    for (const auto& item : items) {
        cout << *item << "\n";
    }
}

void InventoryManager::listSortedByRentability() const {
    vector<const InventoryItem*> sorted;
    for (const auto& item : items) sorted.push_back(item.get());

    sort(sorted.begin(), sorted.end(), [](const auto* a, const auto* b) {
        return a->getRentabilityScore() > b->getRentabilityScore();
    });

    cout << "--- SORTED BY RENTABILITY ---\n";
    for (const auto* item : sorted) {
        cout << *item << " | Score: " << item->getRentabilityScore() << "\n";
    }
}

void InventoryManager::listExpiringSoon() const {
    cout << "--- EXPIRING SOON ---\n";
    for (const auto& item : items) {
        if (item->isExpiringSoon()) cout << *item << "\n";
    }
}
void InventoryManager::addItemFromPreset() {
    cout << "\nAvailable options:\n"
         << "1. Paracetamol (Medication)\n"
         << "2. Defibrillator (Equipment)\n"
         << "3. BatteryDefibKit (ExpirableEquipment)\n"
         << "Choose (1-3): ";

    std::string opt;
    getline(cin, opt);

    string name;
    double price;
    std::unique_ptr<InventoryItem> item;

    if (opt == "1") {
        name = "Paracetamol";
        if (presetCount[name] >= presetLimits[name])
            throw std::runtime_error("Limit reached for " + name);

        price = 5.0;
        auto expiry = chrono::floor<chrono::days>(chrono::system_clock::now()) + chrono::days(180);
        item = std::make_unique<Medication>(name, price, expiry);
    }
    else if (opt == "2") {
        name = "Defibrillator";
        if (presetCount[name] >= presetLimits[name])
            throw std::runtime_error("Limit reached for " + name);

        price = 800.0;
        item = std::make_unique<MedicalEquipment>(name, price, 24);
    }
    else if (opt == "3") {
        name = "BatteryDefibKit";
        if (presetCount[name] >= presetLimits[name])
            throw std::runtime_error("Limit reached for " + name);

        price = 300.0;
        auto expiry = chrono::floor<chrono::days>(chrono::system_clock::now()) + chrono::days(365);
        item = std::make_unique<ExpirableEquipment>(name, price, expiry, 12);
    }
    else {
        throw std::runtime_error("Invalid option.");
    }

    if (item->priceValue() > budget) {
        throw std::runtime_error("Insufficient funds.");
    }

    presetCount[name]++;
    addItem(std::move(item));
}

void InventoryManager::autoManage() {
    std::vector<std::unique_ptr<InventoryItem>> keptItems;
    int sold = 0, replaced = 0;

    for (auto& item : items) {
        if (item->isExpiringSoon()) {
            sold++;
            budget += item->priceValue() * 0.25; // Recuperezi 25%
            std::string name;

            if (auto m = dynamic_cast<Medication*>(item.get()))
                name = "Paracetamol";
            else if (auto e = dynamic_cast<MedicalEquipment*>(item.get()))
                name = "Defibrillator";
            else if (auto x = dynamic_cast<ExpirableEquipment*>(item.get()))
                name = "BatteryDefibKit";
            else continue;

            if (presetCount[name] < presetLimits[name]) {
                try {
                    // Simulăm apăsarea pe preset
                    if (name == "Paracetamol") {
                        auto expiry = chrono::floor<chrono::days>(chrono::system_clock::now()) + chrono::days(180);
                        auto newItem = std::make_unique<Medication>(name, 5.0, expiry);
                        if (newItem->priceValue() <= budget) {
                            presetCount[name]++;
                            budget -= newItem->priceValue();
                            keptItems.push_back(std::move(newItem));
                            replaced++;
                        }
                    }
                    else if (name == "Defibrillator") {
                        auto newItem = std::make_unique<MedicalEquipment>(name, 800.0, 24);
                        if (newItem->priceValue() <= budget) {
                            presetCount[name]++;
                            budget -= newItem->priceValue();
                            keptItems.push_back(std::move(newItem));
                            replaced++;
                        }
                    }
                    else if (name == "BatteryDefibKit") {
                        auto expiry = chrono::floor<chrono::days>(chrono::system_clock::now()) + chrono::days(365);
                        auto newItem = std::make_unique<ExpirableEquipment>(name, 300.0, expiry, 12);
                        if (newItem->priceValue() <= budget) {
                            presetCount[name]++;
                            budget -= newItem->priceValue();
                            keptItems.push_back(std::move(newItem));
                            replaced++;
                        }
                    }
                } catch (...) {
                    // Ignorăm fallback
                }
            }
        } else {
            keptItems.push_back(std::move(item));
        }
    }

    items = std::move(keptItems);
    cout << "Auto-manage done: sold = " << sold << ", replaced = " << replaced << ", budget = $" << budget << "\n";
}


void InventoryManager::showMenu() {
    string input;
    while (true) {
        cout << "\n--- INVENTORY MENU ---\n"
             << "1. List all\n"
             << "2. List expiring soon\n"
             << "3. Sort by rentability\n"
             << "4. Add item\n"
             << "5. Auto-manage (sell expired, refill)\n"
             << "6. Save & Exit\n"
             << "Choice: ";
        getline(cin, input);
        if (input == "1") listAll();
        else if (input == "2") listExpiringSoon();
        else if (input == "3") listSortedByRentability();
        else if (input == "4") {
            try {
                addItemFromPreset();
            } catch (const std::exception& e) {
                cout << "Error: " << e.what() << "\n";
            }
        }
        else if (input == "5") {
            autoManage();
        }
        else if (input == "6") break;
        else cout << "Invalid.\n";
    }
}
