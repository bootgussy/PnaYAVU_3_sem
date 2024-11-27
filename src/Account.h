#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "sqlite3.h"

class Account
{
private:
    std::string login;
    std::string password;
    int points;
    std::string role;

public:
    Account(const std::string& accountLogin, const std::string& accountPassword, int accountPoints = 0, const std::string& accountRole = "");
    Account();

    std::string getLogin() const;
    std::string getPassword() const;
    int getPoints() const;
    std::string getRole() const;
    std::shared_ptr<Account> signIn(std::string& login, std::string& password);
    std::shared_ptr<Account> logIn(std::string& login, std::string& password);

    friend void operator+=(Account& account, int addedPoints);
    friend void operator-=(Account& account, int usedPoints);
    bool operator!=(const Account& right) const;
};
