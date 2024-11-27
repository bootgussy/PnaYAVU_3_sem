#include "changeoptiondiscount.h"
#include "custommessagebox.h"

ChangeOptionDiscount::ChangeOptionDiscount(QWidget *parent)
    : ChooseOptionWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    operationLabelButton = new AnimatedButton("     Изменить скидку     ", "white", "black", "color: black; padding: 12px;", this);

    stackedWidget = new QStackedWidget(this);

    stackedWidget->addWidget(categoriesWidget());
    stackedWidget->addWidget(optionSelection());
    stackedWidget->addWidget(editWidget());

    stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(stackedWidget, 1);
}

QWidget *ChangeOptionDiscount::editWidget() {
    QWidget* mainWidget = new QWidget(this);

    changeLayout = new QHBoxLayout(mainWidget);

    currentItemWidget = new QWidget(this);
    currentItemLayout = new QVBoxLayout(currentItemWidget);
    currentItemLayout->setContentsMargins(0, 0, 0, 0);

    QWidget *changingDiscountWidget = new QWidget(this);
    QVBoxLayout *changingDiscountLayout = new QVBoxLayout(changingDiscountWidget);

    categoryLabelButton = new AnimatedButton("Категория: ", "white", "black", "color: black; padding: 12px;", this);
    categoryLabelButton->setEnabled(false);

    QLineEdit *discountInput = new QLineEdit(this);
    discountInput->setPlaceholderText("Новая скидка");

    discountInput->setMinimumHeight(25);
    discountInput->setMinimumWidth(200);

    AnimatedButton *confirmButton = new AnimatedButton("Подтвердить иземенение", "#C28D4B", "#C28D4B", "color: white; padding: 3px 7px 3px 7px;", this);

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

    connect(confirmButton, &QPushButton::clicked, [this, discountInput]() {
        bool ok;
        double newDiscount = discountInput->text().toDouble(&ok);

        if (ok && newDiscount >= 0 && newDiscount < 100) {
            processInputAndConfirm<double>(this, "скидку", "Скидка", newDiscount, [this](double discount) {
                manager.changeDiscount(currentOption.getName(), static_cast<int>(discount));
            });
        } else {
            CustomMessageBox::warning(this, "Ошибка", "Введите корректную скидку!");
        }
    });

    return mainWidget;
}
