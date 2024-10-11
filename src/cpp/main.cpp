#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "../header/Menu.h"
#include "../header/Order.h"
#include "../header/MenuOption.h"
#include "../header/LoyaltySystem.h"
#include "../header/Database.h"

using namespace std;

int main() {
    Menu menu;
    LoyaltySystem loyaltySystem;

    std::shared_ptr<Account> currentAccount = nullptr;
    char hasAccount;
    char needRepeatLogIn;
    char continueOrdering;
    char needDeleteOption;

    cout << "Do you have an account? (y/n): ";
    cin >> hasAccount;

    while (hasAccount != 'y' && hasAccount != 'n')
    {
        cout << "Choose yes or no (y/n): ";
        cin >> hasAccount;
    }

    if (hasAccount == 'y')
    {
        currentAccount = loyaltySystem.logIn();
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
                currentAccount = loyaltySystem.logIn();
            }
            else
            {
                hasAccount = 'n';
                currentAccount = loyaltySystem.signIn();
            }
        }
    }
    else
    {
        currentAccount = loyaltySystem.signIn();
    }

    cout << '\n';

    do
    {
        menu.selectOption();
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
            menu.deleteOption();
        }
    } while (needDeleteOption != 'n');
    
    cout << '\n';

    menu.finishOrder();

    cout << '\n';

    loyaltySystem.redeemPoints(std::shared_ptr<Account>(currentAccount), menu.GetOrderTotalCost());

    return 0;
}
