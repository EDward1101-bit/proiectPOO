#include <iostream>
#include <string>
#include <limits>
#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/nurse.h"
#include "../includes/patient.h"

int main() {
    Spital hospital("General Hospital");

    while (true) {
        std::cout << "Welcome to the Hospital Management System!\n";
        std::cout << "1. Add Doctor\n";
        std::cout << "2. Add Nurse\n";
        std::cout << "3. Print Doctors\n";
        std::cout << "4. Print Nurses\n";
        std::cout << "5. Assign Patient to Doctor\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore last input
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                std::string name, specialty;
                unsigned int tarif;
                std::cout << "Enter Doctor's Name: ";
                std::cin >> name;
                std::cout << "Enter Doctor's Specialty: ";
                std::cin >> specialty;
                std::cout << "Enter Doctor's Tarif: ";
                std::cin >> tarif;

                Doctor* newDoctor = new Doctor(name, specialty, tarif);
                hospital.assignDoctor(newDoctor);
                std::cout << "Doctor added successfully!\n";
                break;
            }

            case 2: {
                std::string name, specialty;
                int age, yearsWorked;
                std::cout << "Enter Nurse's Name: ";
                std::cin >> name;
                std::cout << "Enter Nurse's Specialty: ";
                std::cin >> specialty;
                std::cout << "Enter Nurse's Age: ";
                std::cin >> age;
                std::cout << "Enter Nurse's Years Worked: ";
                std::cin >> yearsWorked;

                Nurse* newNurse = new Nurse(name, specialty, age, yearsWorked);
                hospital.assignNurse(newNurse);
                std::cout << "Nurse added successfully!\n";
                break;
            }

            case 3: {
                hospital.printDoctors();
                break;
            }

            case 4: {
                hospital.printNurses();
                break;
            }

            case 5: {
                // add code to assign a patient to a doctor.
                break;
            }

            case 6:
                std::cout << "Exiting program...\n";
                return 0;

            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
