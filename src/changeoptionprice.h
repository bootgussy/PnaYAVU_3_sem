#ifndef CHANGEOPTIONPRICE_H
#define CHANGEOPTIONPRICE_H

#include "chooseoptionwidget.h"

class ChangeOptionPrice : public ChooseOptionWidget {
    Q_OBJECT

public:
    explicit ChangeOptionPrice(QWidget *parent = nullptr);

private:
    QWidget *editWidget() override;
    QLineEdit *priceInput;
};

#endif // CHANGEOPTIONPRICE_H
