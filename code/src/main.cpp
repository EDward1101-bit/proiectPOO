#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <limits>
#include "hospital.h"
#include "location.h"
#include "doctor.h"
#include "patient.h"
#include "appointment.h"
#include "medical_data.h"

// Real doctor and patient names
const std::vector<std::pair<std::string, std::string>> doctorInfo = {
    {"Andrei Popescu", "Cardiologist"},
    {"Ioana Marinescu", "Endocrinologist"},
    {"Mihai Dumitrescu", "Neurologist"},
    {"Elena Stan", "Pulmonologist"},
    {"Vlad Ionescu", "General Practitioner"},
    {"Ana Petrescu", "Dermatologist"},
    {"George Enache", "Orthopedist"},
    {"Cristina Gheorghiu", "Allergist"},
    {"Florin Radu", "Cardiologist"},
    {"Daniela Apostol", "General Practitioner"}
};

const std::vector<std::string> patientNames = {
    "Alina Stoica", "Paul Cristea", "Maria Ciobanu", "Dorel Vasilescu",
    "Ilinca Pop", "Bogdan Costache", "Andreea Nistor", "Radu Matei",
    "Camelia Sava", "Ionut Moldovan", "Sorina Neagu", "Costin Pavel",
    "Oana Cernat", "Sebastian Udrea", "Bianca Sima"
};

// Helper function to generate realistic CNP
std::string generateCNP(bool male, int year, int month, int day, int index) {
    int genderDigit = male ? 1 : 2;
    char buffer[14];
    snprintf(buffer, sizeof(buffer), "%d%02d%02d%02d%02d%03d",
             genderDigit, year % 100, month, day, (index % 52) + 1, index % 1000);
    return std::string(buffer);
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Location romania("Romania", +2);
    Hospital hospital("Spitalul Municipal Bucuresti", romania);
    Hospital backupHospital("Backup - Spitalul Municipal Bucuresti", romania);

    int patientCounter = 0;
    std::vector<std::unique_ptr<Patient>> allPatients;
    auto diseases = std::vector<std::string>(knownDiseases.begin(), knownDiseases.end());

    for (size_t i = 0; i < doctorInfo.size(); ++i) {
        auto doctor = std::make_unique<Doctor>(doctorInfo[i].first, doctorInfo[i].second);

        int numPatients = 2 + (i % 2);
        for (int j = 0; j < numPatients; ++j) {
            if (patientCounter >= patientNames.size()) break;

            bool isMale = (patientCounter % 2 == 0);
            int year = 1980 + (patientCounter % 30);
            int month = 1 + (patientCounter % 12);
            int day = 1 + (patientCounter % 28);

            std::string cnp = generateCNP(isMale, year, month, day, patientCounter);
            double funds = 1000 + (patientCounter * 50);

            auto patient = std::make_unique<Patient>(patientNames[patientCounter], 30 + (patientCounter % 10),
                                                     isMale ? 'M' : 'F', cnp, funds);

            std::string disease = diseases[(i + j) % diseases.size()];
            patient->addDisease(disease, 200.0 + (j * 50));

            doctor->assignPatient(patient.get());
            allPatients.push_back(std::move(patient));
            patientCounter++;
        }

        hospital.addDoctor(std::move(doctor));
    }

    for (const auto& docPtr : hospital.getDoctors()) {
        if (!docPtr->getPatientList().empty()) {
            hospital.scheduleAppointment(docPtr->getName(), docPtr->getPatientList()[0],
                                          "2025-06-01", "09:00");
        }
    }

    int choice;
    do {
        std::cout << "\n=== Spitalul Municipal Bucuresti ===\n";
        std::cout << "1. View Hospital Info\n";
        std::cout << "2. View Doctors List\n";
        std::cout << "3. View a Doctor's Patients\n";
        std::cout << "4. View All Patients\n";
        std::cout << "5. View Appointments\n";
        std::cout << "6. Schedule a New Appointment\n";
        std::cout << "7. Discharge a Patient\n";
        std::cout << "8. Add Funds to a Patient\n";
        std::cout << "9. View Hospital Total Profit\n";
        std::cout << "10. View Most Common Diseases\n";
        std::cout << "11. Backup Hospital\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        clearInput();

        switch (choice) {
            case 1:
                hospital.printInfo();
                break;
            case 2:
                hospital.printDoctors();
                break;
            case 3: {
                std::cout << "Enter Doctor's Name: ";
                std::string docName;
                getline(std::cin, docName);
                for (const auto& doc : hospital.getDoctors()) {
                    if (doc->getName() == docName) {
                        doc->printPatients();
                    }
                }
                break;
            }
            case 4:
                for (const auto& patient : allPatients) {
                    patient->printInfo();
                    std::cout << "\n";
                }
                break;
            case 5:
                hospital.printAppointments();
                break;
            case 6: {
                std::cout << "Enter Doctor's Name for Appointment: ";
                std::string docName;
                getline(std::cin, docName);
                std::cout << "Enter Appointment Date (YYYY-MM-DD): ";
                std::string date;
                getline(std::cin, date);
                std::cout << "Enter Appointment Time (HH:MM): ";
                std::string time;
                getline(std::cin, time);
                if (!hospital.getDoctors().empty()) {
                    hospital.scheduleAppointment(docName, nullptr, date, time);
                }
                break;
            }
            case 7: {
                std::cout << "Enter Doctor's Name: ";
                std::string docName;
                getline(std::cin, docName);
                for (const auto& doc : hospital.getDoctors()) {
                    if (doc->getName() == docName && !doc->getPatientList().empty()) {
                        std::cout << "Enter Patient Name to Discharge: ";
                        std::string patientName;
                        getline(std::cin, patientName);
                        for (Patient* p : doc->getPatientList()) {
                            if (p->getName() == patientName) {
                                hospital.dischargePatient(p, doc.get());
                                break;
                            }
                        }
                    }
                }
                break;
            }
            case 8: {
                std::cout << "Enter Patient Name to Add Funds: ";
                std::string patientName;
                getline(std::cin, patientName);
                for (auto& patient : allPatients) {
                    if (patient->getName() == patientName) {
                        std::cout << "Enter amount to add: ";
                        double amount;
                        std::cin >> amount;
                        clearInput();
                        patient->addFunds(amount);
                        std::cout << "Funds updated.\n";
                    }
                }
                break;
            }
            case 9:
                std::cout << "Hospital Profit: $" << hospital.getProfit() << "\n";
                break;
            case 10: {
                auto common = hospital.getMostCommonDiseases();
                for (const auto& [disease, count] : common) {
                    std::cout << disease << " - " << count << " patients\n";
                }
                break;
            }
            case 11:
                std::cout << "Backup Created!\n";
                backupHospital = hospital;
                break;
            case 0:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}