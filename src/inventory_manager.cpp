#include "../includes/inventory_manager.h"
#include "../includes/medication.h"
#include "../includes/medical_equipment.h"
#include "../includes/expirable_equipment.h"
#include "../includes/spital_exception.h"
#include "../includes/reusable_equipment.h"
#include "../includes/spital_exception.h"
#include "../includes/inventory_item_template.h"
#include "../includes/utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

InventoryManager::InventoryManager()
    : budget(0.0){}

InventoryManager& InventoryManager::getInstance() {
    static InventoryManager instance;
    return instance;
}

void InventoryManager::loadFromCSV(const string& filename) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        throw FileOpenException(filename);
    }

    string line;
    while (getline(fin, line)) {
        auto item = parseCSVLine(line);
        if (item) items.push_back(std::move(item));
    }
}

void InventoryManager::saveToCSV(const string& filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw SpitalException("Nu s-a putut deschide fișierul de inventar pentru scriere.");
    }

    for (const auto& item : items) {
        item->saveToCSV(out);
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
        throw InsufficientBudgetException(item->priceValue());
    }

    budget -= item->priceValue();
    items.push_back(std::move(item));
}

void InventoryManager::addItemFromTemplate() {
    std::cout << "\nAvailable Item Templates:\n"
              << "1. Paracetamol\n"
              << "2. Defibrillator\n"
              << "3. BatteryDefibKit\n"
              << "4. ReusableScalpel\n"
              << "Choice: ";

    std::string opt;
    std::getline(std::cin, opt);

    std::unique_ptr<InventoryItem> item;

    if (opt == "1") {
        item = std::make_unique<Medication>("Paracetamol", 5.0, floor<days>(system_clock::now()) + days(180));
    } else if (opt == "2") {
        item = std::make_unique<MedicalEquipment>("Defibrillator", 800.0, 24);
    } else if (opt == "3") {
        item = std::make_unique<ExpirableEquipment>("BatteryDefibKit", 300.0, floor<days>(system_clock::now()) + days(365), 12);
    } else if (opt == "4") {
        item = std::make_unique<ReusableEquipment>("ReusableScalpel", 100.0, 12, 50, 0);
    } else {
        throw InvalidInputException("Opțiune invalidă pentru șablon de item.");
    }

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
        std::cout << "Item sold. Budget updated.\n";
    } else {
        throw EntityNotFoundException("ID item necunoscut: " + std::to_string(id));
    }

}

void InventoryManager::cloneMostRentableItem() {
    if (items.empty()) return;
    auto it = max_element(items.begin(), items.end(), [](const auto& a, const auto& b) {
        return a->getRentabilityScore() < b->getRentabilityScore();
    });
    auto cloned = (*it)->clone();
    if (cloned->priceValue() > budget) {
        throw InsufficientBudgetException(cloned->priceValue());
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
    std::vector<std::unique_ptr<InventoryItem>> kept;

    for (auto& item : items) {
        bool shouldRemove = false;

        // am preferat sa scurtez portiunea asta decat sa fac functie virtuala
        if (const auto* reusable = dynamic_cast<ReusableEquipment*>(item.get())) {
            if (reusable->getUsageLeft() <= 0) {
                std::cout << "[AUTO-MANAGE] Removed reusable tool with 0 usage left: " << reusable->getName() << "\n";
                shouldRemove = true;
            }
        } else if (const auto* exp = dynamic_cast<ExpirableEquipment*>(item.get())) {
            if (exp->isExpiringSoon()) {
                std::cout << "[AUTO-MANAGE] Removed expiring equipment: " << exp->getName() << "\n";
                shouldRemove = true;
            }
        }


        if (shouldRemove) {
            budget += item->priceValue() * 0.25;
        } else {
            kept.push_back(std::move(item));
        }
    }

    items = std::move(kept);
    std::cout << "Auto-manage complete.\n";
}


void InventoryManager::showMenu() {
    std::string input;
    while (true) {
        try {
            cout << "\n=== INVENTORY MENU ===\n"
                 << "1. List all\n2. List expiring soon\n3. Sort by rentability\n4. Add inventory item\n"
                 << "5. Auto-manage\n6. Remove item by ID\n7. Clone most rentable\n8. Save & Exit\n9. Adaugă item cu informație extinsă\n10. Afișează itemi cu rentabilitate > X\nChoice: ";
            getline(cin, input);

            if (input == "1") listAll();
            else if (input == "2") listExpiringSoon();
            else if (input == "3") listSortedByRentability();
            else if (input == "4") {
                try { addItemFromTemplate(); }
                catch (const SpitalException& e) { cerr << e.what() << "\n"; }
            }
            else if (input == "5") autoManage();
            else if (input == "6") {
                cout << "Enter ID to remove: ";
                string idStr;
                getline(cin, idStr);
                try {
                    int id = stoi(idStr);
                    removeItemById(id);
                } catch (const std::invalid_argument&) {
                    throw InvalidInputException("ID introdus invalid (nu e număr)");
                } catch (const SpitalException& e) {
                    cerr << e.what() << "\n";
                }
            }
            else if (input == "7") {
                try { cloneMostRentableItem(); }
                catch (const SpitalException& e) { cerr << e.what() << "\n"; }
            }
            else if (input == "8") break;
            else if (input == "9") {
                std::string name, type, priceStr;

                std::cout << "Nume item: ";
                std::getline(std::cin, name);

                std::cout << "Preț: ";
                std::getline(std::cin, priceStr);

                if (priceStr.empty() || !std::all_of(priceStr.begin(), priceStr.end(), [](char c) {
                        return std::isdigit(c) || c == '.' || c == ',';
                    })) {
                    throw InvalidInputException("Preț invalid: trebuie să fie un număr pozitiv");
                    }

                double price = 0.0;
                try {
                    price = std::stod(priceStr);
                } catch (const std::exception& e) {
                    throw InvalidInputException("Conversie eșuată a prețului: " + std::string(e.what()));
                }

                std::cout << "Tip info extra (int/string): ";
                std::getline(std::cin, type);

                if (type == "int") {
                    std::string valStr;
                    std::cout << "Cod numeric suplimentar (ex: cod lot): ";
                    std::getline(std::cin, valStr);

                    if (valStr.empty() || !std::all_of(valStr.begin(), valStr.end(), ::isdigit)) {
                        throw InvalidInputException("Cod numeric invalid");
                    }

                    int val = std::stoi(valStr);
                    auto item = std::make_unique<InventoryItemTemplate<int>>(name, price, val);
                    addItem(std::move(item));

                } else if (type == "string") {
                    std::string val;
                    std::cout << "Etichetă suplimentară (ex: Secție): ";
                    std::getline(std::cin, val);

                    if (val.empty()) {
                        throw InvalidInputException("Eticheta nu poate fi goală");
                    }

                    auto item = std::make_unique<InventoryItemTemplate<std::string>>(name, price, val);
                    addItem(std::move(item));

                } else {
                    throw InvalidInputException("Tip necunoscut: trebuie 'int' sau 'string'");
                }
            }
            else if (input == "10") {
                std::string xStr;
                std::cout << "Rentabilitate minimă: ";
                std::getline(std::cin, xStr);

                double x = 0;
                try {
                    x = std::stod(xStr);
                } catch (...) {
                    throw InvalidInputException("Valoare rentabilitate invalidă");
                }

                std::cout << "Itemi cu rentabilitate > " << x << ":\n";
                afiseazaDaca(items, [x](const InventoryItem* item) {
                    return item->getRentabilityScore() > x;
                });
            }else throw InvalidInputException("Opțiune invalidă selectată: " + input);


        } catch (const SpitalException& e) {
            cerr << "[Eroare] " << e.what() << "\n";
        }
    }
}


std::unique_ptr<InventoryItem> InventoryManager::parseCSVLine(const std::string& line) const {
    std::istringstream iss(line);
    std::string type, name, priceStr;

    if (!getline(iss, type, ',') ||
        !getline(iss, name, ',') ||
        !getline(iss, priceStr, ',')) {
        return nullptr;
        }

    double price = std::stod(priceStr);

    if (type == "Medication") {
        std::string expiryStr;
        if (!getline(iss, expiryStr)) return nullptr;
        auto expiry = Medication::parseDate(expiryStr);
        return std::make_unique<Medication>(name, price, expiry);
    }

    if (type == "Equipment") {
        std::string warrantyStr;
        if (!getline(iss, warrantyStr)) return nullptr;
        int warranty = std::stoi(warrantyStr);
        return std::make_unique<MedicalEquipment>(name, price, warranty);
    }

    if (type == "ExpirableEquipment") {
        std::string expiryStr, warrantyStr;
        if (!getline(iss, expiryStr, ',') || !getline(iss, warrantyStr)) return nullptr;
        auto expiry = Medication::parseDate(expiryStr);
        int warranty = std::stoi(warrantyStr);
        return std::make_unique<ExpirableEquipment>(name, price, expiry, warranty);
    }

    if (type == "ReusableEquipment") {
        std::string warrantyStr, usageLimitStr, currentUsageStr;
        if (!getline(iss, warrantyStr, ',') ||
            !getline(iss, usageLimitStr, ',') ||
            !getline(iss, currentUsageStr)) return nullptr;

        int warranty = std::stoi(warrantyStr);
        int usageLimit = std::stoi(usageLimitStr);
        int currentUsage = std::stoi(currentUsageStr);

        return std::make_unique<ReusableEquipment>(name, price, warranty, usageLimit, currentUsage);
    }


    return nullptr;
}


