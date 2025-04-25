#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include <limits>
#include "../includes/hospital.h"
#include "../includes/location.h"
#include "../includes/doctor.h"
#include "../includes/patient.h"
#include "../includes/appointment.h"
#include "../includes/medical_data.h"

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

Patient* findPatientByName(const std::vector<std::unique_ptr<Patient>>& patients, const std::string& name) {
    for (const auto& p : patients) {
        if (p->getName() == name) {
            return p.get();
        }
    }
    return nullptr;
}

int main() {
    Location romania("Romania", +2);
    std::unique_ptr<Hospital> hospital = std::make_unique<Hospital>("Spitalul Municipal Bucuresti", romania);
    std::unique_ptr<Hospital> backupHospital = nullptr;

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

        hospital->addDoctor(std::move(doctor));
    }

    for (const auto& docPtr : hospital->getDoctors()) {
        if (!docPtr->getPatientList().empty()) {
            hospital->scheduleAppointment(docPtr->getName(), docPtr->getPatientList()[0],
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
        std::cout << "12. Restore Hospital from Backup\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        clearInput();

        switch (choice) {
            case 11: {
                std::cout << "Creating Backup...\n";
                backupHospital = std::make_unique<Hospital>("Backup - Spitalul Municipal Bucuresti", hospital->getLocation());
                for (const auto& doctor : hospital->getDoctors()) {
                    auto newDoctor = std::make_unique<Doctor>(doctor->getName(), doctor->getSpecialty());
                    for (const auto& patient : doctor->getPatientList()) {
                        newDoctor->assignPatient(patient);
                    }
                    for (const auto& appointment : doctor->getAppointments()) {
                        auto newAppointment = std::make_unique<Appointment>(
                            appointment->getDate(),
                            appointment->getTime(),
                            newDoctor.get(),
                            appointment->getTimezoneOffset()
                        );
                        newDoctor->addAppointment(newAppointment.get());
                        backupHospital->addAppointment(std::move(newAppointment));
                    }
                    backupHospital->addDoctor(std::move(newDoctor));
                }
                std::cout << "Backup completed successfully!\n";
                break;
            }
            case 12: {
                if (backupHospital) {
                    std::cout << "Restoring Backup...\n";
                    hospital = std::make_unique<Hospital>(backupHospital->getName() + " (Restored)", backupHospital->getLocation());
                    for (const auto& doctor : backupHospital->getDoctors()) {
                        auto newDoctor = std::make_unique<Doctor>(doctor->getName(), doctor->getSpecialty());
                        for (const auto& patient : doctor->getPatientList()) {
                            Patient* existingPatient = findPatientByName(allPatients, patient->getName());
                            if (existingPatient) {
                                newDoctor->assignPatient(existingPatient);
                            }
                        }
                        for (const auto& appointment : doctor->getAppointments()) {
                            auto newAppointment = std::make_unique<Appointment>(
                                appointment->getDate(),
                                appointment->getTime(),
                                newDoctor.get(),
                                appointment->getTimezoneOffset()
                            );
                            newDoctor->addAppointment(newAppointment.get());
                            hospital->addAppointment(std::move(newAppointment));
                        }
                        hospital->addDoctor(std::move(newDoctor));
                    }
                    std::cout << "Hospital restored successfully!\n";
                } else {
                    std::cout << "No backup found to restore!\n";
                }
                break;
            }
        }
    } while (choice != 0);

    return 0;
}