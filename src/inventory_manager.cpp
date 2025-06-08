#include "../includes/inventory_manager.h"
#include "../includes/medication.h"
#include "../includes/medical_equipment.h"
#include "../includes/expirable_equipment.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

InventoryManager::InventoryManager()
    : budget(0.0),
      presetLimits{
              {"Paracetamol", 3},
              {"Defibrillator", 3},
              {"BatteryDefibKit", 3}
      },
      presetCount{
              {"Paracetamol", 0},
              {"Defibrillator", 0},
              {"BatteryDefibKit", 0}
      }
{}


void InventoryManager::loadFromCSV(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Error opening inventory file.\n";
        return;
    }
    string line;
    while (getline(fin, line)) {
        auto item = parseCSVLine(line);
        if (item) items.push_back(std::move(item));
    }
}

void InventoryManager::saveToCSV(const string& filename) const {
    ofstream fout(filename);
    for (const auto& item : items) {
        if (dynamic_cast<const ExpirableEquipment*>(item.get()))
            fout << "ExpirableEquipment,";
        else if (dynamic_cast<const Medication*>(item.get()))
            fout << "Medication,";
        else if (dynamic_cast<const MedicalEquipment*>(item.get()))
            fout << "Equipment,";
        fout << item->getName() << "," << item->priceValue() << "\n";
    }
}

void InventoryManager::loadBudget(const string& filename) {
    ifstream fin(filename);
    fin >> budget;
}

void InventoryManager::saveBudget(const string& filename) const {
    ofstream fout(filename);
    fout << budget;
}

void InventoryManager::addItem(unique_ptr<InventoryItem> item) {
    if (item->priceValue() > budget) {
        cerr << "Insufficient budget for: " << item->getName() << "\n";
        return;
    }
    budget -= item->priceValue();
    items.push_back(std::move(item));
}

void InventoryManager::addItemFromPreset() {
    cout << "\nAvailable Presets:\n1. Paracetamol\n2. Defibrillator\n3. BatteryDefibKit\nChoice: ";
    string opt;
    getline(cin, opt);
    string name;
    unique_ptr<InventoryItem> item;
    if (opt == "1") {
        name = "Paracetamol";
        if (presetCount[name] >= presetLimits[name]) throw runtime_error("Limit reached");
        item = make_unique<Medication>(name, 5.0, floor<days>(system_clock::now()) + days(180));
    } else if (opt == "2") {
        name = "Defibrillator";
        if (presetCount[name] >= presetLimits[name]) throw runtime_error("Limit reached");
        item = make_unique<MedicalEquipment>(name, 800.0, 24);
    } else if (opt == "3") {
        name = "BatteryDefibKit";
        if (presetCount[name] >= presetLimits[name]) throw runtime_error("Limit reached");
        item = make_unique<ExpirableEquipment>(name, 300.0, floor<days>(system_clock::now()) + days(365), 12);
    } else {
        throw runtime_error("Invalid preset");
    }
    presetCount[name]++;
    addItem(std::move(item));
}

void InventoryManager::removeItemById(int id) {
    auto it = remove_if(items.begin(), items.end(), [&](const unique_ptr<InventoryItem>& item) {
        if (item->getId() == id) {
            budget += item->priceValue() * 0.25;
            return true;
        }
        return false;
    });
    if (it != items.end()) {
        items.erase(it, items.end());
        cout << "Item sold. Budget updated.\n";
    } else {
        cout << "Item ID not found.\n";
    }
}

void InventoryManager::cloneMostRentableItem() {
    if (items.empty()) return;
    auto it = max_element(items.begin(), items.end(), [](const auto& a, const auto& b) {
        return a->getRentabilityScore() < b->getRentabilityScore();
    });
    auto cloned = (*it)->clone();
    if (cloned->priceValue() > budget) {
        cout << "Not enough budget to clone.\n";
        return;
    }
    budget -= cloned->priceValue();
    items.push_back(std::move(cloned));
    cout << "Item cloned and added.\n";
}

void InventoryManager::listAll() const {
    for (const auto& item : items) cout << *item << "\n";
}

void InventoryManager::listSortedByRentability() const {
    vector<const InventoryItem*> sorted;
    for (const auto& item : items) sorted.push_back(item.get());
    sort(sorted.begin(), sorted.end(), [](auto a, auto b) {
        return a->getRentabilityScore() > b->getRentabilityScore();
    });
    for (const auto& item : sorted) cout << *item << " | Score: " << item->getRentabilityScore() << "\n";
}

void InventoryManager::listExpiringSoon() const {
    for (const auto& item : items) {
        if (item->isExpiringSoon()) cout << *item << "\n";
    }
}

void InventoryManager::autoManage() {
    vector<unique_ptr<InventoryItem>> kept;
    for (auto& item : items) {
        if (item->isExpiringSoon()) {
            budget += item->priceValue() * 0.25;
            continue;
        }
        kept.push_back(std::move(item));
    }
    items = std::move(kept);
    cout << "Auto-manage complete.\n";
}

void InventoryManager::showMenu() {
    string input;
    while (true) {
        cout << "\n=== INVENTORY MENU ===\n"
             << "1. List all\n2. List expiring soon\n3. Sort by rentability\n4. Add from preset\n"
             << "5. Auto-manage\n6. Remove item by ID\n7. Clone most rentable\n8. Save & Exit\nChoice: ";
        getline(cin, input);
        if (input == "1") listAll();
        else if (input == "2") listExpiringSoon();
        else if (input == "3") listSortedByRentability();
        else if (input == "4") try { addItemFromPreset(); } catch (exception& e) { cout << e.what() << "\n"; }
        else if (input == "5") autoManage();
        else if (input == "6") {
            cout << "Enter ID to remove: ";
            string idStr;
            getline(cin, idStr);
            try { removeItemById(stoi(idStr)); } catch (...) { cout << "Invalid ID.\n"; }
        }
        else if (input == "7") cloneMostRentableItem();
        else if (input == "8") break;
        else cout << "Invalid choice.\n";
    }
}

std::unique_ptr<InventoryItem> InventoryManager::parseCSVLine(const std::string& line) const {
    std::istringstream iss(line);
    std::string type, name, priceStr, d1;
    if (!getline(iss, type, ',') ||
        !getline(iss, name, ',') ||
        !getline(iss, priceStr, ',')) {
        return nullptr;
        }

    double price = std::stod(priceStr);

    if (type == "Medication") {
        if (!getline(iss, d1)) return nullptr;
        auto expiry = Medication::parseDate(d1);
        return std::make_unique<Medication>(name, price, expiry);
    }

    if (type == "Equipment") {
        if (!getline(iss, d1)) return nullptr;
        int warranty = std::stoi(d1);
        return std::make_unique<MedicalEquipment>(name, price, warranty);
    }

    if (type == "ExpirableEquipment") {
        std::string d2;
        if (!getline(iss, d1, ',') || !getline(iss, d2)) return nullptr;
        auto expiry = Medication::parseDate(d1);
        int warranty = std::stoi(d2);
        return std::make_unique<ExpirableEquipment>(name, price, expiry, warranty);
    }

    return nullptr;
}

