#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <cstdlib>
#include <thread>
#include <chrono>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "../includes/hospital.h"
#include "../includes/location.h"
#include "../includes/doctor.h"
#include "../includes/patient.h"
#include "../includes/medical_data.h"
#include "../includes/termcolor.hpp"

using namespace termcolor;

void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseAndClear() {
    std::cout << yellow << "\nPress Enter to continue..." << reset;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    clearConsole();
}

std::vector<std::unique_ptr<Hospital>> initializeHospitals() {
    std::vector<std::unique_ptr<Hospital>> hospitals;

    Location roLoc("Romania", +2);
    Location ukLoc("UK", 0);
    Location usLoc("USA", -5);

    auto h1 = std::make_unique<Hospital>("Bucharest Medical Center", roLoc);
    auto h2 = std::make_unique<Hospital>("London Central Hospital", ukLoc);
    auto h3 = std::make_unique<Hospital>("New York Health Institute", usLoc);

    h1->addDoctor(std::make_unique<Doctor>("Andrei Ionescu", "Cardiologist"));
    h1->addDoctor(std::make_unique<Doctor>("Ana Georgescu", "Neurologist"));
    h1->addDoctor(std::make_unique<Doctor>("Mihai Toma", "Orthopedic Surgeon"));

    h2->addDoctor(std::make_unique<Doctor>("Emily Clarke", "Dermatologist"));
    h2->addDoctor(std::make_unique<Doctor>("James Brown", "Oncologist"));
    h2->addDoctor(std::make_unique<Doctor>("Chloe Wright", "Gastroenterologist"));

    h3->addDoctor(std::make_unique<Doctor>("John Smith", "Endocrinologist"));
    h3->addDoctor(std::make_unique<Doctor>("Laura Johnson", "Psychiatrist"));
    h3->addDoctor(std::make_unique<Doctor>("Michael Green", "Cardiologist"));

    auto* p1 = new Patient("Alex Luca", 30, 'M', "1234567890123", 1200);
    p1->addDisease("Heart Disease", 300);
    h1->addPatientToDoctor("Andrei Ionescu", p1);

    auto* p2 = new Patient("George Vasilescu", 40, 'M', "2234567890123", 800);
    p2->addDisease("Epilepsy", 400);
    h1->addPatientToDoctor("Ana Georgescu", p2);

    auto* p3 = new Patient("Elena Bratu", 33, 'F', "3234567890123", 900);
    p3->addDisease("Arthritis", 350);
    h1->addPatientToDoctor("Mihai Toma", p3);

    auto* p4 = new Patient("Emma White", 25, 'F', "4234567890123", 1500);
    p4->addDisease("Eczema", 250);
    h2->addPatientToDoctor("Emily Clarke", p4);

    auto* p5 = new Patient("Daniel Lee", 45, 'M', "5234567890123", 1800);
    p5->addDisease("Leukemia", 900);
    h2->addPatientToDoctor("James Brown", p5);

    auto* p6 = new Patient("Sophie Moore", 29, 'F', "6234567890123", 1100);
    p6->addDisease("IBS", 400);
    h2->addPatientToDoctor("Chloe Wright", p6);

    auto* p7 = new Patient("Kevin Brooks", 50, 'M', "7234567890123", 950);
    p7->addDisease("Diabetes", 450);
    h3->addPatientToDoctor("John Smith", p7);

    auto* p8 = new Patient("Sarah Black", 34, 'F', "8234567890123", 1300);
    p8->addDisease("Anxiety", 320);
    h3->addPatientToDoctor("Laura Johnson", p8);

    auto* p9 = new Patient("Tom Wilson", 38, 'M', "9234567890123", 1400);
    p9->addDisease("Heart Disease", 500);
    h3->addPatientToDoctor("Michael Green", p9);

    h1->scheduleAppointment("Andrei Ionescu", p1, "2025-05-01", "10:00");
    h1->scheduleAppointment("Ana Georgescu", p2, "2025-05-02", "11:00");
    h2->scheduleAppointment("Emily Clarke", p4, "2025-05-03", "12:00");
    h3->scheduleAppointment("John Smith", p7, "2025-05-04", "09:30");

    hospitals.push_back(std::move(h1));
    hospitals.push_back(std::move(h2));
    hospitals.push_back(std::move(h3));

    return hospitals;
}
Hospital* selectHospital(const std::vector<std::unique_ptr<Hospital>>& hospitals) {
    std::cout << bold << cyan << "Select a hospital:" << reset << "\n";
    for (size_t i = 0; i < hospitals.size(); ++i) {
        std::cout << yellow << i + 1 << ". " << reset << *hospitals[i] << "\n";
    }
    std::cout << yellow << "Choice: " << reset;
    int index;
    std::cin >> index;
    std::cin.ignore();

    if (index >= 1 && static_cast<size_t>(index) <= hospitals.size()) {
        return hospitals[index - 1].get();
    } else {
        std::cout << red << "Invalid selection. Returning to main menu.\n" << reset;
        pauseAndClear();
        return nullptr;
    }
}

void displayMainMenu();
void runAdminMenu(const std::vector<std::unique_ptr<Hospital>>& hospitals);
void runDoctorMenu(const std::vector<std::unique_ptr<Hospital>>& hospitals);
void runPatientMenu(std::vector<std::unique_ptr<Hospital>>& hospitals);

int main() {
    auto hospitals = initializeHospitals();
    int choice = -1;

    while (choice != 0) {
        clearConsole();
        displayMainMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                runAdminMenu(hospitals);
                break;
            case 2:
                runDoctorMenu(hospitals);
                break;
            case 3:
                runPatientMenu(hospitals);
                break;
            case 0:
                std::cout << red << "Exiting...\n" << reset;
                break;
            default:
                std::cout << red << "Invalid choice!" << reset;
                pauseAndClear();
        }
    }
    return 0;
}
void displayMainMenu() {
    std::cout << termcolor::cyan << "==== HOSPITAL MANAGEMENT SYSTEM ====" << termcolor::reset << std::endl;
    std::cout << "1. " << termcolor::green << "Admin Menu" << termcolor::reset << "\n"
              << "2. " << termcolor::green << "Doctor Menu" << termcolor::reset << "\n"
              << "3. " << termcolor::green << "Patient Menu" << termcolor::reset << "\n"
              << "0. " << termcolor::red << "Exit" << termcolor::reset << std::endl;
    std::cout << termcolor::yellow << "Choose your role: " << termcolor::reset;
}

void runAdminMenu(const std::vector<std::unique_ptr<Hospital>>& hospitals) {
    int option = -1;
    while (option != 0) {
        clearConsole();
        std::cout << bold << cyan << "==== ADMIN MENU ====" << reset << std::endl;
        std::cout << green << "1. View all hospitals\n"
                  << "2. View doctors per hospital\n"
                  << "3. View total profit per hospital\n"
                  << "4. View most common diseases\n"
                  << red   << "0. Back to Main Menu" << reset << std::endl;
        std::cout << yellow << "Choose an option: " << reset;
        std::cin >> option;
        std::cin.ignore();

        switch (option) {
            case 1:
                for (const auto& h : hospitals) h->printInfo();
                pauseAndClear();
                break;
            case 2:
                for (const auto& h : hospitals) {
                    h->printInfo();
                    h->printDoctors();
                }
                pauseAndClear();
                break;
            case 3:
                for (const auto& h : hospitals) {
                    std::cout << yellow << "Profit: " << reset << green << h->getProfit() << reset << " at " << *h << std::endl;
                }
                pauseAndClear();
                break;
            case 4:
                for (const auto& h : hospitals) {
                    std::cout << bold << "\nTop Diseases in: " << *h << reset;
                    for (const auto& [name, count] : h->getMostCommonDiseases()) {
                        std::cout << cyan << name << reset << " (" << count << ")\n";
                    }
                }
                pauseAndClear();
                break;
            case 0:
                break;
            default:
                std::cout << red << "Invalid choice!" << reset;
                pauseAndClear();
                break;
        }
    }
}

// === DOCTOR MENU ===
void runDoctorMenu(const std::vector<std::unique_ptr<Hospital>>& hospitals) {
    std::string doctorName;
    std::cout << yellow << "Enter your full name: " << reset;
    std::getline(std::cin, doctorName);

    for (const auto& hospital : hospitals) {
        for (const auto& doctor : hospital->getDoctors()) {
            if (doctor->getName() == doctorName) {
                int option = -1;
                while (option != 0) {
                    clearConsole();
                    std::cout << bold << cyan << "\n==== DOCTOR MENU for " << doctor->getName() << " ====" << reset << std::endl;
                    std::cout << green << "1. View assigned patients\n2. View scheduled appointments\n3. Discharge a patient\n"
                              << red << "0. Back to Main Menu" << reset << std::endl;
                    std::cout << yellow << "Choose an option: " << reset;
                    std::cin >> option;
                    std::cin.ignore();

                    switch (option) {
                        case 1:
                            doctor->printPatients();
                            pauseAndClear();
                            break;
                        case 2:
                            for (const auto& appt : doctor->getAppointments()) {
                                std::cout << *appt << "\n";
                            }
                            pauseAndClear();
                            break;
                        case 3: {
                            std::string cnp;
                            std::cout << yellow << "Enter the CNP of the patient to discharge: " << reset;
                            std::getline(std::cin, cnp);
                            for (const auto& p : doctor->getPatientList()) {
                                if (p->getCNP() == cnp) {
                                    hospital->dischargePatient(p, doctor.get());
                                    break;
                                }
                            }
                            pauseAndClear();
                            break;
                        }
                        case 0:
                            break;
                        default:
                            std::cout << red << "Invalid option!\n" << reset;
                            pauseAndClear();
                            break;
                    }
                }
                return;
            }
        }
    }
    std::cout << red << "Doctor not found." << reset << std::endl;
    pauseAndClear();
}

// === PATIENT MENU ===
void runPatientMenu(std::vector<std::unique_ptr<Hospital>>& hospitals) {
    std::string cnp;
    std::cout << yellow << "Enter your CNP: " << reset;
    std::getline(std::cin, cnp);

    for (auto& hospital : hospitals) {
        for (const auto& doctor : hospital->getDoctors()) {
            for (const auto& patient : doctor->getPatientList()) {
                if (patient->getCNP() == cnp) {
                    clearConsole();
                    std::cout << green << "Welcome, " << patient->getName() << "!" << reset << "\n";
                    std::cout << *patient;
                    pauseAndClear();
                    return;
                }
            }
        }
    }

    std::cout << red << "Patient not found." << reset << std::endl;
    pauseAndClear();
}