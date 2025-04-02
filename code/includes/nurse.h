
#ifndef NURSE_H
#define NURSE_H
#include <string>

class Nurse {
private:
    std::string name;
    std::string speciality;
    int age;
    int yearsWorked;

public:
    explicit Nurse(std::string name, std::string speciality, int age, int yearsWorked);

};

#endif //NURSE_H
