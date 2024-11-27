#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include "Account.h"
#include <QWidget>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SignInWindow; }
QT_END_NAMESPACE

class SignInWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SignInWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *stackedWidget;
    Account account;

signals:
    void backButtonClicked();
    void signInButtonClicked();
    void signInSuccessful(std::shared_ptr<Account> currentAccount);
};

#endif // SIGNINWINDOW_H
