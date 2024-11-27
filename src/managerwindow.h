#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include "Order.h"
#include "AnimatedButton.h"
#include"buyerwindow.h"
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
namespace Ui { class ManagerWindow; }
QT_END_NAMESPACE

class ManagerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerWindow(QWidget *parent = nullptr);

private:
    AnimatedButton *managerStatusLabel;
    QListWidget *operationsList;
    QVBoxLayout *operationLayout;
    QWidget *operationWidget;
    QWidget *currentOperationWidget = nullptr;

    void addItemToList(QString itemName, int itemIndex);

signals:
    void logOutButtonClicked();
};

#endif // MANAGERWINDOW_H
