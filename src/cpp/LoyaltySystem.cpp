#include "../header/LoyaltySystem.h"
#include "../header/Account.h"
#include "../header/Menu.h"
#include "../header/Database.h"
#include <iostream>
#include <cmath>
#include <sqlite3.h>

LoyaltySystem::LoyaltySystem() = default;
 
std::shared_ptr<Account> LoyaltySystem::logIn()
{
    std::string login;
    std::string password;

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

std::shared_ptr<Account> LoyaltySystem::signIn()
{
    std::string login;
    std::string password;
    char needSignIn;

    std::cout << "Let's create an account!\nEnter login: ";
    std::cin >> login;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (Database::getInstance()->addAccount(login, password, 0) == true)
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

void LoyaltySystem::redeemPoints(std::shared_ptr<Account> account, double totalCost) const
{
    std::cout << "Your current loyalty points: " << account->getPoints() << '\n';

    if (account->getPoints() > 0)
    {
        int pointsToRedeem;
        std::cout << "How many points would you like to redeem? (1 point = 1$): ";
        std::cin >> pointsToRedeem;

        while (pointsToRedeem < 0 || pointsToRedeem > totalCost || pointsToRedeem > account->getPoints())
        {
            std::cout << "Invalid loyalty points. Please enter a number\nnot exceeding the order amount or the number\nof points in your account: ";
            std::cin >> pointsToRedeem;
        }

        *account -= pointsToRedeem;
        totalCost -= pointsToRedeem;

        std::cout << pointsToRedeem << " points redeemed.\n";
        std::cout << "New total cost: $" << totalCost << '\n';
    }
    else 
    {
        std::cout << "You have no loyalty points to redeem.\n";
    }

    int pointsEarned = round(totalCost * 0.1);
    *account += pointsEarned;
    std::cout << "Points earned: " << pointsEarned << std::endl;
    std::cout << "Current loyalty points: " << account->getPoints() << std::endl;

    Database::getInstance()->updateAccount(account->getLogin(), account->getPoints());
}