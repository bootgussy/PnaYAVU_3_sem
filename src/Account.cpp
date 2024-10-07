#include "Account.h"

Account::Account(const std::string& accountLogin, const std::string& accountPassword, int accountPoints)
    : login(accountLogin), password(accountPassword), points(accountPoints) {}

Account::Account()
{

}

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

void Account::operator+=(int addedPoints) {
    points += addedPoints;
}

void Account::operator-=(int usedPoints) {
    points -= usedPoints;
}