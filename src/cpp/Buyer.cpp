#include <string>
#include <cmath>
#include "../header/Buyer.h"

Buyer::Buyer() = default;

std::string Buyer::getRole () const {
    return "Buyer";
}

void Buyer::redeemPoints(std::shared_ptr<Account> account, double totalCost) const
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