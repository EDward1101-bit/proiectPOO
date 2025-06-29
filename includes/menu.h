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


    Menu(Hospital& hospital, std::vector<std::unique_ptr<Patient>>& patients,
     const std::map<std::string, std::string>& diseaseToSpecialty);
public:

    static Menu& getInstance(Hospital& h, std::vector<std::unique_ptr<Patient>>& p, std::map<std::string, std::string>& d);
    void showMainMenu();

    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;
    Menu(Menu&&) = delete;
    Menu& operator=(Menu&&) = delete;
};

#endif // MENU_H
