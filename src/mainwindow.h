#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "signinwindow.h"
#include "loginwindow.h"
#include "buyerwindow.h"
#include "cartwindow.h"
#include "managerwindow.h"
#include "adminwindow.h"
#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SignInWindow;
class LogInWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void openSignInWidget();
    void openLogInWidget();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    SignInWindow *signInWidget;
    LogInWindow *logInWidget;
    BuyerWindow *buyerWidget;
    CartWindow *cartWidget;
    ManagerWindow *managerWidget;
    AdminWindow *adminWidget;
};
#endif // MAINWINDOW_H
