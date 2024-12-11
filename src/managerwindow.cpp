#include "managerwindow.h"

ManagerWindow::ManagerWindow(QWidget *parent)
    : LeadershipWindow("Статус: Менеджер", {
                                               {"Изменить цену", 1},
                                               {"Изменить скидку", 2},
                                               {"Добавить комбо", 3},
                                               {"Редактировать категории", 4},
                                               {"Редактировать опции", 5}
                                           }, parent) {
    connect(logOutButton, &QPushButton::clicked, this, &ManagerWindow::logOutButtonClicked);
}

void ManagerWindow::handleSpecificOperation(int operationIndex)
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
        break;
    case 5:
        break;
    default:
        break;
    }
}
