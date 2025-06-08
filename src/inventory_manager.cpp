#include "../includes/inventory_manager.h"
#include "../includes/medication.h"
#include "../includes/medical_equipment.h"
#include "../includes/expirable_equipment.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

InventoryManager::InventoryManager() : budget(0.0) {}

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

void InventoryManager::showMenu() {
    string input;
    while (true) {
        cout << "\n--- INVENTORY MENU ---\n"
             << "1. List all\n"
             << "2. List expiring soon\n"
             << "3. Sort by rentability\n"
             << "4. Save & Exit\n"
             << "Choice: ";
        getline(cin, input);
        if (input == "1") listAll();
        else if (input == "2") listExpiringSoon();
        else if (input == "3") listSortedByRentability();
        else if (input == "4") break;
        else cout << "Invalid.\n";
    }
}
