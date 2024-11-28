#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "sqlite3.h"

class Account
{
private:
    std::string accountLogin;
    std::string accountPassword;
    int accountPoints;
    std::string accountRole;

public:
    Account(const std::string& login, const std::string& password, int points = 0, const std::string& role = "");
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
