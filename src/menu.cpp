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
        std::cin.ignore();

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
        }
    } while (choice != 0);
}


void Menu::doctorsMenu() {
    int choice;
    do {
        std::cout << "\n--- Doctors Menu ---\n";
        std::cout << "1. List all doctors\n";
        std::cout << "2. Find doctor by name\n";
        std::cout << "3. Assign patient to doctor\n";
        std::cout << "4. Discharge patient from doctor\n";
        std::cout << "0. Back to main menu\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                hospital.listAllDoctors();
                break;
            case 2: {
                std::string doctorName;
                std::cout << "Enter doctor's name: ";
                std::getline(std::cin, doctorName);
                Doctor* doctor = hospital.findDoctorByName(doctorName);
                if (doctor) {
                    std::cout << *doctor << "\n";
                } else {
                    std::cout << "Doctor not found.\n";
                }
                break;
            }
            case 3: {
                std::string doctorName, patientName;
                std::cout << "Enter doctor's name: ";
                std::getline(std::cin, doctorName);
                Doctor* doctor = hospital.findDoctorByName(doctorName);
                if (!doctor) {
                    std::cout << "Doctor not found.\n";
                    break;
                }
                std::cout << "Enter patient's name to assign: ";
                std::getline(std::cin, patientName);
                Patient* foundPatient = nullptr;
                for (const auto& p : patients) {
                    if (p->getName() == patientName) {
                        foundPatient = p.get();
                        break;
                    }
                }
                if (foundPatient) {
                    doctor->assignPatient(foundPatient);
                    std::cout << "Patient assigned successfully.\n";
                } else {
                    std::cout << "Patient not found.\n";
                }
                break;
            }
            case 4: {
                std::string doctorName, patientName;
                std::cout << "Enter doctor's name: ";
                std::getline(std::cin, doctorName);
                Doctor* doctor = hospital.findDoctorByName(doctorName);
                if (!doctor) {
                    std::cout << "Doctor not found.\n";
                    break;
                }
                std::cout << "Enter patient's name to discharge: ";
                std::getline(std::cin, patientName);
                if (doctor->dischargePatient(patientName)) {
                    std::cout << "Patient discharged successfully.\n";
                } else {
                    std::cout << "Patient not found under this doctor.\n";
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}


void Menu::patientsMenu() {
    int choice;
    do {
        std::cout << "\n--- Patients Menu ---\n";
        std::cout << "1. List all patients\n";
        std::cout << "2. Add disease to patient\n";
        std::cout << "3. Remove disease from patient\n";
        std::cout << "4. Check if patient is healthy\n";
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
            case 2: {
                std::string patientName, disease;
                std::cout << "Enter patient's name: ";
                std::getline(std::cin, patientName);
                Patient* patient = nullptr;
                for (const auto& p : patients) {
                    if (p->getName() == patientName) {
                        patient = p.get();
                        break;
                    }
                }
                if (patient) {
                    std::cout << "Enter disease to add: ";
                    std::getline(std::cin, disease);
                    patient->addDisease(disease);
                    std::cout << "Disease added.\n";
                } else {
                    std::cout << "Patient not found.\n";
                }
                break;
            }
            case 3: {
                std::string patientName, disease;
                std::cout << "Enter patient's name: ";
                std::getline(std::cin, patientName);
                Patient* patient = nullptr;
                for (const auto& p : patients) {
                    if (p->getName() == patientName) {
                        patient = p.get();
                        break;
                    }
                }
                if (patient) {
                    std::cout << "Enter disease to remove: ";
                    std::getline(std::cin, disease);
                    patient->removeDisease(disease);
                    std::cout << "Disease removed.\n";
                } else {
                    std::cout << "Patient not found.\n";
                }
                break;
            }
            case 4: {
                std::string patientName;
                std::cout << "Enter patient's name: ";
                std::getline(std::cin, patientName);
                Patient* patient = nullptr;
                for (const auto& p : patients) {
                    if (p->getName() == patientName) {
                        patient = p.get();
                        break;
                    }
                }
                if (patient) {
                    if (patient->isHealthy()) {
                        std::cout << "Patient is healthy.\n";
                    } else {
                        std::cout << "Patient has diseases.\n";
                    }
                } else {
                    std::cout << "Patient not found.\n";
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}

void Menu::appointmentsMenu() {
    int choice;
    do {
        std::cout << "\n--- Appointments Menu ---\n";
        std::cout << "1. List all appointments\n";
        std::cout << "2. Add a new appointment\n";
        std::cout << "0. Back to main menu\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                hospital.listAllAppointments();
            break;
            case 2: {
                std::string doctorName, patientName, date, time;
                std::cout << "Enter doctor's name: ";
                std::getline(std::cin, doctorName);
                Doctor* doctor = hospital.findDoctorByName(doctorName);
                if (!doctor) {
                    std::cout << "Doctor not found.\n";
                    break;
                }

                std::cout << "Enter patient's name: ";
                std::getline(std::cin, patientName);
                Patient* patient = nullptr;
                for (const auto& p : patients) {
                    if (p->getName() == patientName) {
                        patient = p.get();
                        break;
                    }
                }

                if (!patient) {
                    std::cout << "Patient not found.\n";
                    break;
                }

                std::cout << "Enter date (YYYY-MM-DD): ";
                std::getline(std::cin, date);
                std::cout << "Enter time (HH:MM): ";
                std::getline(std::cin, time);

                auto appointment = std::make_unique<Appointment>(date, time, doctor, patient);
                if (appointment->isValidDateTime()) {
                    hospital.addAppointment(std::move(appointment));
                    std::cout << "Appointment added successfully.\n";
                } else {
                    std::cout << "Invalid appointment date/time. Must be in the future and correct format.\n";
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}

