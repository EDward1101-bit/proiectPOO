#include <iostream>
#include <string>
#include "../includes/appointment.h"
#include "../includes/doctor.h"
#include "../includes/hospital.h"
#include "../includes/patient.h"

int main() {
    // Step 1: Create a Hospital
    Hospital hospital("City Hospital", "Downtown");

    // Step 2: Create Doctors
    Doctor* drSmith = new Doctor("Dr. Smith", "Cardiology");
    Doctor* drJohnson = new Doctor("Dr. Johnson", "Neurology");

    // Add doctors to the hospital
    hospital.addDoctor(drSmith);
    hospital.addDoctor(drJohnson);

    // Step 3: Create Patients
    Patient* patient1 = new Patient("Alice", 30, 'F', "Heart Disease");
    Patient* patient2 = new Patient("Bob", 45, 'M', "Brain Tumor");

    // Step 4: Assign patients to doctors
    drSmith->assignPatient(patient1);
    drJohnson->assignPatient(patient2);

    // Step 5: Create Appointments
    Appointment* app1 = new Appointment("2025-04-20", "10:00", drSmith);
    Appointment* app2 = new Appointment("2025-04-20", "11:00", drSmith);
    Appointment* app3 = new Appointment("2025-04-21", "10:00", drJohnson);

    // Add appointments to the hospital
    hospital.addAppointment(app1);
    hospital.addAppointment(app2);
    hospital.addAppointment(app3);

    // Step 6: Use the unused functions to prevent warnings
    std::cout << "Checking doctor availability:" << std::endl;
    std::cout << "Is Dr. Smith available on 2025-04-20 at 10:00? ";
    if (app1->isDoctorAvailable("2025-04-20", "10:00")) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    std::cout << "Is Dr. Smith available on 2025-04-20 at 11:00? ";
    if (app2->isDoctorAvailable("2025-04-20", "11:00")) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    std::cout << "Is Dr. Johnson available on 2025-04-21 at 10:00? ";
    if (app3->isDoctorAvailable("2025-04-21", "10:00")) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    // Use getDisease and updateDisease functions
    std::cout << "\nPatient information before update:" << std::endl;
    std::cout << "Patient: " << patient1->getName() << ", Disease: " << patient1->getDisease() << std::endl;

    // Update patient's disease
    patient1->updateDisease("Cardiac Arrhythmia");

    std::cout << "Patient: " << patient1->getName() << ", Updated Disease: " << patient1->getDisease() << std::endl;

    // Print doctor information and their patients
    std::cout << "\nDoctor Information:" << std::endl;
    drSmith->printInfo();
    drSmith->printPatients();

    drJohnson->printInfo();
    drJohnson->printPatients();

    // Use printDoctors function from Hospital
    std::cout << "\nDoctors in the hospital:" << std::endl;
    hospital.printDoctors();

    // Print appointments for the hospital
    std::cout << "\nAppointments in the hospital:" << std::endl;
    hospital.printAppointments();

    // Clean up dynamically allocated memory
    delete drSmith;
    delete drJohnson;
    delete patient1;
    delete patient2;
    delete app1;
    delete app2;
    delete app3;

    return 0;
}
