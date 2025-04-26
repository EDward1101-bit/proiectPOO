#include "../includes/menu.h"
#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/patient.h"
#include "../includes/appointment.h"

#include <iostream>


Menu::Menu(Hospital& hospital, std::vector<std::unique_ptr<Patient>>& patients)
    : hospital(hospital), patients(patients) {}


void Menu::showMainMenu() {
    int choice;
    do {
        std::cout << "\n=== Hospital Management Menu ===\n";
        std::cout << "1. Doctors Menu\n";
        std::cout << "2. Patients Menu\n";
        std::cout << "3. Appointments Menu\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                doctorsMenu();
                break;
            case 2:
                patientsMenu();
                break;
            case 3:
                appointmentsMenu();
                break;
            case 0:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 0);
}


void Menu::doctorsMenu() {
    int choice;
    do {
        std::cout << "\n--- Doctors Menu ---\n";
        std::cout << "1. List all doctors\n";
        std::cout << "2. Find doctor by name\n";
        std::cout << "0. Back to main menu\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                hospital.listAllDoctors();
                break;
            case 2: {
                std::string name;
                std::cout << "Enter doctor's name: ";
                std::getline(std::cin, name);
                Doctor* doctor = hospital.findDoctorByName(name);
                if (doctor) {
                    std::cout << *doctor << "\n";
                } else {
                    std::cout << "Doctor not found.\n";
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 0);
}


void Menu::patientsMenu() {
    int choice;
    do {
        std::cout << "\n--- Patients Menu ---\n";
        std::cout << "1. List all patients\n";
        std::cout << "0. Back to main menu\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                if (patients.empty()) {
                    std::cout << "No patients available.\n";
                } else {
                    for (const auto& p : patients) {
                        std::cout << *p << "\n";
                    }
                }
                break;
            case 0:
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 0);
}


void Menu::appointmentsMenu() {
    int choice;
    do {
        std::cout << "\n--- Appointments Menu ---\n";
        std::cout << "1. List all appointments (sorted)\n";
        std::cout << "0. Back to main menu\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                hospital.listAllAppointments();
                break;
            case 0:
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 0);
}
