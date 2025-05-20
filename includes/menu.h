#ifndef MENU_H
#define MENU_H

#include <vector>
#include <memory>
#include <map>
#include <string>

class Hospital;
class Patient;

class Menu {
private:
    Hospital& hospital;
    std::vector<std::unique_ptr<Patient>>& patients;
    const std::map<std::string, std::string>& diseaseToSpecialty;

    void doctorsMenu();
    void patientsMenu();
    void appointmentsMenu();

public:
    Menu(Hospital& hospital, std::vector<std::unique_ptr<Patient>>& patients,
         const std::map<std::string, std::string>& diseaseToSpecialty);

    void showMainMenu();
};

#endif // MENU_H
