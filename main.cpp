#include <iostream>
#include <vector>
#include <string>
#include "Menu.h"

using namespace std;

int main() {
    Menu menu;
    char continueOrdering, needDeleteOption;

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

        cout << endl;
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
    
    menu.finishOrder();

    return 0;
}
