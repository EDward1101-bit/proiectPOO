#include "../includes/appointment_builder.h"

AppointmentBuilder::AppointmentBuilder()
    : doctor(nullptr), patient(nullptr), hasDoctor(false),
      hasPatient(false), hasDate(false), hasTime(false) {}

AppointmentBuilder& AppointmentBuilder::setDoctor(Doctor* d) {
    if (!d) throw InvalidInputException("Doctor null.");
    doctor = d;
    hasDoctor = true;
    return *this;
}

AppointmentBuilder& AppointmentBuilder::setPatient(Patient* p) {
    if (!p) throw InvalidInputException("Patient null.");
    patient = p;
    hasPatient = true;
    return *this;
}

AppointmentBuilder& AppointmentBuilder::setDate(const std::string& d) {
    if (d.empty()) throw InvalidInputException("Data nu poate fi goală.");
    date = d;
    hasDate = true;
    return *this;
}

AppointmentBuilder& AppointmentBuilder::setTime(const std::string& t) {
    if (t.empty()) throw InvalidInputException("Ora nu poate fi goală.");
    time = t;
    hasTime = true;
    return *this;
}

Appointment AppointmentBuilder::build() const {
    if (!hasDoctor) throw SpitalException("Doctorul nu a fost setat.");
    if (!hasPatient) throw SpitalException("Pacientul nu a fost setat.");
    if (!hasDate) throw SpitalException("Data nu a fost setată.");
    if (!hasTime) throw SpitalException("Ora nu a fost setată.");

    Appointment appt(date, time, doctor, patient);

    if (!appt.isValidDateTime()) {
        throw InvalidInputException("Format dată/oră invalid (corect: YYYY-MM-DD HH:MM)");
    }
    if (!appt.isInFuture()) {
        throw InvalidInputException("Programarea nu este validă: trebuie să fie în viitor, în intervalul orar și zile lucrătoare.");
    }

    return appt;
}
