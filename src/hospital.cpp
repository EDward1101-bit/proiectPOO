#include "../includes/hospital.h"
#include "../includes/doctor.h"
#include "../includes/appointment.h"
#include "../includes/patient.h"
#include "../includes/Consultatie.h"
#include "../includes/TratamentSpecializat.h"
#include "../includes/InterventieChirurgicala.h"
#include "../includes/Internare.h"
#include <algorithm>
#include <fstream>
#include <string>
#include <random>

Hospital::Hospital(const std::string& name) : name(name) {}

Hospital::Hospital(const Hospital& other)
    : name(other.name) {
    for (const auto& doctor : other.doctors) {
        doctors.push_back(std::make_unique<Doctor>(*doctor));
    }
    for (const auto& appointment : other.appointments) {
        appointments.push_back(std::make_unique<Appointment>(*appointment));
    }
}

Hospital& Hospital::operator=(const Hospital& other) {
    if (this != &other) {
        name = other.name;
        doctors.clear();
        appointments.clear();
        for (const auto& doctor : other.doctors) {
            doctors.push_back(std::make_unique<Doctor>(*doctor));
        }
        for (const auto& appointment : other.appointments) {
            appointments.push_back(std::make_unique<Appointment>(*appointment));
        }
    }
    return *this;
}

Hospital::~Hospital() {}

const std::string& Hospital::getName() const { return name; }
const std::vector<std::unique_ptr<Doctor>>& Hospital::getDoctors() const { return doctors; }

void Hospital::addDoctor(std::unique_ptr<Doctor> doctor) {
    doctors.push_back(std::move(doctor));
}

void Hospital::addAppointment(std::unique_ptr<Appointment> appointment) {
    appointments.push_back(std::move(appointment));
}

Doctor* Hospital::findDoctorByName(const std::string& doctorName) const {
    for (const auto& doctor : doctors) {
        if (doctor && doctor->getName() == doctorName) {
            return doctor.get();
        }
    }
    return nullptr;
}


void Hospital::listAllDoctors() const {
    for (const auto& doctor : doctors) {
        if (doctor) {
            std::cout << *doctor << "\n";
        }
    }
}

void Hospital::listAllAppointments() const {
    std::vector<const Appointment*> sortedAppointments;
    for (const auto& appt : appointments) {
        sortedAppointments.push_back(appt.get());
    }

    std::sort(sortedAppointments.begin(), sortedAppointments.end(), [](const Appointment* a, const Appointment* b) {
        return a->getDate() < b->getDate() || (a->getDate() == b->getDate() && a->getTime() < b->getTime());
    });

    for (const auto& appt : sortedAppointments) {
        if (appt) {
            std::cout << *appt << "\n";
        }
    }
}

bool Hospital::isDoctorAvailable(const Doctor* doctor, const std::string& date, const std::string& time) const {
    for (const auto& appointment : appointments) {
        if (appointment && appointment->getDoctor() == doctor) {
            if (appointment->getDate() == date && appointment->getTime() == time) {
                return false;
            }
        }
    }
    return true; // Doctorul e liber
}

void Hospital::saveAppointmentsToCSV(const std::string& filename) const {
    std::ofstream fout(filename, std::ios::trunc); // suprascrie fisierul
    if (!fout.is_open()) {
        std::cerr << "Error opening appointments file for writing.\n";
        return;
    }

    for (const auto& appointment : appointments) {
        if (appointment) {
            fout << appointment->getDoctor()->getName() << ","
                 << appointment->getPatient()->getName() << ","
                 << appointment->getDate() << ","
                 << appointment->getTime() << "\n";
        }
    }
    fout.close();
}


void Hospital::proceseazaProgramare(Appointment& programare,
                                    const std::map<std::string, std::string>& diseaseToSpecialty) {


    if (programare.isProcesata()) {
        std::cout << "Programarea a fost deja procesată.\n";
        return;
    }

    Doctor* doctor = programare.getDoctor();
    Patient* pacient = programare.getPatient();

    if (!doctor || !pacient) {
        std::cout << "Programare invalidă: doctor sau pacient lipsă.\n";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> boolDist(0, 1);
    bool esteBolnav = boolDist(gen);  // 50% șansă

    if (!esteBolnav) {
        std::cout << pacient->getName() << " este sănătos.\n";
        pacient->setHealthy(true);
        pacient->setExternat(true);

        auto consult = std::make_shared<Consultatie>(
            programare.getDate(), programare.getTime(), doctor, pacient, 0.0);
        pacient->adaugaServiciu(consult);
    } else {
        std::vector<std::string> boli;
        for (const auto& pair : diseaseToSpecialty)
            boli.push_back(pair.first);

        if (boli.empty()) {
            std::cout << "Nu există boli definite în sistem.\n";
            return;
        }

        std::uniform_int_distribution<> boalaDist(0, boli.size() - 1);
        std::string boala = boli[boalaDist(gen)];
        std::string specialitateNecesara = diseaseToSpecialty.at(boala);

        if (doctor->getSpecialty() != specialitateNecesara) {
            std::cout << "Doctorul nu este specializat pentru boala aleasă: " << boala << "\n";
            return;
        }

        std::cout << pacient->getName() << " a fost diagnosticat cu " << boala << "\n";
        pacient->addDisease(boala);

        std::uniform_real_distribution<> costDist(200.0, 500.0);
        double cost = costDist(gen);

        if (boala == "fractură") {
            // Intervenție specială pentru fractură
            std::uniform_int_distribution<> durataDist(1, 4); // între 1–4 ore
            int durata = durataDist(gen);
            auto interventie = std::make_shared<InterventieChirurgicala>(
                programare.getDate(), programare.getTime(), doctor, pacient, "Operație fractură", durata);
            pacient->adaugaServiciu(interventie);
        } else {
            auto tratament = std::make_shared<TratamentSpecializat>(
                programare.getDate(), programare.getTime(), doctor, pacient, boala, cost);
            pacient->adaugaServiciu(tratament);
        }

    }

    programare.seteazaProcesata();
    std::cout << "Programarea a fost procesată.\n";
}

void Hospital::proceseazaToateProgramarile(const std::map<std::string, std::string>& diseaseToSpecialty) {
    for (auto& appointment : appointments) {
        if (!appointment->isProcesata()) {
            std::cout << "\n> Procesare programare: "
                      << appointment->getPatient()->getName()
                      << " cu Dr. " << appointment->getDoctor()->getName()
                      << " la " << appointment->getDate() << " " << appointment->getTime() << "\n";
            proceseazaProgramare(*appointment, diseaseToSpecialty);
        }
    }
}

void Hospital::genereazaFactura(Patient& pacient) const {
    if (pacient.getIstoric().empty()) {
        std::cout << "Fișa pacientului este goală. Nu există servicii.\n";
        return;
    }

    std::cout << "\n===== FACTURĂ PACIENT =====\n";
    std::cout << "Nume: " << pacient.getName() << "\n";
    std::cout << "CNP: " << pacient.getCNP() << "\n";
    std::cout << "------------------------------\n";

    double total = 0;
    for (const auto& serviciu : pacient.getIstoric()) {
        serviciu->print(std::cout);
        double cost = serviciu->getCost();
        std::cout << " → Cost: " << cost << " RON\n";
        total += cost;
    }

    std::cout << "------------------------------\n";
    std::cout << "TOTAL DE PLATĂ: " << total << " RON\n";
    std::cout << "==============================\n";

    if (!pacient.getExternat()) {
        std::cout << "Pacientul a fost acum marcat ca externat.\n";
        const_cast<Patient&>(pacient).setExternat(true);
    }
}

void Hospital::savePatientsToCSV(const std::vector<std::unique_ptr<Patient>>& patients, const std::string& filename) {
    std::ofstream fout(filename, std::ios::trunc); // ștergem și rescriem

    if (!fout.is_open()) {
        std::cerr << "Error opening patients file for writing.\n";
        return;
    }

    for (const auto& patientPtr : patients) {
        if (patientPtr) {
            fout << patientPtr->getName() << ","
                 << patientPtr->getCNP() << ","
                 << patientPtr->getAge() << ","
                 << patientPtr->getGender() << ",";

            if (!patientPtr->getDiseases().empty()) {
                auto it = patientPtr->getDiseases().begin();
                fout << *it;
                ++it;
                for (; it != patientPtr->getDiseases().end(); ++it) {
                    fout << "|" << *it;
                }
            } else {
                fout << "Healthy";
            }

            fout << "\n";
        }
    }
    fout.close();
}

std::ostream& operator<<(std::ostream& os, const Hospital& hospital) {
    os << "Hospital Name: " << hospital.name;
    return os;
}
