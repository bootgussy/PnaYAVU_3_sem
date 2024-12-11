#include "changeoptiondiscount.h"
#include "custommessagebox.h"

ChangeOptionDiscount::ChangeOptionDiscount(QWidget *parent)
    : ChooseOptionWidget(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    operationLabelButton = new AnimatedButton("Изменить скидку", "white", "black", "white", "color: black; padding: 12px;", this);
    changeText = QString::fromUtf8("Изменить");

    stackedWidget = new QStackedWidget(this);

    stackedWidget->addWidget(categoriesWidget());
    stackedWidget->addWidget(optionSelection());
    stackedWidget->addWidget(this->editWidget());

    stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(stackedWidget, 1);
}

QWidget *ChangeOptionDiscount::editWidget() {
    auto mainWidget = new QWidget(this);

    changeLayout = new QHBoxLayout(mainWidget);

    currentItemWidget = new QWidget(this);
    currentItemLayout = new QVBoxLayout(currentItemWidget);
    currentItemLayout->setContentsMargins(0, 0, 0, 0);

    auto changingDiscountWidget = new QWidget(this);
    auto changingDiscountLayout = new QVBoxLayout(changingDiscountWidget);

    categoryLabelButton = new AnimatedButton("Категория: ", "white", "black", "white", "color: black; padding: 12px;", this);

    discountInput = new QLineEdit(this);
    discountInput->setPlaceholderText("Новая скидка");

    discountInput->setMinimumHeight(25);
    discountInput->setMinimumWidth(200);

    auto confirmButton = new AnimatedButton("Подтвердить иземенение", "#C28D4B", "white", "#C28D4B", "color: white; padding: 3px 7px 3px 7px;", this);

    confirmButton->setEnabled(false);

    connect(discountInput, &QLineEdit::textChanged, confirmButton, [confirmButton](const QString &text) {
        confirmButton->setEnabled(!text.trimmed().isEmpty());
    });

    changingDiscountLayout->addWidget(categoryLabelButton, 0, Qt::AlignHCenter);
    changingDiscountLayout->addWidget(discountInput, 0, Qt::AlignHCenter);
    changingDiscountLayout->addWidget(confirmButton, 0, Qt::AlignHCenter);
    changingDiscountLayout->setSpacing(20);
    changingDiscountLayout->setContentsMargins(0, 0, 0, 0);

    changingDiscountWidget->setMaximumHeight(150);

    if (currentItemLayout) {
        delete currentItemLayout;
        currentItemLayout = nullptr;
    }

    currentItemLayout = new QVBoxLayout();

    changeLayout->addLayout(currentItemLayout);
    changeLayout->addWidget(changingDiscountWidget);

    connect(confirmButton, &QPushButton::clicked, [this]() {
        bool ok;
        double newDiscount = discountInput->text().toInt(&ok);

        if(!ok) {
            CustomMessageBox::warning(this, "Ошибка", "Cкидка должна быть целым числом!");
        }
        else if (newDiscount >= 0 && newDiscount < 100) {
            processConfirm<int>(this, "скидку", "Скидка", newDiscount, discountInput, [this](int discount) {
                Database::getInstance()->setDiscount(currentOption.getName(), static_cast<int>(discount));
            });
        } else {
            CustomMessageBox::warning(this, "Ошибка", "Введите корректную скидку!");
        }
    });

    return mainWidget;
}
