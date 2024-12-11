#include "loginwindow.h"
#include "AnimatedButton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

LogInWindow::LogInWindow(QWidget *parent)
    : QWidget(parent)
{
    auto backButton = new QPushButton(this);
    backButton->setIcon(QIcon(":/pics/pics/back_arrow.png"));
    backButton->setIconSize(QSize(24, 24));
    backButton->setFlat(true);

    auto logoLabel = new QLabel(this);
    logoLabel->setPixmap(QPixmap(":/pics/pics/logo.png").scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setAlignment(Qt::AlignCenter);

    auto loginEdit = new QLineEdit(this);
    loginEdit->setPlaceholderText("Логин");
    loginEdit->setMinimumHeight(25);
    loginEdit->setMinimumWidth(150);
    loginEdit->setMaximumWidth(300);

    auto passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setMinimumHeight(25);
    passwordEdit->setMinimumWidth(150);
    passwordEdit->setMaximumWidth(300);

    auto passwordCheckEdit = new QLineEdit(this);
    passwordCheckEdit->setPlaceholderText("Повторный пароль");
    passwordCheckEdit->setMinimumHeight(25);
    passwordCheckEdit->setMinimumWidth(150);
    passwordCheckEdit->setMaximumWidth(300);

    auto editLayout = new QVBoxLayout;
    editLayout->addWidget(loginEdit);
    editLayout->addWidget(passwordEdit);
    editLayout->addWidget(passwordCheckEdit);
    editLayout->setSpacing(10);
    editLayout->setAlignment(Qt::AlignCenter);

    auto logInButton = new AnimatedButton("Создать аккаунт", "#C28D4B", "white", "#C28D4B", "", this);
    logInButton->setFixedHeight(40);
    logInButton->setMinimumWidth(150);
    logInButton->setMaximumWidth(300);

    logInButton->setEnabled(false);

    auto validateInputs = [logInButton, loginEdit, passwordEdit, passwordCheckEdit]() {
        bool isLoginFilled = !loginEdit->text().trimmed().isEmpty();
        bool isPasswordFilled = !passwordEdit->text().trimmed().isEmpty();
        bool isPasswordCheckFilled = !passwordCheckEdit->text().trimmed().isEmpty();
        logInButton->setEnabled(isLoginFilled && isPasswordFilled && isPasswordCheckFilled);
    };

    connect(loginEdit, &QLineEdit::textChanged, validateInputs);
    connect(passwordEdit, &QLineEdit::textChanged, validateInputs);
    connect(passwordCheckEdit, &QLineEdit::textChanged, validateInputs);

    auto errorLabel = new QLabel(this);
    errorLabel->setText("Пароль не совпадает");
    errorLabel->setStyleSheet("QLabel { color : white; }");
    errorLabel->setAlignment(Qt::AlignCenter);

    auto buttonAndErrorLayout = new QVBoxLayout;
    buttonAndErrorLayout->addWidget(logInButton, 0, Qt::AlignCenter);
    buttonAndErrorLayout->addWidget(errorLabel);
    buttonAndErrorLayout->setSpacing(10);

    auto layout = new QVBoxLayout;
    layout->addWidget(backButton, 0, Qt::AlignLeft);
    layout->addWidget(logoLabel, 0, Qt::AlignCenter);
    layout->addLayout(editLayout);
    layout->addLayout(buttonAndErrorLayout);

    setLayout(layout);

    setWindowTitle("Создать аккаунт");
    resize(400, 500);

    connect(backButton, &QPushButton::clicked, this, &LogInWindow::backButtonClicked);

    connect(logInButton, &QPushButton::clicked, [this, loginEdit, passwordEdit, passwordCheckEdit, errorLabel]() {
        emit logInButtonClicked();

        QString login = loginEdit->text();
        QString password = passwordEdit->text();
        QString passwordCheck = passwordCheckEdit->text();

        std::string stdLogin = login.toStdString();
        std::string stdPassword = password.toStdString();
        std::string stdPasswordCheck = passwordCheck.toStdString();
        if (stdPassword != stdPasswordCheck)
        {
            errorLabel->setText("Пароль не совпадает");
            errorLabel->setStyleSheet("QLabel { color : red; }");
        }
        else
        {
            std::shared_ptr<Account> currentAccount = account.logIn(stdLogin, stdPassword);
            if (!currentAccount)
            {
                errorLabel->setText("Аккаунт с таким именем уже существует");
                errorLabel->setStyleSheet("QLabel { color : red; }");
            }
            else
            {
                errorLabel->setStyleSheet("QLabel { color : white; }");

                loginEdit->clear();
                passwordEdit->clear();
                passwordCheckEdit->clear();

                emit logInSuccessful(currentAccount);
            }
        }
    });
}
