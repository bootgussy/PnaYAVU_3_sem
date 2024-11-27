#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "Order.h"
#include "AnimatedButton.h"
#include "buyerwindow.h"
#include "MenuOption.h"
#include "changeoptionprice.h"
#include "changeoptiondiscount.h"
#include <vector>
#include <QLabel>
#include <QListWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QString>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class AdminWindow; }
QT_END_NAMESPACE

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);

private:
    AnimatedButton *adminStatusLabel;
    QListWidget *operationsList;
    QVBoxLayout *operationLayout;
    QWidget *operationWidget;
    QWidget *currentOperationWidget = nullptr;

    void addItemToList(QString itemName, int itemIndex);

signals:
    void logOutButtonClicked();
};

#endif // ADMINWINDOW_H
