#include <iostream>
#include <vector>
#include <string>
#include "MenuSystem.h"

using namespace std; 

int main() {
    MenuSystem menuSystem;
    char continueOrdering;
    do {
        menuSystem.selectItem();
        cout << "Do you want to add more items? (y/n): ";
        cin >> continueOrdering;
    } while (continueOrdering == 'y');

    menuSystem.finishOrder();

    return 0;
}
