#include "cartwindow.h"
#include "marqueelabel.h"
#include "buyerwindow.h"
#include "AnimatedButton.h"
#include "Order.h"
#include "itemlayout.h"
#include <iostream>
#include <vector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QString>
#include <string>

CartWindow::CartWindow(QWidget *parent)
    : QWidget(parent) {

    QHBoxLayout *headerLayout = new QHBoxLayout();

    QString cellStyle = "padding: 7px;";

    QPushButton *backButton = new QPushButton(this);
    backButton->setIcon(QIcon(":/pics/pics/back_arrow.png"));
    backButton->setIconSize(QSize(24, 24));
    backButton->setFlat(true);
    headerLayout->addWidget(backButton, 1, Qt::AlignLeft);

    QWidget *cartWidget = new QWidget(this);
    QHBoxLayout *cartLayout = new QHBoxLayout(cartWidget);
    AnimatedButton *cartLabel = new AnimatedButton("   Корзина   ", "white", "black", "color: black;", this);
    cartLabel->setIcon(QIcon(":/pics/pics/cart_icon.png"));
    cartLabel->setIconSize(QSize(24, 24));
    cartLayout->addWidget(cartLabel, 1, Qt::AlignCenter);
    cartWidget->setStyleSheet(cellStyle);
    headerLayout->addWidget(cartWidget, 1, Qt::AlignRight);

    QWidget *headerWidget = new QWidget(this);
    headerWidget->setLayout(headerLayout);

    orderScrollArea = new QScrollArea(this);
    orderWidget = new QWidget(this);
    orderLayout = new QGridLayout(orderWidget);

    orderScrollArea->setWidget(orderWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(orderScrollArea);

    QWidget *mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);

    QWidget *totalCostWidget = new QWidget(this);
    QHBoxLayout *totalCostLayout = new QHBoxLayout(totalCostWidget);
    totalCostLabel = new AnimatedButton("   К оплате: $" + QString::number(order.totalCost) + "   ", "white", "black", "color: black;", this);
    totalCostLayout->addWidget(totalCostLabel, 1, Qt::AlignCenter);
    totalCostWidget->setStyleSheet(cellStyle);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(headerWidget);
    layout->addWidget(mainWidget);
    layout->addWidget(totalCostWidget);

    setLayout(layout);

    populateOrderItems();

    connect(backButton, &QPushButton::clicked, this, &CartWindow::backButtonClicked);

}

void CartWindow::populateOrderItems() {
    QLayoutItem *child;
    while ((child = orderLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    struct MenuItem {
        QString name;
        QString imagePath;
        double price;
    };

    int row = 0, col = 0;
    int index = 0;

    for (const MenuOption &item : order.orderedOptions) {
        QLabel *imageLabel = new QLabel;

        QWidget *itemWidget = new QWidget(this);

        QVBoxLayout *itemLayout = new QVBoxLayout(itemWidget);

        ItemLayout *contentLayout = new ItemLayout(item, this);
        itemLayout->addLayout(contentLayout);

        AnimatedButton *deleteFromCartButton = new AnimatedButton("Удалить из заказа", "#C28D4B", "#C28D4B", "color: white; padding: 3px 7px 3px 7px;", this);
        itemLayout->addWidget(deleteFromCartButton, 0, Qt::AlignCenter);

        itemWidget->setLayout(itemLayout);

        itemWidget->setStyleSheet(R"(
                                QWidget {
                                    border: 1px solid lightgray;
                                    border-radius: 5px;
                                    color: black;
                                    margin: 5px;
                                }
                                )");

        connect(deleteFromCartButton, &QPushButton::clicked, [this, index]() {
            order.deleteOption(index);
            updateOrder(order);
            totalCostLabel->setText("   К оплате: $" + QString::number(order.totalCost) + "   ");
            emit orderUpdated();
        });

        itemWidget->setMaximumHeight(250);
        itemWidget->setMaximumWidth(190);
        itemWidget->setMinimumWidth(180);

        orderLayout->addWidget(itemWidget, row, col);

        if (++col == 3) {
            col = 0;
            row++;
        }

        index++;
    }
    orderWidget->setLayout(orderLayout);
    orderWidget->update();
    orderScrollArea->setWidgetResizable(true);
}

Order CartWindow::getOrder() const {
    return order;
}

void CartWindow::updateOrder(const Order& newOrder)
{
    order = newOrder;
    populateOrderItems();
}

void CartWindow::updateTotalCostLabel(const double newTotalCost)
{
    totalCostLabel->setText("   К оплате: $" + QString::number(newTotalCost) + "   ");
    populateOrderItems();
}
