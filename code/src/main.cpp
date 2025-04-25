#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include <algorithm>
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

void waitForEnter() {
    std::cout << "[Press Enter to continue]";
    std::cin.get();
}

Patient* findPatientByName(const std::vector<std::unique_ptr<Patient>>& patients,
                           const std::string& name) {
    for (const auto& p : patients) {
        if (p->getName() == name) return p.get();
    }
    return nullptr;
}

std::string generateCNP(bool male, int year, int month, int day, int index) {
    int genderDigit = male ? 1 : 2;
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%d%02d%02d%02d%02d%03d",
                  genderDigit, year % 100, month, day, (index % 52) + 1, index % 1000);
    return std::string(buf);
}

void runHealthQuiz(Patient* patient, Hospital* hospital) {
    std::cout << "=== Health Assessment Quiz ===\n"
              << "Answer each question with 'yes' or 'no'.\n\n";

    struct DiseaseInfo {
        std::string name;
        std::vector<std::string> questions;
        double cost;
    };

    std::vector<DiseaseInfo> quiz = {
        { "Heart Disease", {"1) Chest pain or tightness?", "2) Irregular heartbeat or palpitations?"}, 500.0 },
        { "Diabetes",      {"1) Excessive thirst?",          "2) Frequent urination?"},          400.0 },
        { "Asthma",        {"1) Wheezing or difficulty breathing?", "2) Nighttime coughing?"}, 350.0 },
        { "Pneumonia",     {"1) High fever?",               "2) Cough producing colored phlegm?"}, 450.0 },
        { "Skin Rash",     {"1) Itchy or inflamed skin patches?", "2) New rash outbreaks?"}, 300.0 },
        { "Brain Tumor",   {"1) Persistent headaches?",    "2) Sudden seizures or vision changes?"}, 1000.0 },
        { "Flu",           {"1) Fever with body aches?",   "2) Sore throat or chills?"},      300.0 },
        { "Allergy",       {"1) Sneezing or itchy eyes?",  "2) Reactions to pollen or food?"}, 200.0 }
    };

    std::vector<std::string> detected;
    std::string answer;

    for (auto& di : quiz) {
        int positives = 0;
        for (const auto& q : di.questions) {
            std::cout << q << " ";
            std::getline(std::cin, answer);
            std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
            if (answer == "yes" || answer == "y") positives++;
        }
        if (positives > 0 && Patient::isValidDisease(di.name)) {
            patient->addDisease(di.name, di.cost);
            detected.push_back(di.name);
        }
    }

    if (detected.empty()) {
        std::cout << "\nNo significant conditions detected. You appear healthy!\n";
        waitForEnter();
        return;
    }

    std::cout << "\nDetected conditions:\n";
    for (const auto& d : detected) {
        std::cout << " - " << d << "\n";
    }

    std::cout << "\nRecommended specialists:\n";
    std::vector<std::string> recommendedSpecs;
    for (const auto& d : detected) {
        const auto& spec = diseaseToSpecialty.at(d);
        if (Doctor::isValidSpecialty(spec) &&
            std::find(recommendedSpecs.begin(), recommendedSpecs.end(), spec) == recommendedSpecs.end()) {
            recommendedSpecs.push_back(spec);
            std::cout << " * " << spec << ":\n";
            for (const auto& docPtr : hospital->getDoctors()) {
                if (docPtr->getSpecialty() == spec) {
                    std::cout << "    - Dr. " << docPtr->getName() << "\n";
                }
            }
        }
    }

    std::cout << "\nWould you like to assign this patient to one of these doctors? (yes/no) ";
    std::getline(std::cin, answer);
    std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    if (answer == "yes" || answer == "y") {
        std::cout << "Enter the full name of the doctor: ";
        std::string docName;
        std::getline(std::cin, docName);
        hospital->addPatientToDoctor(docName, patient);
    }

    waitForEnter();
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
    const std::vector<std::string> patientNames = {
        "Alina Stoica","Paul Cristea","Maria Ciobanu","Dorel Vasilescu",
        "Ilinca Pop","Bogdan Costache","Andreea Nistor","Radu Matei",
        "Camelia Sava","Ionut Moldovan","Sorina Neagu","Costin Pavel",
        "Oana Cernat","Sebastian Udrea","Bianca Sima"
    };

    std::vector<std::unique_ptr<Patient>> allPatients;
    allPatients.reserve(patientNames.size());
    size_t patCount = 0;
    std::vector<std::string> diseases(knownDiseases.begin(), knownDiseases.end());

    for (size_t i = 0; i < doctorInfo.size(); ++i) {
        auto doc = std::make_unique<Doctor>(doctorInfo[i].first,
                                            doctorInfo[i].second);
        int numP = 2 + (i % 2);
        for (int j = 0; j < numP && patCount < patientNames.size(); ++j) {
            bool male  = (patCount % 2 == 0);
            int  year  = 1980 + (patCount % 30);
            int  month = 1 + (patCount % 12);
            int  day   = 1 + (patCount % 28);
            auto cnp   = generateCNP(male, year, month, day, patCount);
            double funds = 1000 + patCount * 50;

            auto pat = std::make_unique<Patient>(
                patientNames[patCount],
                30 + (patCount % 10),
                male ? 'M' : 'F',
                cnp,
                funds
            );

            std::string d = diseases[(i + j) % diseases.size()];
            if (Patient::isValidDisease(d)) {
                pat->addDisease(d, 200.0 + j * 50);
            }

            doc->assignPatient(pat.get());
            allPatients.push_back(std::move(pat));
            ++patCount;
        }
        hospital->addDoctor(std::move(doc));
    }

    for (const auto& dptr : hospital->getDoctors()) {
        if (!dptr->getPatientList().empty()) {
            hospital->scheduleAppointment(
                dptr->getName(),
                dptr->getPatientList()[0],
                "2025-06-01",
                "09:00"
            );
        }
    }



    while (true) {
        std::cout << "\n\n";
        std::cout << "=== Spitalul Municipal Bucuresti ===\n"
                  << "1) Hospital Info\n"
                  << "2) Doctors\n"
                  << "3) Patients\n"
                  << "4) Appointments\n"
                  << "5) Analytics\n"
                  << "0) Exit\n"
                  << "Select: ";

        int mainOpt;
        if (!(std::cin >> mainOpt)) break;
        clearInput();

        if (mainOpt == 0) {
            std::cout << "Goodbye!\n";
            break;
        }

        switch (mainOpt) {
        case 1:
            std::cout << "\n";
            hospital->printInfo();
            waitForEnter();
            break;

        case 2: {
            int opt;
            while (true) {
                std::cout << "\n\n";
                std::cout << "--- Doctors ---\n"
                          << "1) List all\n"
                          << "2) View a doctor's patients\n"
                          << "3) Add new doctor\n"
                          << "4) Assign existing patient\n"
                          << "0) Back\n"
                          << "Choice: ";
                if (!(std::cin >> opt)) break;
                clearInput();
                if (opt == 0) break;

                switch (opt) {
                case 1:
                    std::cout << "\n";
                    hospital->printDoctors();
                    waitForEnter();
                    break;
                case 2: {
                    std::cout << "\nDoctor name: ";
                    std::string dn; std::getline(std::cin, dn);
                    bool found = false;
                    for (const auto& dptr : hospital->getDoctors()) {
                        if (dptr->getName() == dn) {
                            std::cout << "\n";
                            dptr->printPatients();
                            found = true;
                        }
                    }
                    if (!found) std::cout << "[Error] Doctor not found.\n";
                    waitForEnter();
                } break;
                case 3: {
                    std::cout << "\nNew doctor name: ";
                    std::string dn; std::getline(std::cin, dn);
                    std::cout << "Specialty: ";
                    std::string sp; std::getline(std::cin, sp);
                    if (Doctor::isValidSpecialty(sp)) {
                        hospital->addDoctor(
                          std::make_unique<Doctor>(dn, sp)
                        );
                        std::cout << "Doctor added.\n";
                    } else {
                        std::cout << "[Error] Invalid specialty.\n";
                    }
                    waitForEnter();
                } break;
                case 4: {
                    std::cout << "\nPatient name: ";
                    std::string pn; std::getline(std::cin, pn);
                    Patient* p = findPatientByName(allPatients, pn);
                    if (!p) {
                        std::cout << "[Error] Patient not found.\n";
                    } else {
                        std::cout << "Doctor name: ";
                        std::string dn; std::getline(std::cin, dn);
                        hospital->addPatientToDoctor(dn, p);
                    }
                    waitForEnter();
                } break;
                default:
                    std::cout << "[Error] Invalid choice.\n";
                    waitForEnter();
                }
            }
        } break;

        case 3: {
            int opt;
            while (true) {
                std::cout << "\n\n";
                std::cout << "--- Patients ---\n"
                          << "1) List all\n"
                          << "2) View details\n"
                          << "3) Register new\n"
                          << "4) Add funds\n"
                          << "5) Add disease manually\n"
                          << "6) Remove disease\n"
                          << "0) Back\n"
                          << "Choice: ";
                if (!(std::cin >> opt)) break;
                clearInput();
                if (opt == 0) break;

                switch (opt) {
                case 1:
                    std::cout << "\n";
                    for (const auto& p : allPatients) {
                        p->printInfo();
                        std::cout << "\n";
                    }
                    waitForEnter();
                    break;
                case 2: {
                    std::cout << "\nPatient name: ";
                    std::string pn; std::getline(std::cin, pn);
                    Patient* p = findPatientByName(allPatients, pn);
                    if (p) {
                        std::cout << "\n";
                        p->printInfo();
                        std::cout << "Total cost: $" << p->getTotalTreatmentCost() << "\n";
                    } else {
                        std::cout << "[Error] Patient not found.\n";
                    }
                    waitForEnter();
                } break;
                case 3: {
                    std::cout << "\n=== New Patient ===\nName: ";
                    std::string nm; std::getline(std::cin, nm);
                    if (!Patient::isValidName(nm)) {
                        std::cout << "[Error] Invalid name.\n";
                        waitForEnter();
                        break;
                    }
                    std::cout << "CNP: ";
                    std::string c; std::getline(std::cin, c);
                    if (!Patient::isValidCNP(c)) {
                        std::cout << "[Error] Invalid CNP.\n";
                        waitForEnter();
                        break;
                    }
                    std::cout << "Age: ";
                    int age; std::cin >> age; clearInput();
                    std::cout << "Gender (M/F): ";
                    char g; std::cin >> g; clearInput();

                    auto newP = std::make_unique<Patient>(nm, age, g, c, 0.0);
                    runHealthQuiz(newP.get(), hospital.get());
                    allPatients.push_back(std::move(newP));
                    std::cout << "Patient registered.\n";
                    waitForEnter();
                } break;
                case 4: {
                    std::cout << "\nPatient name: ";
                    std::string pn; std::getline(std::cin, pn);
                    Patient* p = findPatientByName(allPatients, pn);
                    if (p) {
                        std::cout << "Amount: $";
                        double amt; std::cin >> amt; clearInput();
                        p->addFunds(amt);
                        std::cout << "\nNew balance: $" << p->getFunds() << "\n";
                    } else {
                        std::cout << "[Error] Patient not found.\n";
                    }
                    waitForEnter();
                } break;
                case 5: {
                    std::cout << "\nPatient name: ";
                    std::string pn; std::getline(std::cin, pn);
                    Patient* p = findPatientByName(allPatients, pn);
                    if (p) {
                        std::cout << "Disease: ";
                        std::string d; std::getline(std::cin, d);
                        if (Patient::isValidDisease(d)) {
                            std::cout << "Cost: $";
                            double cost; std::cin >> cost; clearInput();
                            p->addDisease(d, cost);
                            std::cout << "Disease added.\n";
                        } else {
                            std::cout << "[Error] Unknown disease.\n";
                        }
                    } else {
                        std::cout << "[Error] Patient not found.\n";
                    }
                    waitForEnter();
                } break;
                case 6: {
                    std::cout << "\nPatient name: ";
                    std::string pn; std::getline(std::cin, pn);
                    Patient* p = findPatientByName(allPatients, pn);
                    if (p) {
                        std::cout << "Disease to remove: ";
                        std::string d; std::getline(std::cin, d);
                        p->removeDisease(d);
                        std::cout << "Removed if present.\n";
                    } else {
                        std::cout << "[Error] Patient not found.\n";
                    }
                    waitForEnter();
                } break;
                default:
                    std::cout << "[Error] Invalid choice.\n";
                    waitForEnter();
                }
            }
        } break;

        case 4: {
            int opt;
            while (true) {
                std::cout << "\n\n";
                std::cout << "--- Appointments ---\n"
                          << "1) List all\n"
                          << "2) Schedule\n"
                          << "3) Discharge & recheck\n"
                          << "0) Back\n"
                          << "Choice: ";
                if (!(std::cin >> opt)) break;
                clearInput();
                if (opt == 0) break;

                switch (opt) {
                case 1:
                    std::cout << "\n";
                    hospital->printAppointments();
                    waitForEnter();
                    break;
                case 2: {
                    std::cout << "\nDoctor: ";
                    std::string dn; std::getline(std::cin, dn);
                    std::cout << "Patient: ";
                    std::string pn; std::getline(std::cin, pn);
                    std::cout << "Date (YYYY-MM-DD): ";
                    std::string dt; std::getline(std::cin, dt);
                    std::cout << "Time (HH:MM): ";
                    std::string tm; std::getline(std::cin, tm);
                    Patient* p = findPatientByName(allPatients, pn);
                    if (p) {
                        hospital->scheduleAppointment(dn, p, dt, tm);
                    } else {
                        std::cout << "[Error] Patient not found.\n";
                    }
                    waitForEnter();
                } break;
                case 3: {
                    std::cout << "\nDoctor: ";
                    std::string dn; std::getline(std::cin, dn);
                    std::cout << "Patient: ";
                    std::string pn; std::getline(std::cin, pn);
                    Patient* p = findPatientByName(allPatients, pn);
                    Doctor* docPtr = nullptr;
                    for (const auto& dptr : hospital->getDoctors()) {
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
                        std::cout << "[Error] Doctor or patient not found.\n";
                    }
                    waitForEnter();
                } break;
                default:
                    std::cout << "[Error] Invalid choice.\n";
                    waitForEnter();
                }
            }
        } break;

        case 5: {
            int opt;
            while (true) {
                std::cout << "\n\n";
                std::cout << "--- Analytics ---\n"
                          << "1) Total profit\n"
                          << "2) Most common diseases\n"
                          << "0) Back\n"
                          << "Choice: ";
                if (!(std::cin >> opt)) break;
                clearInput();
                if (opt == 0) break;

                switch (opt) {
                case 1:
                    std::cout << "\nHospital profit: $" << hospital->getProfit() << "\n";
                    waitForEnter();
                    break;
                case 2: {
                    std::cout << "\nTop diseases:\n";
                    for (auto const& pr : hospital->getMostCommonDiseases()) {
                        std::cout << " - " << pr.first
                                  << " (" << pr.second << " cases)\n";
                    }
                    waitForEnter();
                } break;
                default:
                    std::cout << "[Error] Invalid choice.\n";
                    waitForEnter();
                }
            }
        } break;

        default:
            std::cout << "[Error] Invalid choice.\n";
            waitForEnter();
        }
    }

    return 0;
}
