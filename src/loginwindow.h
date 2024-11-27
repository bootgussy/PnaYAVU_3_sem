#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "Account.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class LogInWindow; }
QT_END_NAMESPACE

class LogInWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LogInWindow(QWidget *parent = nullptr);

private:
    Account account;

signals:
    void backButtonClicked();
    void logInButtonClicked();
    void logInSuccessful(std::shared_ptr<Account> currentAccount);
};

#endif // LOGINWINDOW_H
