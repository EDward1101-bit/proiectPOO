#include <iostream>
#include "../includes/doctor.h"
#include "../includes/patient.h"
#include "../includes/hospital.h"

int main() {

    Hospital hospital("City Hospital", "New York");

    // Crearea doctorilor
    Doctor* doc1 = new Doctor("Dr. Smith", "Cardiology");
    Doctor* doc2 = new Doctor("Dr. Johnson", "Neurology");

    hospital.addDoctor(doc1);
    hospital.addDoctor(doc2);

    Patient p1("John Doe", 45, 'M', "Heart Disease");
    Patient p2("Jane Doe", 30, 'F', "Migraine");


    hospital.addPatientToDoctor("Dr. Smith", &p1);
    hospital.addPatientToDoctor("Dr. Johnson", &p2);


    hospital.printInfo();
    hospital.printDoctors();

    // Programare
    try {
        hospital.scheduleAppointment("Dr. Smith", &p1, "2025-04-20", "10:00");
        hospital.scheduleAppointment("Dr. Smith", &p2, "2025-04-20", "11:00");
        hospital.scheduleAppointment("Dr. Smith", &p1, "2025-04-20", "10:00");  // Aceasta ar trebui să dea eroare
        hospital.scheduleAppointment("Dr. Johnson", &p2, "2025-04-20", "12:00");
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Verificarea programărilor
    hospital.printAppointments();

    return 0;
}
