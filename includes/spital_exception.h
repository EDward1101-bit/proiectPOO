#ifndef SPITAL_EXCEPTION_H
#define SPITAL_EXCEPTION_H

#include <exception>
#include <string>

class SpitalException : public std::exception {
protected:
    std::string msg;
public:
    explicit SpitalException(const std::string& msg) : msg(msg) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};


class FileOpenException : public SpitalException {
public:
    explicit FileOpenException(const std::string& filename)
        : SpitalException("Nu s-a putut deschide fișierul: " + filename) {}
};


class EntityNotFoundException : public SpitalException {
public:
    explicit EntityNotFoundException(const std::string& entityDesc)
        : SpitalException("Entitate negăsită: " + entityDesc) {}
};

class DuplicateEntityException : public SpitalException {
public:
    explicit DuplicateEntityException(const std::string& entityDesc)
        : SpitalException("Entitate duplicată: " + entityDesc) {}
};


class InvalidInputException : public SpitalException {
public:
    explicit InvalidInputException(const std::string& reason)
        : SpitalException("Input invalid: " + reason) {}
};


class InvalidAppointmentException : public SpitalException {
public:
    explicit InvalidAppointmentException(const std::string& reason)
        : SpitalException("Programare invalidă: " + reason) {}
};


class InsufficientBudgetException : public SpitalException {
public:
    explicit InsufficientBudgetException(double needed)
        : SpitalException("Buget insuficient. Necesar: " + std::to_string(needed)) {}
};

class LimitExceededException : public SpitalException {
public:
    explicit LimitExceededException(const std::string& item)
        : SpitalException("Limita atinsă pentru: " + item) {}
};

class InvalidCNPException : public SpitalException {
public:
    InvalidCNPException() : SpitalException("CNP invalid.") {}
};

class AppointmentConflictException : public SpitalException {
public:
    AppointmentConflictException() : SpitalException("Programare imposibilă: doctorul este deja ocupat la acea oră.") {}
};

#endif // SPITAL_EXCEPTION_H
