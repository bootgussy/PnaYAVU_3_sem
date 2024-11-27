#include "buyerwindow.h"
#include "marqueelabel.h"
#include "Database.h"
#include "Account.h"
#include "Menu.h"
#include "itemlayout.h"
#include "categorieslist.h"
#include <iostream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <QString>
#include <string>

BuyerWindow::BuyerWindow(std::shared_ptr<Account> currentAccount, QWidget *parent)
    : QWidget(parent), account(currentAccount) {

   // Создаём горизонтальный макет для шапки
    QHBoxLayout *headerLayout = new QHBoxLayout();

    QString cellStyle = "padding: 7px;";

    QWidget *pointsWidget = new QWidget(this);
    QHBoxLayout *pointsLayout = new QHBoxLayout(pointsWidget);
    AnimatedButton *pointsButton = new AnimatedButton("   Баллы:  " + QString::number(account->getPoints()) + " ", "white", "black", "color: black;", this);
    pointsButton->setIcon(QIcon(":/pics/pics/points_icon.png"));
    pointsButton->setIconSize(QSize(24, 24));
    pointsButton->setEnabled(false);
    pointsLayout->addWidget(pointsButton, 1, Qt::AlignCenter);
    pointsWidget->setStyleSheet(cellStyle);
    headerLayout->addWidget(pointsWidget, 1, Qt::AlignLeft);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    QWidget *cartWidget = new QWidget(this);
    QHBoxLayout *cartLayout = new QHBoxLayout(cartWidget);
    AnimatedButton *cartButton = new AnimatedButton("   Корзина", "#C28D4B", "#C28D4B", "color: white;", this);
    cartButton->setIcon(QIcon(":/pics/pics/cart_icon.png"));
    cartButton->setIconSize(QSize(24, 24));
    cartLayout->addWidget(cartButton, 1, Qt::AlignCenter);
    cartWidget->setStyleSheet(cellStyle);
    buttonsLayout->addWidget(cartWidget, 1, Qt::AlignCenter);

    QFrame *verticalLine = new QFrame(this);
    verticalLine->setFrameShape(QFrame::VLine);
    verticalLine->setFrameShadow(QFrame::Sunken);
    buttonsLayout->addWidget(verticalLine);

    QWidget *logoutWidget = new QWidget(this);
    QHBoxLayout *logoutLayout = new QHBoxLayout(logoutWidget);
    AnimatedButton *logoutButton = new AnimatedButton("Выход", "#EDC676", "#EDC676", "padding: 12px;", this);
    logoutLayout->addWidget(logoutButton, 1, Qt::AlignCenter);
    buttonsLayout->addWidget(logoutWidget, 1, Qt::AlignRight);

    headerLayout->addLayout(buttonsLayout);

    QWidget *headerWidget = new QWidget(this);
    headerWidget->setLayout(headerLayout);

    QWidget *categoriesWidget = new QWidget(this);

    QWidget *categoriesLabelWidget = new QWidget(this);
    QHBoxLayout *categoriesLabelLayout = new QHBoxLayout(categoriesLabelWidget);
    AnimatedButton *categoriesLabelButton = new AnimatedButton("     Категории     ", "white", "black", "color: black;", this);
    categoriesLabelButton->setEnabled(false);
    categoriesLabelLayout->addWidget(categoriesLabelButton, 1, Qt::AlignCenter);
    categoriesLabelWidget->setStyleSheet(cellStyle);

    categoryList = new CategoriesList(this);
    categoryList->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *categoryLayout = new QVBoxLayout(this);
    categoryLayout->addWidget(categoriesLabelWidget);
    categoryLayout->addWidget(categoryList);

    categoriesWidget->setLayout(categoryLayout);
    categoriesWidget->setStyleSheet(R"(
                                QWidget {
                                    background-color: white;
                                    border: 2px solid black;
                                    border-radius: 5px;
                                    padding: 5px;
                                }
                                )");
    categoriesLabelWidget->setStyleSheet("border: 0px;");

    categoriesWidget->setMaximumWidth(150);

    menuScrollArea = new QScrollArea(this);
    menuWidget = new QWidget(this);
    menuLayout = new QGridLayout(menuWidget);

    menuScrollArea->setWidget(menuWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(categoriesWidget);
    mainLayout->addWidget(menuScrollArea);

    QWidget *mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(headerWidget);
    layout->addWidget(mainWidget);

    setLayout(layout);

    connect(categoryList, &QListWidget::itemClicked, [this](QListWidgetItem *item) {
        int categoryId = item->data(Qt::UserRole).toInt();

        populateMenuItems(categoryId);
    });

    connect(cartButton, &QPushButton::clicked, this, &BuyerWindow::cartButtonClicked);

    connect(logoutButton, &QPushButton::clicked, this, &BuyerWindow::logoutButtonClicked);

}

void BuyerWindow::populateMenuItems(int categoryId) {
    QLayoutItem *child;
    while ((child = menuLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    struct MenuItem {
        QString name;
        QString imagePath;
        double price;
    };

    int row = 0, col = 0;
    for (const MenuOption &item : menu.displayOptions(categoryId)) {
        QLabel *imageLabel = new QLabel;

        QWidget *itemWidget = new QWidget(this);

        QVBoxLayout *itemLayout = new QVBoxLayout(itemWidget);

        ItemLayout *contentLayout = new ItemLayout(item, this);
        itemLayout->addLayout(contentLayout);

        AnimatedButton *addToCartButton = new AnimatedButton("Добавить в заказ", "#C28D4B", "#C28D4B", "color: white; padding: 3px 7px 3px 7px;", this);
        itemLayout->addWidget(addToCartButton, 0, Qt::AlignCenter);

        itemWidget->setLayout(itemLayout);

        itemWidget->setStyleSheet(R"(
                                QWidget {
                                    border: 1px solid lightgray;
                                    border-radius: 5px;
                                    color: black;
                                    margin: 5px;
                                }
                                )");

        connect(addToCartButton, &QPushButton::clicked, [this, item]() {
            order.addOption(item);
            emit orderUpdated();
        });

        itemWidget->setMaximumHeight(250);
        itemWidget->setMaximumWidth(190);
        itemWidget->setMinimumWidth(180);

        menuLayout->addWidget(itemWidget, row, col);

        if (++col == 3) {
            col = 0;
            row++;
        }
    }
    menuWidget->setLayout(menuLayout);
    menuWidget->update();
    menuScrollArea->setWidgetResizable(true);
}

Order BuyerWindow::getOrder() const {
    return order;
}

void BuyerWindow::updateOrder(const Order& newOrder)
{
    order = newOrder;
}
