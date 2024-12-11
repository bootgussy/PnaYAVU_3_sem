#include "itemlayout.h"

ItemLayout::ItemLayout(const MenuOption &item, QWidget *parent)
    : QVBoxLayout(), menuItem(item)
{
    auto imageLabel = new QLabel;
    imageLabel->setPixmap(QPixmap(":/pics/pics/logo.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    imageLabel->setStyleSheet("border: 0px;");

    auto nameLabel = new MarqueeLabel;
    nameLabel->setText(QString::fromStdString(item.getName()));
    nameLabel->setMaximumHeight(30);
    nameLabel->setMaximumWidth(100);
    nameLabel->setStyleSheet("border: 1px solid lightgray; background: lightgray;");

    discountLabel = new QLabel(QString("Скидка %1%").arg(item.getDiscount()));
    newPriceLabel = new QLabel(QString("$%1").arg(round((item.getPrice() - (item.getPrice() / 100 * item.getDiscount())) * 100) / 100));
    priceLabel = new QLabel(QString("$%1").arg(item.getPrice()));

    if (item.getDiscount() == 0) {
        discountLabel->setStyleSheet("border: 0px; color: white;");
        newPriceLabel->setStyleSheet("border: 0px; color: white;");
    } else {
        discountLabel->setStyleSheet("border: 0px;");
        newPriceLabel->setStyleSheet("border: 0px; color: red;");
        priceLabel->setText(QString("<html><body><s>$%1</s></body></html>").arg(item.getPrice()));
    }
    priceLabel->setStyleSheet("border: 0px;");

    auto inscriptionsLayout = new QVBoxLayout;
    inscriptionsLayout->addWidget(nameLabel, 0, Qt::AlignCenter);

    auto discountAndPriceLayout = new QHBoxLayout;
    discountAndPriceLayout->addWidget(discountLabel, 0, Qt::AlignLeft);
    discountAndPriceLayout->addWidget(newPriceLabel, 0, Qt::AlignRight);
    discountAndPriceLayout->addWidget(priceLabel, 0, Qt::AlignRight);

    inscriptionsLayout->addLayout(discountAndPriceLayout);
    inscriptionsLayout->setSpacing(0);

    addWidget(imageLabel, 0, Qt::AlignCenter);
    addLayout(inscriptionsLayout);
}

MenuOption ItemLayout::getMenuItem() const {
    return menuItem;
}

std::string ItemLayout::getName() const {
    return menuItem.getName();
}
