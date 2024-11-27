#include "Account.h"
#include "Database.h"

Account::Account(const std::string& accountLogin, const std::string& accountPassword, int accountPoints, const std::string& accountRole)
    : login(accountLogin), password(accountPassword), points(accountPoints), role(accountRole) {}

Account::Account() = default;

std::string Account::getLogin() const
{
    return login;
}

std::string Account::getPassword() const
{
    return password;
}

int Account::getPoints() const
{
    return points;
}

std::string Account::getRole() const
{
    return role;
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
    role = "Buyer";
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
    account.points += addedPoints;
}

void operator-=(Account& account, int usedPoints) {
    account.points -= usedPoints;
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
