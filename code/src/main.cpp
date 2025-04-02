#include <iostream>
#include "../includes/doctor.h"
#include "../includes/patient.h"

int main() {
    // Create doctors
    Doctor doc1("Dr. Smith", "Cardiology");
    Doctor doc2("Dr. Johnson", "Neurology");
    Doctor doc3("Dr. Brown", "Pediatrics");

    // Create patients
    Patient p1("John Doe", 45, 'M', "Heart Disease");
    Patient p2("Jane Doe", 30, 'F', "Migraine");
    Patient p3("Alice Brown", 25, 'F', "Asthma");

    // Assign patients to doctors
    doc1.assignPatient(&p1);
    doc1.assignPatient(&p2);

    doc2.assignPatient(&p3);

    // Print doctor info and patients
    doc1.printInfo();
    doc1.printPatients();

    doc2.printInfo();
    doc2.printPatients();

    // Update disease for a patient
    p1.updateDisease("Recovered");
    p1.printInfo();

    // Remove a patient from a doctor
    doc1.removePatient(&p1);
    doc1.printPatients();

    return 0;
}
