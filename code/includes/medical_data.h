#ifndef MEDICAL_DATA_H
#define MEDICAL_DATA_H

#include <map>
#include <string>
#include <unordered_set>

// Maps diseases to their corresponding required specialties
static const std::map<std::string, std::string> diseaseToSpecialty = {
    {"Heart Disease", "Cardiologist"},
    {"Diabetes", "Endocrinologist"},
    {"Brain Tumor", "Neurologist"},
    {"Asthma", "Pulmonologist"},
    {"Flu", "General Practitioner"},
    {"Skin Rash", "Dermatologist"},
    {"Broken Arm", "Orthopedist"},
    {"Allergy", "Allergist"},
    {"Hypertension", "Cardiologist"},
    {"Thyroid Disorder", "Endocrinologist"}
};

// Optional: List of all specialties for validation
static const std::unordered_set<std::string> knownSpecialties = {
    "Cardiologist", "Endocrinologist", "Neurologist",
    "Pulmonologist", "General Practitioner", "Dermatologist",
    "Orthopedist", "Allergist"
};

#endif // MEDICAL_DATA_H
