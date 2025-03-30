#include <iostream>
#include "../includes/doctor.h"
#include "../includes/patient.h"

int main() {
    // Create doctors
    Doctor doc1("Dr. Smith", "Cardiology");
    Doctor doc2("Dr. Johnson", "Neurology");
    Doctor doc3("Dr. Brown", "Pediatrics");

    // Create a patient
    Patient p1("John Doe", 45, 'M', "Heart Disease");

    // Assign doctors to the patient
    p1.assignDoctor(&doc1);
    p1.assignDoctor(&doc2);

    // Print patient info and doctors assigned to the patient
    p1.printInfo();
    p1.printDoctors();

    // Update disease and reassign doctors
    p1.updateDisease("Recovered");
    p1.printInfo();

    // Remove a doctor from the patient
    p1.removeDoctor(&doc1);
    p1.printDoctors();

    return 0;
}
