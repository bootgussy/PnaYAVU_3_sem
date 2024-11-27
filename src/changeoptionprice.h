#ifndef CHANGEOPTIONPRICE_H
#define CHANGEOPTIONPRICE_H

#include "chooseoptionwidget.h"
#include "Manager.h"

class ChangeOptionPrice : public ChooseOptionWidget {
    Q_OBJECT

public:
    explicit ChangeOptionPrice(QWidget *parent = nullptr);

private:
    Manager manager;

    QWidget *editWidget() override;
};

#endif // CHANGEOPTIONPRICE_H
