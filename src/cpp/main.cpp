#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include "../header/Menu.h"
#include "../header/Order.h"
#include "../header/MenuOption.h"
#include "../header/Database.h"
#include "../header/Person.h"
#include "../header/Buyer.h"
#include "../header/Manager.h"
#include "../header/Admin.h"

using namespace std;

Menu menu;
Account account;
Order order;
std::shared_ptr<Account> currentAccount = nullptr;

void logInOrSignIn()
{
    char hasAccount;
    char needRepeatLogIn;

    cout << "Do you have an account? (y/n): ";
    cin >> hasAccount;

    while (hasAccount != 'y' && hasAccount != 'n')
    {
        cout << "Choose yes or no (y/n): ";
        cin >> hasAccount;
    }

    if (hasAccount == 'y')
    {
        currentAccount = account.logIn();
        while (!currentAccount && hasAccount != 'n')
        {
            cout << "Log in failed. Want to try again? (y/n): ";
            cin >> needRepeatLogIn;
            while (needRepeatLogIn != 'y' && needRepeatLogIn != 'n')
            {
                cout << "Choose yes or no (y/n): ";
                cin >> needRepeatLogIn;
            }

            if (needRepeatLogIn == 'y')
            {
                currentAccount = account.logIn();
            }
            else
            {
                hasAccount = 'n';
                currentAccount = account.signIn();
            }
        }
    }
    else
    {
        currentAccount = account.signIn();
    }

    cout << '\n';
}

template<typename addDisc, typename removeDisc>
void discounts(addDisc addDiscounts, removeDisc removeDiscounts)
{
    int discountOperation;

    cout << "Types of operations" << endl;
    cout << "1. Add discount to option" << endl;
    cout << "2. Remove discount from option" << endl;

    cout << "Choose operation: ";
    cin >> discountOperation;

    while (discountOperation < 1 || discountOperation > 2)
    {
        cout << "Please, write correct number (1-2): ";
        cin >> discountOperation;
    }

    switch (discountOperation)
    {
    case 1:
        addDiscounts();
        break;
    case 2:
        removeDiscounts();
        break;
    default:
        break;
    }
}

void buyerMenu()
{
    Buyer buyer;

    char continueOrdering;
    char needDeleteOption;

    do
    {
        order = menu.addToOrder(order);
        cout << "Do you want to add more options? (y/n): ";
        cin >> continueOrdering;

        while (continueOrdering != 'y' && continueOrdering != 'n')
        {
            cout << "Choose yes or no (y/n): ";
            cin >> continueOrdering;
        }

        cout << '\n';
    } while (continueOrdering != 'n');

    do
    {
        cout << "Do you want to delete any option? (y/n): ";
        cin >> needDeleteOption;

        while (needDeleteOption != 'y' && needDeleteOption != 'n')
        {
            cout << "Choose yes or no (y/n): ";
            cin >> needDeleteOption;
        }

        if (needDeleteOption == 'y')
        {
            order = menu.deleteOption(order);
        }
    } while (needDeleteOption != 'n');

    cout << '\n';

    menu.finishOrder(order);

    cout << '\n';

    buyer.redeemPoints(std::shared_ptr<Account>(currentAccount), menu.GetOrderTotalCost(order));
}

void managerMenu()
{
    Manager manager;
    int managerSelection;

    do
    {
        cout << "Types of operations" << endl;
        cout << "1. Change option price" << endl;
        cout << "2. Work with discounts" << endl;
        cout << "3. Add combo" << endl;
        cout << "4. Add category to menu" << endl;
        cout << "5. Add option to category" << endl;
        cout << "6. Remove option from menu" << endl;
        cout << "7. Exit" << endl;

        cout << "Choose operation: ";
        cin >> managerSelection;

        while (managerSelection < 1 || managerSelection > 7)
        {
            cout << "Please, write correct number (1-7): ";
            cin >> managerSelection;
        }

        switch (managerSelection)
        {
        case 1:
            manager.changePrice();
            break;
        case 2:
            discounts([&manager]() { manager.addDiscounts(); }, [&manager]() { manager.removeDiscounts(); });
            break;
        case 3:
            manager.addCombo();
            break;
        case 4:
            manager.addCategoryToMenu();
            break;
        case 5:
            manager.addOptionToCategory();
            break;
        case 6:
            manager.removeOptionFromMenu();
            break;
        case 7:
            break;
        default:
            break;
        }
    } while (managerSelection != 7);
}

void adminMenu()
{
    Admin admin;
    int adminSelection;

    do
    {
        cout << "Types of operations" << endl;
        cout << "1. Change option price" << endl;
        cout << "2. Work with discounts" << endl;
        cout << "3. Add combo" << endl;
        cout << "4. Add category to menu" << endl;
        cout << "5. Add option to category" << endl;
        cout << "6. Remove option from menu" << endl;
        cout << "7. Change role" << endl;
        cout << "8. Exit" << endl;

        cout << "Choose operation: ";
        cin >> adminSelection;

        while (adminSelection < 1 || adminSelection > 8)
        {
            cout << "Please, write correct number (1-8): ";
            cin >> adminSelection;
        }

        switch (adminSelection)
        {
        case 1:
            admin.changePrice();
            break;
        case 2:
            discounts([&admin]() { admin.addDiscounts(); }, [&admin]() { admin.removeDiscounts(); });
            break;
        case 3:
            admin.addCombo();
            break;
        case 4:
            admin.addCategoryToMenu();
            break;
        case 5:
            admin.addOptionToCategory();
            break;
        case 6:
            admin.removeOptionFromMenu();
            break;
        case 7:
            admin.changeRole();
            break;
        case 8:
            break;
        default:
            break;
        }
    } while (adminSelection != 8);
}

int main() {
    std::string role;

    logInOrSignIn();

    role = std::shared_ptr<Account>(currentAccount)->getRole();

    if (role == "Buyer")
    {
        buyerMenu();
    }
    else if (role == "Manager")
    {
        managerMenu();
    }
    else if (role == "Admin")
    {
        adminMenu();
    }

    return 0;
}
