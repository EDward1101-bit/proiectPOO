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

  // Copy Constructor
  Patient(const Patient& other);

  // Copy Assignment Operator
  Patient& operator=(const Patient& other);

  // Destructor
  ~Patient();

  // Public Methods
  void updateDisease(const std::string& newDisease);
  void assignDoctor(Doctor* doc);
  void removeDoctor(Doctor* doc);  // Remove a doctor
  void printInfo() const;
  void printDoctors() const;  // Print all assigned doctors

  // Operator<< Overload
  friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif // PATIENT_H
