#include "Account.h"
#include "Database.h"
#include <cmath>

Account::Account(const std::string& login, const std::string& password, int points, const std::string& role)
    : accountLogin(login), accountPassword(password), accountPoints(points), accountRole(role) {}

Account::Account() = default;

std::string Account::getLogin() const
{
    return accountLogin;
}

std::string Account::getPassword() const
{
    return accountPassword;
}

int Account::getPoints() const
{
    return accountPoints;
}

std::string Account::getRole() const
{
    return accountRole;
}

std::shared_ptr<Account> Account::signIn(std::string& login, std::string& password)
{
    if (Account account = Database::getInstance()->getAccount(login, password);  account.getLogin() == login)
    {
        return std::make_shared<Account>(account);
    }

    return nullptr;
}

std::shared_ptr<Account> Account::logIn(std::string& login, std::string& password)
{
    std::string role = "Buyer";
    if (Database::getInstance()->addAccount(login, password, 0, role) == true)
    {
        Account account = Database::getInstance()->getAccount(login, password);
        return std::make_shared<Account>(account);
    }
    else
    {
        return std::shared_ptr<Account>(nullptr);
    }
}

void operator+=(Account& account, int addedPoints) {
    account.accountPoints += addedPoints;
}

void operator-=(Account& account, int usedPoints) {
    account.accountPoints -= usedPoints;
}

bool Account::operator!=(const Account& right) const {
    if (this->getLogin() == right.getLogin() &&
        this->getPassword() == right.getPassword() &&
        this->getPoints() == right.getPoints() &&
        this->getRole() == right.getRole())
    {
        return false;
    }
    else
    {
        return true;
    }
}
