#include "cartwindow.h"

CartWindow::CartWindow(std::shared_ptr<Account> currentAccount, QWidget *parent)
    : QWidget(parent), account(currentAccount) {

    auto mainLayout = new QVBoxLayout(this);

    stackedWidget = new QStackedWidget(this);

    stackedWidget->addWidget(cartWidget());
    stackedWidget->addWidget(loyaltySystemWidget());

    stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(stackedWidget, 1);

}

void CartWindow::populateOrderItemsToScrollArea() {
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

    int row = 0;
    int col = 0;
    int index = 0;

    for (const MenuOption &item : order.orderedOptions) {
        auto imageLabel = new QLabel;

        auto itemWidget = new QWidget(this);

        auto itemLayout = new QVBoxLayout(itemWidget);

        auto contentLayout = new ItemLayout(item, this);
        itemLayout->addLayout(contentLayout);

        auto deleteFromCartButton = new AnimatedButton("Удалить из заказа", "#C28D4B", "#C28D4B", "#C28D4B", "color: white; padding: 3px 7px 3px 7px;", this);
        itemLayout->addWidget(deleteFromCartButton, 0, Qt::AlignCenter);

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

            totalCostButton->setText("   К оплате: $" + QString::number(order.totalCost) + "   ");
            totalCostLabel->setText("   К оплате: $" + QString::number(order.totalCost) + "   ");

            cartLabel->setText("   Корзина  |  " + QString::number(order.orderedOptions.size()));
            orderLabel->setText("   Ваш заказ  |  " + QString::number(order.orderedOptions.size()));

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
    orderWidget->update();
    orderScrollArea->setWidgetResizable(true);
}

void CartWindow::populateOrderItemsToList() {
    if (!orderList) {
        orderList = new QListWidget(this);
        orderList->setFocusPolicy(Qt::NoFocus);
    } else {
        orderList->clear();
    }

    for (const MenuOption &item : order.orderedOptions) {
        auto nameLabel = new MarqueeLabel;

        nameLabel->setText(QString::fromStdString(item.getName()));
        nameLabel->setMaximumHeight(30);
        nameLabel->setMaximumWidth(100);
        nameLabel->setStyleSheet("border: 1px solid lightgray; background: lightgray; border-radius: 5px; color: black; padding: 12px 12px;");

        double discountedPrice = round((item.getPrice() - (item.getPrice() / 100 * item.getDiscount())) * 100) / 100;
        auto newPriceLabel = new QLabel(QString("$%1").arg(discountedPrice));

        auto priceLabel = new QLabel(QString("$%1").arg(item.getPrice()));

        if (item.getDiscount() == 0) {
            newPriceLabel->setStyleSheet("border: 0px; color: white;");
            priceLabel->setStyleSheet("border: 0px; color: black;");
        } else {
            newPriceLabel->setStyleSheet("border: 0px; color: red;");
            priceLabel->setText(QString("<html><body><s>$%1</s></body></html>").arg(item.getPrice()));
            priceLabel->setStyleSheet("border: 0px; color: black;");
        }

        auto nameAndPriceWidget = new QWidget(this);
        auto nameAndPriceLayout = new QHBoxLayout(nameAndPriceWidget);

        nameAndPriceLayout->addWidget(nameLabel, 0, Qt::AlignLeft);
        nameAndPriceLayout->addWidget(newPriceLabel, 0, Qt::AlignRight);
        nameAndPriceLayout->addWidget(priceLabel, 0, Qt::AlignRight);
        nameAndPriceLayout->setContentsMargins(5, 5, 5, 5);

        auto listItem = new QListWidgetItem();
        listItem->setSizeHint(nameAndPriceWidget->sizeHint());

        orderList->addItem(listItem);
        orderList->setItemWidget(listItem, nameAndPriceWidget);
    }

    orderList->setStyleSheet(R"(
                                QListWidget {
                                    border: 0px;
                                    background-color: white;
                                    padding: 5px;
                                }
                                QListWidget::item {
                                    border: 1px solid lightgray;
                                    padding: 1px;
                                    border-radius: 5px;
                                    color: black;
                                    margin: 2px;
                                }
                                )");

    orderList->repaint();
}


QWidget *CartWindow::cartWidget() {
    auto mainWidget = new QWidget(this);
    auto layout = new QVBoxLayout(mainWidget);

    auto headerWidget = new QWidget(this);
    auto headerLayout = new QHBoxLayout(headerWidget);

    auto backButton = new QPushButton(this);
    backButton->setIcon(QIcon(":/pics/pics/back_arrow.png"));
    backButton->setIconSize(QSize(24, 24));
    backButton->setFlat(true);
    headerLayout->addWidget(backButton, 1, Qt::AlignLeft);

    auto cartWidget = new QWidget(this);
    auto cartLayout = new QHBoxLayout(cartWidget);
    cartLabel = new AnimatedButton("   Корзина  |  0", "white", "black", "white", "color: black; padding: 7px;", this);
    cartLabel->setIcon(QIcon(":/pics/pics/cart_icon.png"));
    cartLabel->setIconSize(QSize(24, 24));
    cartLayout->addWidget(cartLabel, 1, Qt::AlignCenter);
    headerLayout->addWidget(cartWidget, 1, Qt::AlignRight);

    orderScrollArea = new QScrollArea(this);
    orderWidget = new QWidget(this);
    orderLayout = new QGridLayout(orderWidget);

    orderScrollArea->setWidget(orderWidget);

    auto orderScrollAreaWidget = new QWidget(this);
    auto orderScrollAreaLayout = new QHBoxLayout(orderScrollAreaWidget);
    orderScrollAreaLayout->addWidget(orderScrollArea);

    auto totalCostWidget = new QWidget(this);
    auto totalCostLayout = new QHBoxLayout(totalCostWidget);

    totalCostButton = new AnimatedButton("   К оплате: $" + QString::number(order.totalCost) + "   ", "#C28D4B", "black", "#C28D4B", "color: white; padding: 11px;", this);
    totalCostButton->setEnabled(false);
    totalCostLayout->addWidget(totalCostButton, 1, Qt::AlignCenter);

    layout->addWidget(headerWidget);
    layout->addWidget(orderScrollAreaWidget);
    layout->addWidget(totalCostWidget);

    populateOrderItemsToScrollArea();

    connect(backButton, &QPushButton::clicked, this, &CartWindow::backButtonClicked);

    connect(totalCostButton, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentIndex(1);
    });

    return mainWidget;
}

QWidget *CartWindow::loyaltySystemWidget() {
    auto mainWidget = new QWidget(this);
    auto layout = new QVBoxLayout(mainWidget);

    auto headerWidget = new QWidget(this);
    auto headerLayout = new QHBoxLayout(headerWidget);

    auto backButton = new QPushButton(this);
    backButton->setIcon(QIcon(":/pics/pics/back_arrow.png"));
    backButton->setIconSize(QSize(24, 24));
    backButton->setFlat(true);
    headerLayout->addWidget(backButton, 1, Qt::AlignLeft);

    auto loyaltySystemHeaderButton = new AnimatedButton("Списание баллов", "white", "black", "white", "color: black; padding: 12px; margin: 0px;", this);

    headerLayout->addWidget(backButton, 0, Qt::AlignLeft);
    headerLayout->addWidget(loyaltySystemHeaderButton, 0, Qt::AlignRight);

    auto totalCostWidget = new QWidget(this);
    auto totalCostLayout = new QHBoxLayout(totalCostWidget);

    totalCostLabel = new AnimatedButton("   К оплате: $" + QString::number(order.totalCost) + "   ", "white", "black", "white", "color: black; padding: 11px;", this);
    totalCostLayout->addWidget(totalCostLabel, 1, Qt::AlignLeft);

    pointsButton = new AnimatedButton("   Баллы:  " + QString::number(account->getPoints()) + " ", "white", "black", "white", "color: black; padding: 7px;", this);
    pointsButton->setIcon(QIcon(":/pics/pics/points_icon.png"));
    pointsButton->setIconSize(QSize(24, 24));
    totalCostLayout->addWidget(pointsButton, 1, Qt::AlignRight);

    auto loyaltySystemLabelButton = new AnimatedButton("Введите количество баллов для списания (1 балл = $1):", "lightgray", "white", "white", "color: black; padding: 7px; margin: 0px;", this);

    countOfPointsInput = new QLineEdit(this);
    countOfPointsInput->setPlaceholderText("Количество баллов");
    countOfPointsInput->setMinimumWidth(270);

    auto redeemButton = new AnimatedButton("Списать", "#C28D4B", "white", "#C28D4B", "color: white; padding: 7px;", this);

    redeemButton->setEnabled(false);

    connect(countOfPointsInput, &QLineEdit::textChanged, redeemButton, [redeemButton](const QString &text) {
        redeemButton->setEnabled(!text.trimmed().isEmpty());
    });

    auto loyaltySystemWidget = new QWidget(this);
    auto loyaltySystemLayout = new QVBoxLayout(loyaltySystemWidget);

    loyaltySystemWidget->setObjectName("loyaltySystemWidget");
    loyaltySystemWidget->setStyleSheet(R"(
                                #loyaltySystemWidget {
                                    background-color: white;
                                    border: 2px solid black;
                                    border-radius: 10px;
                                    padding: 20px;
                                }
                                )");

    loyaltySystemLayout->addWidget(totalCostWidget, 0, Qt::AlignCenter);
    loyaltySystemLayout->addWidget(loyaltySystemLabelButton, 0, Qt::AlignCenter);
    loyaltySystemLayout->addWidget(countOfPointsInput, 0, Qt::AlignCenter);
    loyaltySystemLayout->addWidget(redeemButton, 0, Qt::AlignCenter);
    loyaltySystemLayout->setSpacing(20);

    orderLabel = new AnimatedButton("   Ваш заказ  |  " + QString::number(order.orderedOptions.size()), "white", "black", "white", "color: black; padding: 7px;", this);

    orderList = new QListWidget();

    orderList->setFrameStyle(QFrame::Box);

    populateOrderItemsToList();

    finalOrderWidget = new QWidget(this);
    finalOrderLayout = new QVBoxLayout(finalOrderWidget);

    finalOrderLayout->addWidget(orderLabel, 0, Qt::AlignCenter);
    finalOrderLayout->addWidget(orderList, 0, Qt::AlignCenter);

    auto loyaltySystemAndOrderWidget = new QWidget(this);
    auto loyaltySystemAndOrderLayout = new QHBoxLayout(loyaltySystemAndOrderWidget);

    loyaltySystemAndOrderLayout->addWidget(loyaltySystemWidget);
    loyaltySystemAndOrderLayout->addWidget(finalOrderWidget);

    layout->addWidget(headerWidget, 1, Qt::AlignTop);
    layout->addWidget(loyaltySystemAndOrderWidget, 1, Qt::AlignCenter);
    layout->setSpacing(5);

    connect(backButton, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentIndex(0);
    });

    connect(redeemButton, &QPushButton::clicked, [this]() {
        try {
            confirmOrder(countOfPointsInput->text());
        } catch (const ExceptionHandler& e) {
            CustomMessageBox::warning(this, "Ошибка", e.what());
        }
    });

    mainWidget->setMaximumHeight(400);

    return mainWidget;
}

Order CartWindow::getOrder() const {
    return order;
}

void CartWindow::updateOrder(const Order& newOrder)
{
    order = newOrder;
    populateOrderItemsToScrollArea();
    populateOrderItemsToList();

    if (order.totalCost == 0) {
        totalCostButton->setEnabled(false);
    }
    else {
        totalCostButton->setEnabled(true);
    }
}

void CartWindow::updateTotalCostLabel(const double newTotalCost)
{
    totalCostButton->setText("   К оплате: $" + QString::number(newTotalCost) + "   ");
    totalCostLabel->setText("   К оплате: $" + QString::number(order.totalCost) + "   ");

    pointsButton->setText("   Баллы:  " + QString::number(account->getPoints()) + "   ");

    cartLabel->setText("   Корзина  |  " + QString::number(order.orderedOptions.size()));
    orderLabel->setText("   Ваш заказ  |  " + QString::number(order.orderedOptions.size()));

    populateOrderItemsToScrollArea();
    populateOrderItemsToList();
}

void CartWindow::redeemPoints(int pointsToRedeem)
{
    *account -= pointsToRedeem;
    order.totalCost -= pointsToRedeem;

    int pointsEarned = round(order.totalCost * 0.1);
    *account += pointsEarned;

    Database::getInstance()->updateAccount(account->getLogin(), account->getPoints());

    countOfPointsInput->clear();
    order.clearOrder();

    populateOrderItemsToScrollArea();
    populateOrderItemsToList();

    totalCostButton->setText("   К оплате: $0   ");
    totalCostLabel->setText("   К оплате: $0   ");

    cartLabel->setText("   Корзина  |  " + QString::number(order.orderedOptions.size()));
    orderLabel->setText("   Ваш заказ  |  " + QString::number(order.orderedOptions.size()));

    totalCostButton->setEnabled(false);

    emit pointsUpdated(account->getPoints());

    emit orderUpdated();

    emit orderFinished();
}

void CartWindow::confirmOrder(QString pointsToRedeemText)
{
    bool ok;
    int pointsToRedeem = pointsToRedeemText.toInt(&ok);

    if (!ok) {
        throw ExceptionHandler("Введенное количество баллов должно быть целым числом!");
    }
    if (pointsToRedeem > account->getPoints()) {
        throw ExceptionHandler("Недостаточно баллов для списания!");
    }
    if (pointsToRedeem < 0) {
        throw ExceptionHandler("Нельзя списать отрицательное число баллов!");
    }
    if (pointsToRedeem > order.totalCost) {
        throw ExceptionHandler("Нельзя списать больше баллов, чем сумма заказа!");
    }

    CustomMessageBox confirmDialog;
    confirmDialog.setWindowTitle("Подтверждение");
    if (pointsToRedeem != 0) {
        confirmDialog.setText("Вы уверены, что хотите списать баллы?");
        confirmDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        confirmDialog.setDefaultButton(QMessageBox::Yes);

        if (confirmDialog.exec() == QMessageBox::Yes) {
            redeemPoints(pointsToRedeem);
        }
    } else {
        if (account->getPoints() == 0) {
            confirmOrder(countOfPointsInput->text());
        } else {
            confirmDialog.setText("Вы уверены, что не хотите списывать баллы?");
            confirmDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            confirmDialog.setDefaultButton(QMessageBox::No);

            if (confirmDialog.exec() == QMessageBox::Yes) {
                redeemPoints(pointsToRedeem);
            }
        }
    }
}
