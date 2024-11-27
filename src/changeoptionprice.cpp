#include "changeoptionprice.h"

ChangeOptionPrice::ChangeOptionPrice(QWidget *parent)
    : ChooseOptionWidget(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    operationLabelButton = new AnimatedButton("     Изменить цену     ", "white", "black", "color: black; padding: 12px;", this);


    stackedWidget = new QStackedWidget(this);

    stackedWidget->addWidget(categoriesWidget());
    stackedWidget->addWidget(optionSelection());
    stackedWidget->addWidget(this->editWidget());

    stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(stackedWidget, 1);
}

QWidget *ChangeOptionPrice::editWidget()
{
    auto mainWidget = new QWidget(this);

    changeLayout = new QHBoxLayout(mainWidget);

    currentItemWidget = new QWidget(this);
    currentItemLayout = new QVBoxLayout(currentItemWidget);
    currentItemLayout->setContentsMargins(0, 0, 0, 0);

    auto changingPriceWidget = new QWidget(this);
    auto changingPriceLayout = new QVBoxLayout(changingPriceWidget);

    categoryLabelButton = new AnimatedButton("Категория: ", "white", "black", "color: black; padding: 12px;", this);
    categoryLabelButton->setEnabled(false);

    auto priceInput = new QLineEdit(this);
    priceInput->setPlaceholderText("Новая цена");

    priceInput->setMinimumHeight(25);
    priceInput->setMinimumWidth(200);

    auto confirmButton = new AnimatedButton("Подтвердить иземенение", "#C28D4B", "#C28D4B", "color: white; padding: 3px 7px 3px 7px;", this);

    changingPriceLayout->addWidget(categoryLabelButton, 0, Qt::AlignHCenter);
    changingPriceLayout->addWidget(priceInput, 0, Qt::AlignHCenter);
    changingPriceLayout->addWidget(confirmButton, 0, Qt::AlignHCenter);
    changingPriceLayout->setSpacing(20);
    changingPriceLayout->setContentsMargins(0, 0, 0, 0);

    changingPriceWidget->setMaximumHeight(150);

    if (currentItemLayout) {
        delete currentItemLayout;
        currentItemLayout = nullptr;
    }

    currentItemLayout = new QVBoxLayout();

    changeLayout->addLayout(currentItemLayout);
    changeLayout->addWidget(changingPriceWidget);

    connect(confirmButton, &QPushButton::clicked, [this, priceInput]() {
        bool ok;
        double newPrice = priceInput->text().toDouble(&ok);

        if (ok && newPrice > 0) {
            processInputAndConfirm<double>(this, "цену", "Цена", newPrice, [this](double price) {
                manager.changePrice(currentOption.getName(), price);
            });
        } else {
            CustomMessageBox::warning(this, "Ошибка", "Введите корректную цену!");
        }
    });

    return mainWidget;
}
