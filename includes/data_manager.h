#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <string>
#include <vector>
#include <map>
#include <memory>

class Hospital;
class Patient;
class InventoryManager;
class InventoryItem;

class DataManager {
private:
    DataManager() = default;
public:
    static DataManager& getInstance();
    static void loadDoctors(Hospital& hospital, const std::string& filename);
    static void loadPatients(std::vector<std::unique_ptr<Patient>>& patients, const std::string& filename);
    static void loadAppointments(Hospital& hospital, const std::vector<std::unique_ptr<Patient>>& patients, const std::string& filename);
    static std::map<std::string, std::string> loadDiseaseSpecialty(const std::string& filename);

    static void loadInventory(const std::string& itemsFile, const std::string& budgetFile);
    static void saveInventory(const std::string& itemsFile, const std::string& budgetFile);

    static void saveHospital(const Hospital& hospital, const std::vector<std::unique_ptr<Patient>>& patients,
                             const std::string& appointmentsFile, const std::string& patientsFile);

    static void loadHospital(Hospital& hospital,
                         std::vector<std::unique_ptr<Patient>>& patients,
                         const std::string& doctorsFile,
                         const std::string& patientsFile,
                         const std::string& appointmentsFile);

    static void assignPatients(const Hospital& hospital,
                               std::vector<std::unique_ptr<Patient>>& patients,
                               const std::map<std::string, std::string>& diseaseToSpecialty);

};

#endif // DATA_MANAGER_H
