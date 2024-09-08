#include <iostream>
#include <vector>
#include <string>
#include "MenuSystem.h"

using namespace std; 

int main() {
    Menu menu;

    char continueOrdering;
    do {
        menu.selectOption();
        cout << "Do you want to add more options? (y/n): ";
        cin >> continueOrdering;
    } while (continueOrdering == 'y');

    menu.finishOrder();

    return 0;
}
