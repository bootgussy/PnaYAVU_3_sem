#include "../header/Account.h"

Account::Account(const std::string& accountLogin, const std::string& accountPassword, int accountPoints)
    : login(accountLogin), password(accountPassword), points(accountPoints) {}

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

void operator+=(Account& account, int addedPoints) {
    account.points += addedPoints;
}

void operator-=(Account& account, int usedPoints) {
    account.points -= usedPoints;
}