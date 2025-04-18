#include <iostream>
#include <string>
#include "../includes/appointment.h"
#include "../includes/doctor.h"
#include "../includes/hospital.h"
#include "../includes/patient.h"
#include <memory>

int main() {
    // Step 1: Create a Hospital
    Hospital hospital("City Hospital", "Downtown");

    // Step 2: Create Doctors
    std::unique_ptr<Doctor> drSmith = std::make_unique<Doctor>("Dr. Smith", "Cardiology");
    std::unique_ptr<Doctor> drJohnson = std::make_unique<Doctor>("Dr. Johnson", "Neurology");

    // Add doctors to the hospital
    hospital.addDoctor(drSmith.get());
    hospital.addDoctor(drJohnson.get());

    // Step 3: Create Patients
    std::unique_ptr<Patient> patient1 = std::make_unique<Patient>("Alice", 30, 'F', "Heart Disease");
    std::unique_ptr<Patient> patient2 = std::make_unique<Patient>("Bob", 45, 'M', "Brain Tumor");

    // Step 4: Assign patients to doctors
    drSmith->assignPatient(patient1.get());
    drJohnson->assignPatient(patient2.get());

    // Step 5: Create Appointments
    std::unique_ptr<Appointment> app1 = std::make_unique<Appointment>("2025-04-20", "10:00", drSmith.get());
    std::unique_ptr<Appointment> app2 = std::make_unique<Appointment>("2025-04-20", "11:00", drSmith.get());
    std::unique_ptr<Appointment> app3 = std::make_unique<Appointment>("2025-04-21", "10:00", drJohnson.get());

    // Add appointments to the hospital
    hospital.addAppointment(app1.get());
    hospital.addAppointment(app2.get());
    hospital.addAppointment(app3.get());

    // Step 6: Use the functions to make sure they aren't unused

    // Test scheduleAppointment function from Hospital
    std::string appointmentDate = "2025-04-22";
    std::string appointmentTime = "14:00";
    if (app1->isValidDateTime(appointmentDate, appointmentTime)) {
        hospital.scheduleAppointment("Dr. Smith", patient1.get(), appointmentDate, appointmentTime);
        std::cout << "Appointment scheduled for " << patient1->getName() << " with Dr. Smith at " << appointmentDate << " " << appointmentTime << std::endl;
    } else {
        std::cout << "Invalid date or time!" << std::endl;
    }

    // Test the isDoctorAvailable function from Hospital
    std::cout << "Checking doctor availability:" << std::endl;
    std::cout << "Is Dr. Smith available on 2025-04-20 at 10:00? ";
    if (hospital.isDoctorAvailable("Dr. Smith", "2025-04-20", "10:00")) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    // Test removePatient function from Doctor (remove Alice from Dr. Smith)
    drSmith->removePatient(patient1.get());

    // Test getDoctor function from Appointment (get doctor for the first appointment)
    std::cout << "Doctor for the first appointment: " << app1->getDoctor()->getName() << "\n";

    // Test getDisease and updateDisease from Patient
    std::cout << "\nPatient information before update:" << std::endl;
    std::cout << "Patient: " << patient1->getName() << ", Disease: " << patient1->getDisease() << std::endl;

    // Update patient's disease
    patient1->updateDisease("Cardiac Arrhythmia");

    std::cout << "Patient: " << patient1->getName() << ", Updated Disease: " << patient1->getDisease() << std::endl;

    // Use addPatientToDoctor to assign a patient to Dr. Smith
    hospital.addPatientToDoctor("Dr. Smith", patient1.get());

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

    return 0;
}
