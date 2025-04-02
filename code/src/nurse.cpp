#include "../includes/nurse.h"

Nurse::Nurse(std::string name, std::string speciality, int age, int yearsWorked): name(std::move(name)), speciality(std::move(speciality)), age(age), yearsWorked(yearsWorked) {}


