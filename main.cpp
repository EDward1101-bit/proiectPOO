#include "includes/hospital.h"
#include "includes/doctor.h"
#include "includes/patient.h"
#include "includes/appointment.h"
#include "includes/menu.h"
#include "includes/inventory_manager.h"
#include "includes/spital_exception.h"
#include "includes/data_manager.h"

#include <map>
#include <iostream>
#include <vector>
#include <memory>

int main() {
    Hospital hospital("Spitalul Municipal");
    InventoryManager& inv = InventoryManager::getInstance();
    DataManager& data = DataManager::getInstance();

    std::vector<std::unique_ptr<Patient>> patients;
    data.loadInventory("data/inventory.csv", "data/admin.csv");
    data.loadHospital(hospital, patients, "data/doctors.csv", "data/patients.csv", "data/appointments.csv");

    auto diseaseToSpecialty = data.loadDiseaseSpecialty("data/disease_specialty.csv");
    data.assignPatients(hospital, patients, diseaseToSpecialty);

    Menu& menu = Menu::getInstance(hospital, patients, diseaseToSpecialty);

    std::string choice;
    while (true) {
        std::cout << "\n=== MAIN MENU ===\n"
                  << "1. Spital\n"
                  << "2. Inventar Medical\n"
                  << "0. Exit\n"
                  << "Choice: ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            try {
                menu.showMainMenu();
            } catch (const SpitalException& e) {
                std::cerr << "Eroare: " << e.what() << "\n";
            }
            data.saveHospital(hospital, patients, "data/appointments.csv", "data/patients.csv");
        } else if (choice == "2") {
            inv.showMenu();
            data.saveInventory("data/inventory.csv", "data/admin.csv");
        } else if (choice == "0") {
            break;
        } else {
            std::cout << "Invalid.\n";
        }
    }

    return 0;
}
