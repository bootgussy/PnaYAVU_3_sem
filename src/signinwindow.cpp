#include "signinwindow.h"
#include "AnimatedButton.h"
#include "buyerwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <string>
#include <iostream>

SignInWindow::SignInWindow(QWidget *parent)
     : QWidget(parent)
{
    QPushButton *backButton = new QPushButton(this);
    backButton->setIcon(QIcon(":/pics/pics/back_arrow.png"));
    backButton->setIconSize(QSize(24, 24));
    backButton->setFlat(true);

    QLabel *logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap(":/pics/pics/logo.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLineEdit *loginEdit = new QLineEdit(this);
    loginEdit->setPlaceholderText("Логин");
    loginEdit->setMinimumHeight(25);
    loginEdit->setMinimumWidth(150);
    loginEdit->setMaximumWidth(300);

    QLineEdit *passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMinimumHeight(25);
    passwordEdit->setMinimumWidth(150);
    passwordEdit->setMaximumWidth(300);

    QVBoxLayout *editLayout = new QVBoxLayout;
    editLayout->addWidget(loginEdit);
    editLayout->addWidget(passwordEdit);
    editLayout->setSpacing(10);
    editLayout->setAlignment(Qt::AlignCenter);

    QPushButton *signInButton = new AnimatedButton("Войти", "#C28D4B", "#C28D4B", "", this);
    signInButton->setFixedHeight(40);
    signInButton->setMinimumWidth(150);
    signInButton->setMaximumWidth(300);

    QLabel *errorLabel = new QLabel(this);
    errorLabel->setText("Неверный логин или пароль");
    errorLabel->setStyleSheet("QLabel { color : white; }");
    errorLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *buttonAndErrorLayout = new QVBoxLayout;
    buttonAndErrorLayout->addWidget(signInButton, 0, Qt::AlignCenter);
    buttonAndErrorLayout->addWidget(errorLabel);
    buttonAndErrorLayout->setSpacing(10);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(backButton, 0, Qt::AlignLeft);
    layout->addWidget(logoLabel, 0, Qt::AlignCenter);
    layout->addLayout(editLayout);
    layout->addLayout(buttonAndErrorLayout);

    setLayout(layout);

    setWindowTitle("Вход в аккаунт");
    resize(400, 500);

    connect(backButton, &QPushButton::clicked, this, &SignInWindow::backButtonClicked);

    connect(signInButton, &QPushButton::clicked, [this, loginEdit, passwordEdit, errorLabel]() {
        emit signInButtonClicked();

        QString login = loginEdit->text();
        QString password = passwordEdit->text();

        std::string stdLogin = login.toStdString();
        std::string stdPassword = password.toStdString();

        std::shared_ptr<Account> currentAccount = account.signIn(stdLogin, stdPassword);
        if (!currentAccount)
        {
            errorLabel->setStyleSheet("QLabel { color : red; }");
        }
        else
        {
            errorLabel->setStyleSheet("QLabel { color : white; }");

            loginEdit->clear();
            passwordEdit->clear();

            emit signInSuccessful(currentAccount);
        }

    });
}
