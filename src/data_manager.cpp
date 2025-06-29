#include "../includes/data_manager.h"
#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/patient.h"
#include "../includes/appointment.h"
#include "../includes/inventory_manager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <algorithm>

void DataManager::loadDoctors(Hospital& hospital, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
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

void DataManager::loadPatients(std::vector<std::unique_ptr<Patient>>& patients, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin) {
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

void DataManager::loadAppointments(Hospital& hospital,
                                   const std::vector<std::unique_ptr<Patient>>& patients,
                                   const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "[ERROR] Cannot open appointments file: " << filename << "\n";
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
                    validAppointments.emplace_back(doctorName, patientName, date, time);
                    hospital.addAppointment(std::move(appointment));
                } else {
                    std::cerr << "[INVALID] Skipped appointment (invalid datetime): " << line << "\n";
                }
            } else {
                std::cerr << "[WARNING] Skipped appointment (doctor/patient not found): " << line << "\n";
            }
        }
    }

    fin.close();

    if (!validAppointments.empty()) {
        std::ofstream fout(filename, std::ios::trunc);
        for (const auto& [doctorName, patientName, date, time] : validAppointments) {
            fout << doctorName << "," << patientName << "," << date << "," << time << "\n";
        }
    }
}

std::map<std::string, std::string> DataManager::loadDiseaseSpecialty(const std::string& filename) {
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

void DataManager::loadInventory(const std::string& itemsFile, const std::string& budgetFile) {
    InventoryManager& inv = InventoryManager::getInstance();
    inv.loadBudget(budgetFile);
    inv.loadFromCSV(itemsFile);
}

void DataManager::saveInventory(const std::string& itemsFile, const std::string& budgetFile) {
    InventoryManager& inv = InventoryManager::getInstance();
    inv.saveToCSV(itemsFile);
    inv.saveBudget(budgetFile);
}

void DataManager::saveHospital(const Hospital& hospital,
                               const std::vector<std::unique_ptr<Patient>>& patients,
                               const std::string& appointmentsFile,
                               const std::string& patientsFile) {
    // Save appointments
    std::ofstream foutApp(appointmentsFile);
    if (!foutApp.is_open()) {
        std::cerr << "[ERROR] Cannot open file to write appointments: " << appointmentsFile << "\n";
    } else {
        for (const auto& app : hospital.getAppointments()) {
            foutApp << app->getDoctor()->getName() << ","
                    << app->getPatient()->getName() << ","
                    << app->getDate() << ","
                    << app->getTime() << "\n";
        }
    }

    // Save patients
    std::ofstream foutPat(patientsFile);
    if (!foutPat.is_open()) {
        std::cerr << "[ERROR] Cannot open file to write patients: " << patientsFile << "\n";
    } else {
        for (const auto& p : patients) {
            foutPat << p->getName() << "," << p->getCNP() << "," << p->getAge() << "," << p->getGender() << ",";
            const auto& diseases = p->getDiseases();
            for (auto it = diseases.begin(); it != diseases.end(); ++it) {
                foutPat << *it;
                if (std::next(it) != diseases.end())
                    foutPat << "|";
            }
            foutPat << "\n";
        }
    }
}

void DataManager::loadHospital(Hospital& hospital,
                               std::vector<std::unique_ptr<Patient>>& patients,
                               const std::string& doctorsFile,
                               const std::string& patientsFile,
                               const std::string& appointmentsFile) {
    loadDoctors(hospital, doctorsFile);
    loadPatients(patients, patientsFile);
    loadAppointments(hospital, patients, appointmentsFile);
}

void DataManager::assignPatients(const Hospital& hospital,
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

DataManager& DataManager::getInstance() {
    static DataManager instance;
    return instance;
}