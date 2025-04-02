#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "doctor.h"


class Spital {
private:
    std::string name;
    std::vector<Doctor*> doctors;
public:
    explicit Spital(std::string name);



};


#endif // HOSPITAL_H