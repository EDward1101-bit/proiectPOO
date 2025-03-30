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
  std::vector<Doctor*> doctors;  // Multiple doctors can be assigned

public:
  // Constructor
  Patient(std::string name, int age, char gender, std::string disease);

  // Copy Constructor
  Patient(const Patient& other);

  // Copy Assignment Operator
  Patient& operator=(const Patient& other);

  // Destructor
  ~Patient();

  // Public member functions
  void updateDisease(const std::string& newDisease);
  void assignDoctor(Doctor* doc);
  void removeDoctor(Doctor* doc);
  void printInfo() const;
  void printDoctors() const;

  // Operator<< Overload
  friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif // PATIENT_H
