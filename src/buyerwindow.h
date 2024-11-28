#ifndef BUYERWINDOW_H
#define BUYERWINDOW_H

#include "Account.h"
#include "Menu.h"
#include "Order.h"
#include "AnimatedButton.h"
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QString>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class BuyerWindow; }
QT_END_NAMESPACE

class BuyerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BuyerWindow(std::shared_ptr<Account> currentAccount, QWidget *parent = nullptr);
    Order getOrder() const;
    void updateOrder(const Order& newOrder);
    void populateMenuItems(int categoryId);

private:
    std::shared_ptr<Account> account;
    Menu menu;
    Order order;

    QListWidget *categoryList;
    QScrollArea *menuScrollArea;
    QWidget *menuWidget;
    QGridLayout *menuLayout;

    void populateCategories();

signals:
    void logoutButtonClicked();
    void cartButtonClicked();
    void orderUpdated();
};

#endif // BUYERWINDOW_H

