#include "includes/hospital.h"
#include "includes/doctor.h"
#include "includes/patient.h"
#include "includes/appointment.h"
#include "includes/menu.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>

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

    // suprascriem fisierul cu  prog valide
    std::ofstream fout(filename, std::ios::trunc);
    for (const auto& [doctorName, patientName, date, time] : validAppointments) {
        fout << doctorName << "," << patientName << "," << date << "," << time << "\n";
    }
    fout.close();
}

void assignPatients(const Hospital& hospital, std::vector<std::unique_ptr<Patient>>& patients) {
    auto& doctors = hospital.getDoctors();
    if (doctors.empty()) {
        std::cerr << "No doctors available to assign patients.\n";
        return;
    }

    int doctorIndex = 0;
    for (auto& p : patients) {
        if (p) {
            doctors[doctorIndex]->assignPatient(p.get());
            doctorIndex = (doctorIndex + 1) % doctors.size();
        }
    }
}

int main() {
        Hospital hospital("Spitalul Municipal");
        std::vector<std::unique_ptr<Patient>> patients;

        loadDoctors(hospital, "data/doctors.csv");
        loadPatients(patients, "data/patients.csv");
        assignPatients(hospital, patients);
        loadAppointments(hospital, patients, "data/appointments.csv");

        Menu menu(hospital, patients);
        menu.showMainMenu();

        return 0;
}

