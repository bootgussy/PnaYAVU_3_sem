#include <iostream>
#include <vector>
#include <string>
#include "MenuSystem.h"

using namespace std; 

int main() {
    Menu menu;
    char continueOrdering;

    do
    {
        menu.selectOption();
        cout << "Do you want to add more options? (y/n): ";
        cin >> continueOrdering;

        if (continueOrdering != 'y')
        {
            do
            {
                cout << "Choose yes or no (y/n): ";
                cin >> continueOrdering;
            } while (continueOrdering != 'y' && continueOrdering != 'n');
        }
    } while (continueOrdering != 'n');

    menu.finishOrder();

    return 0;
}
