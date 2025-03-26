#include <iostream>
#include "../includes/patient.h"
#include "../includes/doctor.h"

int main() {
    // Create a doctor
    Doctor doc("Dr. Smith", "Cardiology");

    // Create a patient assigned to the doctor
    Patient p1("John Doe", 45, 'M', "Heart Disease", &doc);
    std::cout << p1 << std::endl;

    // Test public functions
    p1.updateDisease("Recovered");
    p1.printInfo();

    // Create another doctor and assign to patient
    Doctor doc2("Dr. Wilson", "Neurology");
    p1.assignDoctor(&doc2);

    // Test Doctor class functions
    doc2.changeSpecialty("General Medicine");
    std::cout << doc2 << std::endl;

    // Test Rule of Three
    Patient p2 = p1; // Copy constructor
    p2 = p1;         // Copy assignment

    return 0;
}
