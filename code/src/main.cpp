#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <algorithm>
#include <functional>
#include <cctype>
#include <regex>
#include "../includes/hospital.h"
#include "../includes/location.h"
#include "../includes/doctor.h"
#include "../includes/patient.h"
#include "../includes/appointment.h"
#include "../includes/medical_data.h"


void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pause() {
    std::cout << "\n[Press Enter to continue]";
    std::cin.get();
}


int promptIntInRange(const std::string& prompt, int min, int max) {
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) continue;
        try {
            int v = std::stoi(line);
            if (v >= min && v <= max) return v;
        } catch (...) {}
        std::cout << "Please enter a number between " << min << " and " << max << ".\n";
    }
}

bool promptYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::string line;
        if (!std::getline(std::cin, line)) continue;
        if (line.empty()) continue;
        char c = std::tolower(line[0]);
        if (c == 'y') return true;
        if (c == 'n') return false;
        std::cout << "Please answer 'y' or 'n'.\n";
    }
}


std::string promptValidated(
    const std::string& prompt,
    const std::function<bool(const std::string&)>& validator,
    const std::string& errorMsg
) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        if (validator(line)) return line;
        std::cout << errorMsg << "\n";
    }
}

Patient* findPatientByName(
    const std::vector<std::unique_ptr<Patient>>& patients,
    const std::string& name
) {
    for (const auto& p : patients) {
        if (p->getName() == name) return p.get();
    }
    return nullptr;
}

std::string generateCNP(bool male, int year, int month, int day, int index) {
    int genderDigit = male ? 1 : 2;
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%d%02d%02d%02d%02d%03d",
                  genderDigit,
                  year % 100,
                  month,
                  day,
                  (index % 52) + 1,
                  index % 1000);
    return std::string(buf);
}

void runHealthQuiz(Patient* patient, Hospital* hospital) {
    std::cout << "\n=== Health Assessment Quiz ===\n"
              << "Answer each question with 'yes' or 'no'.\n\n";

    struct DiseaseInfo {
        std::string name;
        std::vector<std::string> questions;
        double cost;
    };
    std::vector<DiseaseInfo> quiz = {
        {"Heart Disease", {"Chest pain or tightness?", "Irregular heartbeat or palpitations?"}, 500.0},
        {"Diabetes",      {"Excessive thirst?", "Frequent urination?"}, 400.0},
        {"Asthma",        {"Wheezing or difficulty breathing?", "Nighttime coughing?"}, 350.0},
        {"Pneumonia",     {"High fever?", "Cough producing colored phlegm?"}, 450.0},
        {"Skin Rash",     {"Itchy or inflamed skin patches?", "New rash outbreaks?"}, 300.0},
        {"Brain Tumor",   {"Persistent headaches?", "Sudden seizures or vision changes?"}, 1000.0},
        {"Flu",           {"Fever with body aches?", "Sore throat or chills?"}, 300.0},
        {"Allergy",       {"Sneezing or itchy eyes?", "Reactions to pollen or food?"}, 200.0}
    };

    std::vector<std::string> detected;
    for (auto& di : quiz) {
        int positives = 0;
        for (auto& q : di.questions) {
            if (promptYesNo(q)) positives++;
        }
        if (positives > 0 && Patient::isValidDisease(di.name)) {
            patient->addDisease(di.name, di.cost);
            detected.push_back(di.name);
        }
    }

    if (detected.empty()) {
        std::cout << "\nNo significant conditions detected. Patient remains healthy.\n";
        return;
    }

    std::cout << "\nDetected conditions:\n";
    for (auto& d : detected) {
        std::cout << " - " << d << "\n";
    }

    std::vector<std::string> specsDone;
    std::cout << "\nRecommended specialists:\n";
    for (auto& d : detected) {
        auto spec = diseaseToSpecialty.at(d);
        if (Doctor::isValidSpecialty(spec) &&
            std::find(specsDone.begin(), specsDone.end(), spec) == specsDone.end()) {
            specsDone.push_back(spec);
            std::cout << " * " << spec << ":\n";
            for (auto& docPtr : hospital->getDoctors()) {
                if (docPtr->getSpecialty() == spec)
                    std::cout << "    - Dr. " << docPtr->getName() << "\n";
            }
        }
    }

    if (promptYesNo("\nAssign this patient to one of these doctors?")) {
        auto docName = promptValidated(
            "Enter full doctor name: ",
            [&](auto& s){ return !s.empty(); },
            "Name cannot be empty."
        );
        hospital->addPatientToDoctor(docName, patient);
        std::cout << "Patient assigned to Dr. " << docName << ".\n";
    }
}

int main() {
    Location loc("Romania", +2);
    auto hospital = std::make_unique<Hospital>("Spitalul Municipal Bucuresti", loc);


    const std::vector<std::pair<std::string, std::string>> doctorInfo = {
        {"Andrei Popescu","Cardiologist"},{"Ioana Marinescu","Endocrinologist"},
        {"Mihai Dumitrescu","Neurologist"},{"Elena Stan","Pulmonologist"},
        {"Vlad Ionescu","General Practitioner"},{"Ana Petrescu","Dermatologist"},
        {"George Enache","Orthopedist"},{"Cristina Gheorghiu","Allergist"},
        {"Florin Radu","Cardiologist"},{"Daniela Apostol","General Practitioner"}
    };
    for (auto& di : doctorInfo) {
        hospital->addDoctor(std::make_unique<Doctor>(di.first, di.second));
    }

    std::vector<std::unique_ptr<Patient>> allPatients;
    allPatients.reserve(20);

    while (true) {
        std::cout << "\n=== Spitalul Municipal Bucuresti ===\n"
                  << "1) Hospital Info\n"
                  << "2) Doctors\n"
                  << "3) Patients\n"
                  << "4) Appointments\n"
                  << "5) Analytics\n"
                  << "0) Exit\n";
        int mainOpt = promptIntInRange("Select: ", 0, 5);

        if (mainOpt == 0) {
            std::cout << "\nGoodbye!\n";
            break;
        }

        switch (mainOpt) {
            case 1:
                std::cout << "\n";
                hospital->printInfo();
                pause();
                break;

            case 2: {
                while (true) {
                    std::cout << "\n--- Doctors ---\n"
                              << "1) List all\n"
                              << "2) View a doctor's patients\n"
                              << "3) Add new doctor\n"
                              << "4) Assign existing patient\n"
                              << "0) Back\n";
                    int opt = promptIntInRange("Choice: ", 0, 4);
                    if (opt == 0) break;
                    switch (opt) {
                        case 1:
                            std::cout << "\n";
                            hospital->printDoctors();
                            pause();
                            break;
                        case 2: {
                            auto dn = promptValidated(
                                "\nDoctor name: ",
                                [&](auto& s){ return !s.empty(); },
                                "Name cannot be empty."
                            );
                            for (auto& dptr : hospital->getDoctors()) {
                                if (dptr->getName() == dn) {
                                    std::cout << "\n";
                                    dptr->printPatients();
                                    break;
                                }
                            }
                            pause();
                        } break;
                        case 3: {
                            auto dn = promptValidated(
                                "\nNew doctor name: ",
                                [&](auto& s){ return !s.empty(); },
                                "Name cannot be empty."
                            );
                            auto sp = promptValidated(
                                "Specialty: ",
                                [&](auto& s){ return Doctor::isValidSpecialty(s); },
                                "Unknown specialty."
                            );
                            hospital->addDoctor(std::make_unique<Doctor>(dn, sp));
                            std::cout << "Doctor added.\n";
                            pause();
                        } break;
                        case 4: {
                            auto pn = promptValidated(
                                "\nPatient name: ",
                                [&](auto& s){ return !s.empty(); },
                                "Name cannot be empty."
                            );
                            Patient* p = findPatientByName(allPatients, pn);
                            if (!p) {
                                std::cout << "Patient not found.\n";
                                pause();
                                break;
                            }
                            auto dn = promptValidated(
                                "Doctor name: ",
                                [&](auto& s){ return !s.empty(); },
                                "Name cannot be empty."
                            );
                            hospital->addPatientToDoctor(dn, p);
                            pause();
                        } break;
                    }
                }
            } break;

            case 3: {
                while (true) {
                    std::cout << "\n--- Patients ---\n"
                              << "1) List all\n"
                              << "2) View details\n"
                              << "3) Register new\n"
                              << "4) Add funds\n"
                              << "5) Add disease manually\n"
                              << "6) Remove disease\n"
                              << "0) Back\n";
                    int opt = promptIntInRange("Choice: ", 0, 6);
                    if (opt == 0) break;
                    switch (opt) {
                        case 1:
                            std::cout << "\n";
                            for (auto& p : allPatients) {
                                p->printInfo();
                                std::cout << "\n";
                            }
                            pause();
                            break;
                        case 2: {
                            auto pn = promptValidated(
                                "\nPatient name: ",
                                [&](auto& s){ return !s.empty(); },
                                "Name cannot be empty."
                            );
                            Patient* p = findPatientByName(allPatients, pn);
                            if (p) {
                                std::cout << "\n";
                                p->printInfo();
                                std::cout << "Total cost: $" << p->getTotalTreatmentCost() << "\n";
                            } else {
                                std::cout << "Not found.\n";
                            }
                            pause();
                        } break;
                        case 3: {
                            auto nm = promptValidated(
                                "\nName: ",
                                [&](auto& s){ return Patient::isValidName(s); },
                                "Invalid name format."
                            );
                            auto cnp = promptValidated(
                                "CNP: ",
                                [&](auto& s){ return Patient::isValidCNP(s); },
                                "Invalid CNP format."
                            );
                            int age = promptIntInRange("Age: ", 0, 150);
                            char g = '\0';
                            while (true) {
                                std::cout << "Gender (M/F): ";
                                std::string gg; std::getline(std::cin, gg);
                                if (!gg.empty()) {
                                    char c = std::toupper(gg[0]);
                                    if (c=='M'||c=='F') { g = c; break; }
                                }
                                std::cout << "Please enter M or F.\n";
                            }
                            auto newP = std::make_unique<Patient>(nm, age, g, cnp, 0.0);
                            runHealthQuiz(newP.get(), hospital.get());
                            if (newP->isHealthy()) {
                                std::cout << "No conditions detected. Patient not added.\n";
                            } else {
                                allPatients.push_back(std::move(newP));
                                std::cout << "Patient registered.\n";
                            }
                            pause();
                        } break;
                        case 4: {
                            auto pn = promptValidated(
                                "\nPatient name: ",
                                [&](auto& s){ return !s.empty(); },
                                "Name cannot be empty."
                            );
                            Patient* p = findPatientByName(allPatients, pn);
                            if (p) {
                                double amt;
                                std::cout << "Amount to add: $";
                                std::cin >> amt; clearInput();
                                p->addFunds(amt);
                                std::cout << "New balance: $" << p->getFunds() << "\n";
                            } else {
                                std::cout << "Not found.\n";
                            }
                            pause();
                        } break;
                        case 5: {
                            auto pn = promptValidated(
                                "\nPatient name: ",
                                [&](auto& s){ return !s.empty(); },
                                "Name cannot be empty."
                            );
                            Patient* p = findPatientByName(allPatients, pn);
                            if (p) {
                                auto d = promptValidated(
                                    "Disease: ",
                                    [&](auto& s){ return Patient::isValidDisease(s); },
                                    "Unknown disease."
                                );
                                double cost;
                                std::cout << "Cost: $";
                                std::cin >> cost; clearInput();
                                p->addDisease(d, cost);
                                std::cout << "Disease added.\n";
                            } else {
                                std::cout << "Not found.\n";
                            }
                            pause();
                        } break;
                        case 6: {
                            auto pn = promptValidated(
                                "\nPatient name: ",
                                [&](auto& s){ return !s.empty(); },
                                "Name cannot be empty."
                            );
                            Patient* p = findPatientByName(allPatients, pn);
                            if (p) {
                                auto d = promptValidated(
                                    "Disease to remove: ",
                                    [&](auto& s){ return !s.empty(); },
                                    "Name cannot be empty."
                                );
                                p->removeDisease(d);
                                std::cout << "Removed if present.\n";
                            } else {
                                std::cout << "Not found.\n";
                            }
                            pause();
                        } break;
                    }
                }
            } break;

            case 4: {
                while (true) {
                    std::cout << "\n--- Appointments ---\n"
                              << "1) List all\n"
                              << "2) Schedule\n"
                              << "3) Discharge & recheck\n"
                              << "0) Back\n";
                    int opt = promptIntInRange("Choice: ", 0, 3);
                    if (opt == 0) break;
                    switch (opt) {
                        case 1:
                            std::cout << "\n";
                            hospital->printAppointments();
                            pause();
                            break;
                        case 2: {
                            auto dn = promptValidated(
                                "\nDoctor name: ",
                                [&](auto& s){ return !s.empty(); },
                                "Name cannot be empty."
                            );
                            auto pn = promptValidated(
                                "Patient name: ",
                                [&](auto& s){ return !s.empty(); },
                                "Name cannot be empty."
                            );
                            auto dt = promptValidated(
                                "Date (YYYY-MM-DD): ",
                                [&](auto& s){ return Appointment::isValidDateTime(s, "00:00", loc.getTimezoneOffset()); },
                                "Invalid date format."
                            );
                            auto tm = promptValidated(
                                "Time (HH:MM): ",
                                [&](auto& s){ return Appointment::isValidDateTime("1970-01-01", s, loc.getTimezoneOffset()); },
                                "Invalid time format."
                            );
                            Patient* p = findPatientByName(allPatients, pn);
                            if (p) {
                                hospital->scheduleAppointment(dn, p, dt, tm);
                            } else {
                                std::cout << "Patient not found.\n";
                            }
                            pause();
                        } break;
                        case 3: {
                            auto dn = promptValidated(
                                "\nDoctor name: ",
                                [&](auto& s){ return !s.empty(); },
                                "Name cannot be empty."
                            );
                            auto pn = promptValidated(
                                "Patient name: ",
                                [&](auto& s){ return !s.empty(); },
                                "Name cannot be empty."
                            );
                            Patient* p = findPatientByName(allPatients, pn);
                            Doctor* docPtr = nullptr;
                            for (auto& dptr : hospital->getDoctors()) {
                                if (dptr->getName() == dn) {
                                    docPtr = dptr.get();
                                    break;
                                }
                            }
                            if (p && docPtr) {
                                hospital->dischargePatient(p, docPtr);
                                p->clearDiseases();
                                std::cout << "Discharged.\n";
                            } else {
                                std::cout << "Doctor or patient not found.\n";
                            }
                            pause();
                        } break;
                    }
                }
            } break;

            case 5: {
                while (true) {
                    std::cout << "\n--- Analytics ---\n"
                              << "1) Total profit\n"
                              << "2) Most common diseases\n"
                              << "0) Back\n";
                    int opt = promptIntInRange("Choice: ", 0, 2);
                    if (opt == 0) break;
                    switch (opt) {
                        case 1:
                            std::cout << "\nTotal profit: $" << hospital->getProfit() << "\n";
                            pause();
                            break;
                        case 2: {
                            auto top = hospital->getMostCommonDiseases();
                            std::cout << "\nTop diseases:\n";
                            for (auto& pr : top) {
                                std::cout << " - " << pr.first
                                          << " (" << pr.second << " cases)\n";
                            }
                            pause();
                        } break;
                    }
                }
            } break;
        }
    }

    return 0;
}
