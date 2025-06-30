#include "../includes/menu.h"
#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/patient.h"
#include "../includes/appointment.h"
#include "../includes/spital_exception.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <algorithm>

Menu::Menu(Hospital& hospital, std::vector<std::unique_ptr<Patient>>& patients,
           const std::map<std::string, std::string>& diseaseToSpecialty)
    : hospital(hospital), patients(patients), diseaseToSpecialty(diseaseToSpecialty) {}

Menu& Menu::getInstance(Hospital& h, std::vector<std::unique_ptr<Patient>>& p, const std::map<std::string, std::string>& d)
 {
    static Menu instance(h, p, d);
    return instance;
}

std::string readValidName(const std::string& prompt) {
    std::string name;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, name);

        if (!name.empty() && name.find_first_not_of(' ') != std::string::npos) {
            break;
        }
        std::cout << "Invalid input. Please enter a non-empty string.\n";
    }
    return name;
}

void Menu::showMainMenu() {
    int choice = -1;
    do {
        std::cout << "\n--- Main Menu ---\n"
                  << "1. Doctors Menu\n"
                  << "2. Patients Menu\n"
                  << "3. Appointments Menu\n"
                  << "0. Exit\n"
                  << "Choice: ";

        std::string input;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        iss >> choice;

        try {
            switch (choice) {
                case 1: doctorsMenu(); break;
                case 2: patientsMenu(); break;
                case 3: appointmentsMenu(); break;
                case 0: std::cout << "Goodbye!\n"; break;
                default: throw InvalidInputException("Opțiune invalidă selectată în meniul principal: " + std::to_string(choice));

            }
        } catch (const SpitalException& e) {
            std::cout << "[Eroare] " << e.what() << "\n";
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
        std::cout << "5. Remove disease from patient\n";
        std::cout << "0. Back to main menu\n";
        std::cout << "Choice: ";
        std::string input;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        if (!(iss >> choice)) {
            choice = -1;
        }
        try {
        switch (choice) {
            case 1:
                hospital.listAllDoctors();
                break;
            case 2: {
                std::string doctorName = readValidName("Enter doctor's name: ");

                const Doctor* doctor = hospital.findDoctorByName(doctorName);
                if (!doctor) {
                    throw EntityNotFoundException("Doctorul \"" + doctorName + "\" nu a fost găsit.");
                }
                std::cout << *doctor << "\n";

                break;
            }
            case 3: {
                std::string doctorName = readValidName("Enter doctor's name: ");
                std::string patientName = readValidName("Enter patient's name: ");

                Doctor* doctor = hospital.findDoctorByName(doctorName);
                Patient* patient = nullptr;
                for (const auto& p : patients) {
                    if (p->getName() == patientName) {
                        patient = p.get();
                        break;
                    }
                }

                if (!doctor) {
                    throw EntityNotFoundException("Doctorul \"" + doctorName + "\" nu a fost găsit.");
                }
                if (!patient) {
                    throw EntityNotFoundException("Pacientul \"" + patientName + "\" nu a fost găsit.");
                }


                bool matched = false;
                for (const std::string& disease : patient->getDiseases()) {
                    auto it = diseaseToSpecialty.find(disease);
                    if (it != diseaseToSpecialty.end() && it->second == doctor->getSpecialty()) {
                        const auto& assigned = doctor->getPatients();
                        if (std::find(assigned.begin(), assigned.end(), patient) == assigned.end()) {
                            doctor->assignPatient(patient);
                            std::cout << "Patient assigned successfully.\n";
                            matched = true;
                            break;
                        } else {
                            std::cout << "Patient already assigned to this doctor.\n";
                            matched = true;
                            break;
                        }
                    }
                }

                if (!matched) {
                    throw InvalidInputException("Doctorul \"" + doctorName + "\" nu este calificat pentru bolile pacientului \"" + patientName + "\".");
                }
                break;
            }

            case 4: {
                std::string doctorName = readValidName("Enter doctor's name: ");
                std::string patientName = readValidName("Enter patient's name: ");


                Doctor* doctor = hospital.findDoctorByName(doctorName);
                if (!doctor) {
                    throw EntityNotFoundException("Doctorul \"" + doctorName + "\" nu a fost găsit.");
                }
                if (!doctor->dischargePatient(patientName)) {
                    throw EntityNotFoundException("Pacientul \"" + patientName + "\" nu este asociat acestui doctor.");
                }
                std::cout << "Pacient externat cu succes.\n";

                break;
            }
            case 5: {
                std::string doctorName = readValidName("Enter doctor's name: ");
                std::string patientName = readValidName("Enter patient's name: ");
                std::string disease;

                std::cout << "Enter disease to remove: ";
                std::getline(std::cin, disease);

                const Doctor* doctor = hospital.findDoctorByName(doctorName);
                if (!doctor) {
                    std::cout << "Doctor not found.\n";
                    break;
                }

                auto& assignedPatients = doctor->getPatients();
                auto it = std::find_if(assignedPatients.begin(), assignedPatients.end(), [&](const Patient* p) {
                    return p && p->getName() == patientName;
                });

                if (it != assignedPatients.end()) {
                    (*it)->removeDisease(disease);
                    std::cout << "Disease removed (if existed).\n";
                } else {
                    std::cout << "Patient not found under this doctor.\n";
                }
                break;
            }
            case 0:
                break;
            default:
                throw InvalidInputException("Opțiune invalidă selectată în meniul programărilor: " + std::to_string(choice));

        }
        } catch (const SpitalException& e) {
            std::cout << "[Eroare] " << e.what() << "\n";
        }
    } while (choice != 0);
}

void Menu::patientsMenu() {
    int choice;
    do {
        std::cout << "\n--- Patients Menu ---\n";
        std::cout << "1. List all patients\n";
        std::cout << "2. Add new patient\n";
        std::cout << "3. Show patient details\n";
        std::cout << "0. Back to main menu\n";
        std::cout << "Choice: ";
        std::string input;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        if (!(iss >> choice)) {
            choice = -1;
        }


        try {
            switch (choice) {
                case 1:
                    for (const auto& p : patients) {
                        std::cout << *p << "\n";
                    }
                    break;
                case 2: {
                    std::string cnp, genderStr, diseasesStr;
                    int age;

                    std::string name = readValidName("Enter patient's name: ");


                    std::cout << "Enter CNP: ";
                    std::getline(std::cin, cnp);
                    if (!Patient::isValidCNP(cnp)) {
                        throw InvalidCNPException();
                    }

                    std::cout << "Enter age: ";
                    if (!(std::cin >> age)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        throw InvalidInputException("Vârsta introdusă nu este un număr valid.");
                    }

                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                    std::cout << "Enter gender (M/F): ";
                    std::getline(std::cin, genderStr);
                    if (genderStr.empty()) {
                        throw InvalidInputException("Genul nu a fost introdus.");
                    }
                    char gender = toupper(genderStr[0]);
                    if (gender != 'M' && gender != 'F') {
                        throw InvalidInputException("Genul trebuie să fie M sau F.");
                    }


                    std::cout << "Enter diseases (comma-separated, leave empty if none): ";
                    std::getline(std::cin, diseasesStr);

                    auto newPatient = std::make_unique<Patient>(name, cnp, age, gender);

                    if (!diseasesStr.empty()) {
                        std::istringstream diseaseStream(diseasesStr);
                        std::string disease;
                        while (std::getline(diseaseStream, disease, ',')) {
                            if (!disease.empty()) {
                                newPatient->addDisease(disease);
                            }
                        }
                    }

                    patients.push_back(std::move(newPatient));
                    std::cout << "Patient added successfully.\n";
                    break;
                }

                case 3: {
                    std::string patientName = readValidName("Enter patient's name: ");

                    for (const auto& p : patients) {
                        if (p->getName() == patientName) {
                            std::cout << *p << "\n";
                            std::cout << "Press ENTER to continue...\n";
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            break;
                        }
                    }
                    break;
                }


                case 0:
                    break;
                default:
                    throw InvalidInputException("Opțiune invalidă selectată în meniul programărilor: " + std::to_string(choice));

            }
        } catch (const SpitalException& e) {
            std::cout << "[Eroare] " << e.what() << "\n";
        }
    } while (choice != 0);
}

void Menu::appointmentsMenu() {
    int choice;
    do {
        std::cout << "\n--- Appointments Menu ---\n";
        std::cout << "1. List appointments\n";
        std::cout << "2. Add new appointment\n";
        std::cout << "0. Back to main menu\n";
        std::cout << "Choice: ";
        std::string input;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        if (!(iss >> choice)) {
            choice = -1;
        }
        try {
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
        throw EntityNotFoundException("Doctorul \"" + doctorName + "\" nu a fost găsit.");
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
        throw EntityNotFoundException("Pacientul \"" + patientName + "\" nu a fost găsit.");
    }

    // Verificam daca pacientul este asignat acestui doctor
    const auto& assigned = doctor->getPatients();
    if (std::find(assigned.begin(), assigned.end(), patient) == assigned.end()) {
        throw InvalidAppointmentException("Pacientul \"" + patientName + "\" nu este asignat doctorului \"" + doctorName + "\".");
    }

    // Verificam daca specialitatea doctorului acopera boala pacientului
    bool specialtyMatch = false;
    for (const std::string& disease : patient->getDiseases()) {
        auto it = diseaseToSpecialty.find(disease);
        if (it != diseaseToSpecialty.end() && it->second == doctor->getSpecialty()) {
            specialtyMatch = true;
            break;
        }
    }

    if (!specialtyMatch) {
        throw InvalidAppointmentException("Doctorul \"" + doctorName + "\" nu este calificat pentru bolile pacientului \"" + patientName + "\".");
    }

    std::cout << "Enter date (YYYY-MM-DD): ";
    std::getline(std::cin, date);
    std::cout << "Enter time (HH:MM): ";
    std::getline(std::cin, time);

    if (!hospital.isDoctorAvailable(doctor, date, time)) {
        throw AppointmentConflictException();
    }

    auto appointment = std::make_unique<Appointment>(date, time, doctor, patient);
    if (appointment->isValidDateTime() && appointment->isInFuture()) {
        hospital.addAppointment(std::move(appointment));
        std::cout << "Appointment added.\n";
    } else {
        throw InvalidAppointmentException("Data și ora introduse nu sunt valide sau se află în trecut.");
    }
    break;
}
            case 0:
                break;
            default:
                throw InvalidInputException("Opțiune invalidă selectată în meniul programărilor: " + std::to_string(choice));

        }
        } catch (const SpitalException& e) {
            std::cout << "[Eroare] " << e.what() << "\n";
        }
    } while (choice != 0);
}
