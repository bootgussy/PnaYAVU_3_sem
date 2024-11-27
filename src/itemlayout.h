#ifndef ITEMLAYOUT_H
#define ITEMLAYOUT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "marqueelabel.h"
#include "MenuOption.h"

class ItemLayout : public QVBoxLayout {
    Q_OBJECT

public:
    explicit ItemLayout(const MenuOption &item, QWidget *parent = nullptr);

    MenuOption getMenuItem() const;
    QLabel *discountLabel;
    QLabel *newPriceLabel;
    QLabel *priceLabel;

private:
    MenuOption menuItem;
};

#endif // ITEMLAYOUT_H