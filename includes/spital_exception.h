#ifndef SPITAL_EXCEPTION_H
#define SPITAL_EXCEPTION_H

#include <exception>
#include <string>

class SpitalException : public std::exception {
protected:
    std::string message;
public:
    explicit SpitalException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidCNPException : public SpitalException {
public:
    InvalidCNPException() : SpitalException("CNP invalid.") {}
};

class InsufficientBudgetException : public SpitalException {
public:
    InsufficientBudgetException(double price)
        : SpitalException("Buget insuficient pentru achizitia itemului (pret: " + std::to_string(price) + ")") {}
};

class AppointmentConflictException : public SpitalException {
public:
    AppointmentConflictException()
        : SpitalException("Doctorul are deja o programare la acea ora.") {}
};

#endif // SPITAL_EXCEPTION_H
