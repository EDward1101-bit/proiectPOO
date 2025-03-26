#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>

class Doctor;

class Patient {
private:
  std::string name;
  int age;
  char gender;
  std::string disease;
  Doctor* doctor; // Composition: a Patient has a Doctor

public:
  // Constructor
  explicit Patient(std::string name, int age, char gender, std::string disease, Doctor* doctor = nullptr);

  Patient(const Patient& other);            // Copy Constructor
  Patient& operator=(const Patient& other); // Copy Assignment Operator
  ~Patient();                               // Destructor

  // Public member functions
  void updateDisease(const std::string& newDisease);
  void assignDoctor(Doctor* doc);
  void printInfo() const;

  // Operator<< Overload
  friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

#endif //PATIENT_H
