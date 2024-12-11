#include "adminwindow.h"

AdminWindow::AdminWindow(QWidget *parent)
           : LeadershipWindow("Статус: Администратор", {
                                                           {"Изменить цену", 1},
                                                           {"Изменить скидку", 2},
                                                           {"Добавить комбо", 3},
                                                           {"Редактировать категории", 4},
                                                           {"Редактировать опции", 5},
                                                           {"Изменить статус аккаунта", 6}
                                                       }, parent) {
    connect(logOutButton, &QPushButton::clicked, this, &AdminWindow::logOutButtonClicked);
}

void AdminWindow::handleSpecificOperation(int operationIndex)
{
    switch (operationIndex) {
    case 1:
        currentOperationWidget = new ChangeOptionPrice(this);
        break;
    case 2:
        currentOperationWidget = new ChangeOptionDiscount(this);
        break;
    case 3:
        break;
    case 4:
        currentOperationWidget = new EditCategories(this);
        break;
    case 5:
        currentOperationWidget = new EditOptions(this);
        break;
    case 6:
        break;
    default:
        break;
    }
}
