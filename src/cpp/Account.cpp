#include "../header/Account.h"
#include "../header/Database.h"

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

std::shared_ptr<Account> Account::logIn()
{
    std::cout << "Enter login: ";
    std::cin >> login;
    std::cout << "Enter password: ";
    std::cin >> password;
    
    if (Account account = Database::getInstance()->getAccount(login, password); account.getLogin() == login)
    {
        return std::make_shared<Account>(account);
    }

    std::cout << "Invalid login or password.\n";
    return nullptr;
}

std::shared_ptr<Account> Account::signIn()
{
    role = "Admin";
    char needSignIn;

    std::cout << "Let's create an account!\nEnter login: ";
    std::cin >> login;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (Database::getInstance()->addAccount(login, password, 0, role) == true)
    {
        std::cout << "Account created!\n";
        Account account = Database::getInstance()->getAccount(login, password);
        return std::make_shared<Account>(account);
    }
    else
    {
        std::cout << "You already have account. Want to sign in? (y/n): ";
        std::cin >> needSignIn;
        while (needSignIn != 'y' && needSignIn != 'n')
        {
            std::cout << "Choose yes or no (y/n): ";
            std::cin >> needSignIn;
        }
        std::cout << '\n';

        if (needSignIn == 'y')
        {
            return signIn();
        }
        else
        {
            return logIn();
        }
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