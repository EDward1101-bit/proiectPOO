#include "includes/hospital.h"
#include "includes/doctor.h"
#include "includes/patient.h"
#include "includes/appointment.h"
#include "includes/menu.h"
#include "includes/inventory_manager.h"
#include "includes/spital_exception.h"
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

void loadDoctors(Hospital& hospital, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening doctors file.\n";
        return;
    }
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string name, specialty;
        if (std::getline(iss, name, ',') && std::getline(iss, specialty)) {
            hospital.addDoctor(std::make_unique<Doctor>(name, specialty));
        }
    }
}

void loadPatients(std::vector<std::unique_ptr<Patient>>& patients, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening patients file.\n";
        return;
    }

    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string name, cnp, ageStr, genderStr, diseasesStr;

        if (std::getline(iss, name, ',') &&
            std::getline(iss, cnp, ',') &&
            std::getline(iss, ageStr, ',') &&
            std::getline(iss, genderStr, ',') &&
            std::getline(iss, diseasesStr)) {

            int age = std::stoi(ageStr);
            char gender = genderStr.empty() ? 'U' : genderStr[0];
            auto patient = std::make_unique<Patient>(name, cnp, age, gender);

            std::istringstream diseaseStream(diseasesStr);
            std::string disease;
            while (std::getline(diseaseStream, disease, '|')) {
                if (!disease.empty()) {
                    patient->addDisease(disease);
                }
            }

            patients.push_back(std::move(patient));
            }
    }
}

void loadAppointments(Hospital& hospital, const std::vector<std::unique_ptr<Patient>>& patients, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening appointments file.\n";
        return;
    }

    std::vector<std::tuple<std::string, std::string, std::string, std::string>> validAppointments;
    std::string line;

    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string doctorName, patientName, date, time;
        if (std::getline(iss, doctorName, ',') &&
            std::getline(iss, patientName, ',') &&
            std::getline(iss, date, ',') &&
            std::getline(iss, time)) {

            Doctor* doctor = hospital.findDoctorByName(doctorName);
            Patient* patient = nullptr;
            for (const auto& p : patients) {
                if (p->getName() == patientName) {
                    patient = p.get();
                    break;
                }
            }

            if (doctor && patient) {
                auto appointment = std::make_unique<Appointment>(date, time, doctor, patient);
                if (appointment->isValidDateTime() && appointment->isInFuture()) {
                    validAppointments.push_back({doctorName, patientName, date, time});
                    hospital.addAppointment(std::move(appointment));
                }
            }
            }
    }
    fin.close();

    // suprascriem fisierul cu prog valide
    std::ofstream fout(filename, std::ios::trunc);
    for (const auto& [doctorName, patientName, date, time] : validAppointments) {
        fout << doctorName << "," << patientName << "," << date << "," << time << "\n";
    }
    fout.close();
}

void assignPatients(const Hospital& hospital,
                    std::vector<std::unique_ptr<Patient>>& patients,
                    const std::map<std::string, std::string>& diseaseToSpecialty) {
    for (auto& p : patients) {
        if (!p) continue;

        for (const std::string& disease : p->getDiseases()) {
            auto it = diseaseToSpecialty.find(disease);
            if (it == diseaseToSpecialty.end()) continue;

            const std::string& requiredSpecialty = it->second;

            for (const auto& doc : hospital.getDoctors()) {
                if (doc->getSpecialty() == requiredSpecialty) {
                    const auto& assigned = doc->getPatients();
                    if (std::find(assigned.begin(), assigned.end(), p.get()) == assigned.end()) {
                        doc->assignPatient(p.get());
                        break;
                    }
                }
            }
        }
    }
}

std::map<std::string, std::string> loadDiseaseSpecialty(const std::string& filename) {
    std::map<std::string, std::string> mapping;
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Error opening disease_specialty file.\n";
        return mapping;
    }

    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string disease, specialty;
        if (std::getline(iss, disease, ',') && std::getline(iss, specialty)) {
            mapping[disease] = specialty;
        }
    }

    return mapping;
}

int main() {
        InventoryManager inv;
        inv.loadBudget("data/admin.csv");
        inv.loadFromCSV("data/inventory.csv");
        Hospital hospital("Spitalul Municipal");
        std::vector<std::unique_ptr<Patient>> patients;

        loadDoctors(hospital, "data/doctors.csv");
        loadPatients(patients, "data/patients.csv");
        auto diseaseToSpecialty = loadDiseaseSpecialty("data/disease_specialty.csv");
        assignPatients(hospital, patients, diseaseToSpecialty);

        loadAppointments(hospital, patients, "data/appointments.csv");

        Menu menu(hospital, patients, diseaseToSpecialty);

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

            hospital.saveAppointmentsToCSV("data/appointments.csv");
            hospital.savePatientsToCSV(patients, "data/patients.csv");
        } else if (choice == "2") {
            inv.showMenu();
            inv.saveToCSV("data/inventory.csv");
            inv.saveBudget("data/admin.csv");
        } else if (choice == "0") {
            break;
        } else {
            std::cout << "Invalid.\n";
        }
    }



/*
    std::cout << "\n--- Pacienti neasignati niciunui doctor ---\n";
    for (const auto& p : patients) {
        bool assigned = false;
        for (const auto& doc : hospital.getDoctors()) {
            const auto& list = doc->getPatients();
            if (std::find(list.begin(), list.end(), p.get()) != list.end()) {
                assigned = true;
                break;
            }
        }
        if (!assigned) {
            std::cout << *p << "\n";
        }
    }
*/


        return 0;
}

