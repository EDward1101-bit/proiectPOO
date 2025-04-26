#include "../includes/menu.h"
#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/patient.h"
#include "../includes/appointment.h"

#include <iostream>
#include <limits>

Menu::Menu(Hospital& hospital, std::vector<std::unique_ptr<Patient>>& patients)
    : hospital(hospital), patients(patients) {}

void Menu::showMainMenu() {
    int choice;
    do {
        std::cout << "\n--- Main Menu ---\n";
        std::cout << "1. Doctors Menu\n";
        std::cout << "2. Patients Menu\n";
        std::cout << "3. Appointments Menu\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: doctorsMenu(); break;
            case 2: patientsMenu(); break;
            case 3: appointmentsMenu(); break;
            case 0: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid choice. Try again.\n";
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
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                hospital.listAllDoctors();
                break;
            case 2: {
                std::string doctorName;
                std::cout << "Enter doctor's name: ";
                std::getline(std::cin, doctorName);
                const Doctor* doctor = hospital.findDoctorByName(doctorName);
                if (doctor) {
                    std::cout << *doctor << "\n";
                    std::cout << "Specialty: " << doctor->getSpecialty() << "\n";
                    for (const auto& p : doctor->getPatients()) {
                        std::cout << "- " << p->getName() << "\n";
                    }
                } else {
                    std::cout << "Doctor not found.\n";
                }
                break;
            }
            case 3: {
                std::string doctorName, patientName;
                std::cout << "Enter doctor's name: ";
                std::getline(std::cin, doctorName);
                std::cout << "Enter patient's name: ";
                std::getline(std::cin, patientName);

                Doctor* doctor = hospital.findDoctorByName(doctorName);
                Patient* patient = nullptr;
                for (const auto& p : patients) {
                    if (p->getName() == patientName) {
                        patient = p.get();
                        break;
                    }
                }

                if (doctor && patient) {
                    doctor->assignPatient(patient);
                    std::cout << "Patient assigned successfully.\n";
                } else {
                    std::cout << "Doctor or patient not found.\n";
                }
                break;
            }
            case 4: {
                std::string doctorName, patientName;
                std::cout << "Enter doctor's name: ";
                std::getline(std::cin, doctorName);
                std::cout << "Enter patient's name: ";
                std::getline(std::cin, patientName);

                Doctor* doctor = hospital.findDoctorByName(doctorName);
                if (doctor) {
                    if (doctor->hasPatient(patientName)) {
                        doctor->removePatient(nullptr); // simulate removal
                        std::cout << "Patient discharged.\n";
                    } else {
                        std::cout << "Patient not found under this doctor.\n";
                    }
                } else {
                    std::cout << "Doctor not found.\n";
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
        std::cout << "4. Show patient details\n";
        std::cout << "5. Validate a CNP\n";
        std::cout << "0. Back to main menu\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                for (const auto& p : patients) {
                    std::cout << *p << "\n";
                }
                break;
            case 2: {
                std::string patientName, disease;
                std::cout << "Enter patient's name: ";
                std::getline(std::cin, patientName);
                std::cout << "Enter disease to add: ";
                std::getline(std::cin, disease);

                for (const auto& p : patients) {
                    if (p->getName() == patientName) {
                        p->addDisease(disease);
                        break;
                    }
                }
                break;
            }
            case 3: {
                std::string patientName, disease;
                std::cout << "Enter patient's name: ";
                std::getline(std::cin, patientName);
                std::cout << "Enter disease to remove: ";
                std::getline(std::cin, disease);

                for (const auto& p : patients) {
                    if (p->getName() == patientName) {
                        p->removeDisease(disease);
                        break;
                    }
                }
                break;
            }
            case 4: {
                std::string patientName;
                std::cout << "Enter patient's name: ";
                std::getline(std::cin, patientName);

                for (const auto& p : patients) {
                    if (p->getName() == patientName) {
                        std::cout << "CNP: " << p->getCNP() << ", Age: " << p->getAge()
                                  << ", Gender: " << p->getGender() << "\n";
                        if (p->isHealthy()) {
                            std::cout << "Patient is healthy.\n";
                        } else {
                            std::cout << "Diseases: ";
                            for (const auto& d : p->getDiseases()) {
                                std::cout << d << " ";
                            }
                            std::cout << "\n";
                        }
                        break;
                    }
                }
                break;
            }
            case 5: {
                std::string cnp;
                std::cout << "Enter CNP: ";
                std::getline(std::cin, cnp);
                std::cout << (Patient::isValidCNP(cnp) ? "CNP is valid.\n" : "CNP is invalid.\n");
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
        std::cout << "1. List appointments (sorted)\n";
        std::cout << "2. Add new appointment\n";
        std::cout << "0. Back to main menu\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
                if (appointment->isValidDateTime() && appointment->isInFuture()) {
                    hospital.addAppointment(std::move(appointment));
                    std::cout << "Appointment added.\n";
                } else {
                    std::cout << "Invalid date/time.\n";
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
