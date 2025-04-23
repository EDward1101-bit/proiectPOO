#ifndef MEDICAL_DATA_H
#define MEDICAL_DATA_H

#include <map>
#include <string>
#include <unordered_set>

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
    {"Thyroid Disorder", "Endocrinologist"},
    {"Epilepsy", "Neurologist"},
    {"Pneumonia", "Pulmonologist"},
    {"Psoriasis", "Dermatologist"},
    {"Fractured Leg", "Orthopedist"},
    {"Hay Fever", "Allergist"},
    {"Cold", "General Practitioner"}
};

static const std::unordered_set<std::string> knownSpecialties = {
    "Cardiologist", "Endocrinologist", "Neurologist",
    "Pulmonologist", "General Practitioner", "Dermatologist",
    "Orthopedist", "Allergist"
};

static const std::unordered_set<std::string> knownDiseases = {
    "Heart Disease", "Diabetes", "Brain Tumor", "Asthma", "Flu",
    "Skin Rash", "Broken Arm", "Allergy", "Hypertension", "Thyroid Disorder",
    "Epilepsy", "Pneumonia", "Psoriasis", "Fractured Leg", "Hay Fever", "Cold"
};

#endif // MEDICAL_DATA_H