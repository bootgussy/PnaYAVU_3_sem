#include <string>
#include "../header/Admin.h"
#include "../header/Database.h"
#include "../header/Account.h"

Admin::Admin() = default;

std::string Admin::getRole() const {
    return "Admin";
}

void Admin::changeRole() const
{
    int id = 1;
    int numAccount;
    int accountRole;

    while (Database::getInstance()->getAccount(id) != Account("", "", 0, ""))
    {
        std::cout << id << ". " << Database::getInstance()->getAccount(id).getLogin() << ". Role: " << Database::getInstance()->getAccount(id).getRole() << std::endl;
        id++;
    }

    std::cout << "Choose account: ";
    std::cin >> numAccount;
    while (numAccount < 1 || numAccount >= id)
    {
        std::cout << "Incorrect. Please try again: ";
        std::cin >> numAccount;
    }

    std::cout << std::endl;

    std::cout << "Types of roles:" << std::endl;
    std::cout << "1. Buyer" << std::endl;
    std::cout << "2. Manager" << std::endl;
    std::cout << "3. Admin" << std::endl;
    std::cout << "Choose account role: ";

    std::cin >> accountRole;

    while (accountRole < 1 && accountRole > 3)
    {
        std::cout << "Please, write correct number (1-3): ";
        std::cin >> accountRole;
    }

    switch (accountRole)
    {
    case 1:
        Database::getInstance()->setRole(numAccount, "Buyer");
        break;
    case 2:
        Database::getInstance()->setRole(numAccount, "Manager");
        break;
    case 3:
        Database::getInstance()->setRole(numAccount, "Admin");
        break;
    default:
        break;
    }

    std::cout << std::endl;
    std::cout << "Role changed sucsesfully!" << std::endl;
}