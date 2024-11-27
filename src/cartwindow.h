#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include "Order.h"
#include "AnimatedButton.h"
#include "buyerwindow.h"
#include "MenuOption.h"
#include <vector>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QString>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CartWindow; }
QT_END_NAMESPACE

class CartWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CartWindow(QWidget *parent = nullptr);
    Order getOrder() const;
    void updateOrder(const Order& newOrder);
    void updateTotalCostLabel(const double newTotalCost);

private:
    Order order;

    QScrollArea *orderScrollArea;
    QWidget *orderWidget;
    QGridLayout *orderLayout;
    AnimatedButton *totalCostLabel;

    void populateOrderItems();

signals:
    void backButtonClicked();
    void orderUpdated();
};

#endif // CARTWINDOW_H
