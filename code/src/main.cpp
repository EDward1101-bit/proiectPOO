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

    // Assign patients to doctors
    drSmith->assignPatient(patient1);
    drJohnson->assignPatient(patient2);

    // Step 4: Create Appointments
    Appointment* app1 = new Appointment("2025-04-20", "10:00", drSmith);
    Appointment* app2 = new Appointment("2025-04-20", "11:00", drSmith);
    Appointment* app3 = new Appointment("2025-04-21", "10:00", drJohnson);

    // Add appointments to the hospital
    hospital.addAppointment(app1);
    hospital.addAppointment(app2);
    hospital.addAppointment(app3);

    // Step 5: Test Doctor Availability
    std::cout << "Checking Doctor Availability:" << std::endl;
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

    std::cout << "\nDoctors and Patients:" << std::endl;
    drSmith->printInfo();
    drSmith->printPatients();

    drJohnson->printInfo();
    drJohnson->printPatients();

    std::cout << "\nAppointments:" << std::endl;
    hospital.printAppointments();

    delete drSmith;
    delete drJohnson;
    delete patient1;
    delete patient2;
    delete app1;
    delete app2;
    delete app3;

    return 0;
}
