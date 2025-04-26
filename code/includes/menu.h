#ifndef MENU_H
#define MENU_H

#include <vector>
#include <memory>

class Hospital;
class Patient;

class Menu {
private:
    Hospital& hospital;
    std::vector<std::unique_ptr<Patient>>& patients;

    void doctorsMenu();
    void patientsMenu();
    void appointmentsMenu();

public:
    Menu(Hospital& hospital, std::vector<std::unique_ptr<Patient>>& patients);

    void showMainMenu();
};

#endif // MENU_H