#ifndef APPOINTMENT_BUILDER_H
#define APPOINTMENT_BUILDER_H

#include "appointment.h"
#include "doctor.h"
#include "patient.h"
#include "spital_exception.h"
#include <string>

class AppointmentBuilder {
private:
    Doctor* doctor;
    Patient* patient;
    std::string date;
    std::string time;
    bool hasDoctor, hasPatient, hasDate, hasTime;

public:
    AppointmentBuilder();

    AppointmentBuilder& setDoctor(Doctor* d);
    AppointmentBuilder& setPatient(Patient* p);
    AppointmentBuilder& setDate(const std::string& d);
    AppointmentBuilder& setTime(const std::string& t);

    Appointment build() const;
};

#endif // APPOINTMENT_BUILDER_H
