#include "adminwindow.h"
#include "AnimatedButton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <string>
#include <iostream>

AdminWindow::AdminWindow(QWidget *parent)
    : QWidget(parent)
{
    QString cellStyle = "padding: 12px;";

    auto headerLayout = new QHBoxLayout();

    auto adminStatusWidget = new QWidget(this);
    QHBoxLayout *adminStatusLayout = new QHBoxLayout(adminStatusWidget);
    adminStatusLabel = new AnimatedButton("Статус:  Администратор", "white", "black", "color: black;", this);
    adminStatusLayout->addWidget(adminStatusLabel, 1, Qt::AlignLeft);
    adminStatusWidget->setStyleSheet(cellStyle);

    auto logOutWidget = new QWidget(this);
    QHBoxLayout *logOutLayout = new QHBoxLayout(logOutWidget);
    AnimatedButton *logOutButton = new AnimatedButton("Выход", "#EDC676", "#EDC676", "padding: 12px;", this);
    logOutLayout->addWidget(logOutButton, 1, Qt::AlignCenter);

    headerLayout->addWidget(adminStatusWidget, 0, Qt::AlignLeft);
    headerLayout->addWidget(logOutWidget, 0, Qt::AlignRight);

    auto headerWidget = new QWidget(this);
    headerWidget->setLayout(headerLayout);

    QFrame *horizontalLine = new QFrame(this);
    horizontalLine->setFrameShape(QFrame::HLine);
    horizontalLine->setFrameShadow(QFrame::Sunken);

    auto operationsWidget = new QWidget(this);

    auto operationsLabelWidget = new QWidget(this);
    QHBoxLayout *operationsLabelLayout = new QHBoxLayout(operationsLabelWidget);
    AnimatedButton *operationsLabelButton = new AnimatedButton("Операции", "white", "black", "color: black;", this);
    operationsLabelButton->setEnabled(false);
    operationsLabelLayout->addWidget(operationsLabelButton, 1, Qt::AlignCenter);
    operationsLabelWidget->setStyleSheet(cellStyle);

    operationsList = new QListWidget(this);
    operationsList->setFocusPolicy(Qt::NoFocus);

    addItemToList("Изменить цену", 1);
    addItemToList("Изменить скидку", 2);
    addItemToList("Добавить комбо", 3);
    addItemToList("Редактировать категории", 4);
    addItemToList("Редактировать опции", 5);
    addItemToList("Изменить статус аккаунта", 6);

    auto operationsLayout = new QVBoxLayout(this);
    operationsLayout->addWidget(operationsLabelWidget);
    operationsLayout->addWidget(operationsList);

    operationsWidget->setLayout(operationsLayout);
    operationsWidget->setStyleSheet(R"(
                                QWidget {
                                    background-color: white;
                                    border: 2px solid black;
                                    border-radius: 5px;
                                    padding: 5px;
                                }
                                )");
    operationsLabelWidget->setStyleSheet("border: 0px;");
    operationsList->setStyleSheet(R"(
                                QListWidget {
                                    border: 0px;
                                    background-color: white;
                                    padding: 5px;
                                }
                                QListWidget::item {
                                    border: 1px solid lightgray;
                                    padding: 10px;
                                    border-radius: 5px;
                                    color: black;
                                    margin: 5px;
                                }
                                QListWidget::item:selected {
                                    background-color: lightgray;
                                }
                                QListWidget::item:hover {
                                    background-color: #e0e0e0;
                                }
                                )");

    operationsWidget->setMaximumWidth(230);

    operationWidget = new QWidget(this);
    operationLayout = new QVBoxLayout(operationWidget);
    operationLayout->setContentsMargins(0, 0, 0, 0);
    operationWidget->setObjectName("operationWidget");
    operationWidget->setStyleSheet(R"(
                                #operationWidget {
                                    background-color: white;
                                    border: 2px solid black;
                                    border-radius: 5px;
                                    padding: 5px;
                                }
                                )");

    auto mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(operationsWidget);
    mainLayout->addWidget(operationWidget);

    auto mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(headerWidget, 0, Qt::AlignTop);
    layout->addWidget(horizontalLine);
    layout->addWidget(mainWidget);

    setLayout(layout);

    setLayout(layout);

    setWindowTitle("Администратор");
    resize(400, 500);

    connect(operationsList, &QListWidget::itemClicked, [this](QListWidgetItem *operationIndex)
    {
        if (currentOperationWidget) {
            operationLayout->removeWidget(currentOperationWidget);
            currentOperationWidget->deleteLater();  // Безопасное удаление
            currentOperationWidget = nullptr;
        }

        switch(operationIndex->data(Qt::UserRole).toInt())
        {
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

        if (currentOperationWidget) {
            operationLayout->addWidget(currentOperationWidget, 1);
            currentOperationWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        }
    });

    connect(logOutButton, &QPushButton::clicked, this, &AdminWindow::logOutButtonClicked);
}

void AdminWindow::addItemToList(QString itemName, int itemIndex) {
    auto item = new QListWidgetItem(itemName, operationsList);

    item->setData(Qt::UserRole, itemIndex);

    operationsList->addItem(item);
}
