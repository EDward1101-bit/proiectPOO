#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>
#include <vector>
#include "doctor.h"

class Patient {
private:
  std::string name;
  int age;
  char gender;
  std::string disease;
  std::vector<Doctor*> doctors;  // A patient can have multiple doctors

public:
  // Constructor
  Patient(std::string name, int age, char gender, std::string disease);

  Patient(const Patient& other);

  Patient& operator=(const Patient& other);
  ~Patient();

  void updateDisease(const std::string& newDisease);
  void assignDoctor(Doctor* doc);
  void removeDoctor(Doctor* doc);
  void printInfo() const;
  void printDoctors() const;

  friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif // PATIENT_H
