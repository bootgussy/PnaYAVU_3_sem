#ifndef CHANGEOPTIONDISCOUNT_H
#define CHANGEOPTIONDISCOUNT_H

#include "chooseoptionwidget.h"

class ChangeOptionDiscount : public ChooseOptionWidget {
    Q_OBJECT

public:
    explicit ChangeOptionDiscount(QWidget *parent = nullptr);

private:
    QWidget *editWidget() override;
    QLineEdit *discountInput;
};

#endif // CHANGEOPTIONDISCOUNT_H
