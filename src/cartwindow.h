#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include "MenuOption.h"
#include "marqueelabel.h"
#include "buyerwindow.h"
#include "AnimatedButton.h"
#include "Order.h"
#include "itemlayout.h"
#include "Account.h"
#include "custommessagebox.h"
#include "exceptionhandler.h"
#include <QLabel>
#include <QStackedWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QString>
#include <iostream>
#include <vector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIcon>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class CartWindow; }
QT_END_NAMESPACE

class CartWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CartWindow(std::shared_ptr<Account> currentAccount, QWidget *parent = nullptr);
    QWidget *cartWidget();
    QWidget *loyaltySystemWidget();
    Order getOrder() const;
    void updateOrder(const Order& newOrder);
    void updateTotalCostLabel(const double newTotalCost);
    void redeemPoints(int pointsToRedeem);
    void confirmOrder(QString countOfPointsText);

private:
    Order order;

    QStackedWidget *stackedWidget;
    QScrollArea *orderScrollArea;
    QWidget *orderWidget;
    QGridLayout *orderLayout;
    AnimatedButton *totalCostButton;
    AnimatedButton *totalCostLabel;
    std::shared_ptr<Account> account;
    QLineEdit *countOfPointsInput;
    AnimatedButton *pointsButton;
    QListWidget *orderList;
    QWidget *finalOrderWidget;
    QVBoxLayout *finalOrderLayout;
    AnimatedButton *cartLabel;
    AnimatedButton *orderLabel;

    void populateOrderItemsToScrollArea();
    void populateOrderItemsToList();

signals:
    void orderFinished();
    void backButtonClicked();
    void orderUpdated();
    void pointsUpdated(int newPoints);
};

#endif // CARTWINDOW_H
