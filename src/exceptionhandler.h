#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <exception>
#include <string>

class ExceptionHandler : public std::exception {
public:
    explicit ExceptionHandler(const std::string& message)
        : message(message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

#endif // EXCEPTIONHANDLER_H
