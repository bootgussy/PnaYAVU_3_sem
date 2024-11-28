#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signinwindow.h"
#include "loginwindow.h"
#include "buyerwindow.h"
#include "Account.h"
#include "Order.h"
#include "AnimatedButton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , stackedWidget(new QStackedWidget(this))
{
    ui->setupUi(this);

    // Логотип
    auto logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap(":/pics/pics/logo.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    // Кнопки
    auto signInButton = new AnimatedButton("Вход в аккаунт", "#C28D4B", "#C28D4B", "", this);
    signInButton->setMinimumSize(150, 40);

    auto logInButton = new AnimatedButton("Создать аккаунт", "#C28D4B", "#C28D4B", "background: white; color: #C28D4B", this);
    logInButton->setMinimumSize(150, 40);

    // Горизонтальный макет для кнопок
    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(signInButton);
    buttonLayout->addWidget(logInButton);
    buttonLayout->setSpacing(20);
    buttonLayout->setAlignment(Qt::AlignCenter);

    // Основной вертикальный макет
    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(logoLabel, 0, Qt::AlignCenter);
    mainLayout->addLayout(buttonLayout);

    auto mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);

    signInWidget = new SignInWindow(this);
    logInWidget = new LogInWindow(this);

    // Добавляем виджеты в QStackedWidget
    stackedWidget->addWidget(mainWidget);
    stackedWidget->addWidget(signInWidget);
    stackedWidget->addWidget(logInWidget);

    setCentralWidget(stackedWidget);

    connect(signInButton, &QPushButton::clicked, this, &MainWindow::openSignInWidget);
    connect(signInWidget, &SignInWindow::backButtonClicked, [this]() {
        stackedWidget->setCurrentIndex(0);
    });

        connect(signInWidget, &SignInWindow::signInSuccessful, [this](std::shared_ptr<Account> currentAccount) {
        if (currentAccount->getRole() == "Buyer")
        {
            buyerWidget = new BuyerWindow(currentAccount, this);
            cartWidget = new CartWindow(this);
            stackedWidget->addWidget(buyerWidget);
            stackedWidget->addWidget(cartWidget);

            stackedWidget->setCurrentWidget(buyerWidget);

            connect(buyerWidget, &BuyerWindow::logoutButtonClicked, [this]() {
                stackedWidget->setCurrentIndex(0);
                buyerWidget->deleteLater();
            });

                connect(buyerWidget, &BuyerWindow::cartButtonClicked, [this] () {
                    stackedWidget->setCurrentWidget(cartWidget);
                });

                connect(cartWidget, &CartWindow::backButtonClicked, [this]() {
                    stackedWidget->setCurrentIndex(3);
                });

                connect(cartWidget, &CartWindow::orderUpdated, this, [this]() {
                    buyerWidget->updateOrder(cartWidget->getOrder());
                });

            connect(buyerWidget, &BuyerWindow::orderUpdated, this, [this]() {
                cartWidget->updateOrder(buyerWidget->getOrder());
                cartWidget->updateTotalCostLabel(buyerWidget->getOrder().totalCost);
            });

        }
        else if (currentAccount->getRole() == "Manager")
        {
            managerWidget = new ManagerWindow();
            stackedWidget->addWidget(managerWidget);

            connect(managerWidget, &ManagerWindow::logOutButtonClicked, [this]() {
                stackedWidget->setCurrentIndex(0);
                managerWidget->deleteLater();
            });

            stackedWidget->setCurrentWidget(managerWidget);
        }
        else if (currentAccount->getRole() == "Admin")
        {
            adminWidget = new AdminWindow();
            stackedWidget->addWidget(adminWidget);

            connect(adminWidget, &AdminWindow::logOutButtonClicked, [this]() {
                stackedWidget->setCurrentIndex(0);
                adminWidget->deleteLater();
            });

            stackedWidget->setCurrentWidget(adminWidget);
        }
        });

    connect(logInButton, &QPushButton::clicked, this, &MainWindow::openLogInWidget);
    connect(logInWidget, &LogInWindow::backButtonClicked, [this]() {
        stackedWidget->setCurrentIndex(0);
    });

        connect(logInWidget, &LogInWindow::logInSuccessful, [this](std::shared_ptr<Account> currentAccount) {
            buyerWidget = new BuyerWindow(currentAccount, this);
            stackedWidget->addWidget(buyerWidget);

            stackedWidget->setCurrentWidget(buyerWidget);

            connect(buyerWidget, &BuyerWindow::logoutButtonClicked, [this]() {
                stackedWidget->setCurrentIndex(0);
                buyerWidget->deleteLater();
            });
        });

    setWindowTitle("Кофейня");
    resize(790, 550);
}

void MainWindow::openSignInWidget()
{
    stackedWidget->setCurrentWidget(signInWidget);
}

void MainWindow::openLogInWidget()
{
    stackedWidget->setCurrentWidget(logInWidget);
}


MainWindow::~MainWindow()
{
    delete ui;
}
