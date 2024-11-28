#ifndef CHANGEOPTIONDISCOUNT_H
#define CHANGEOPTIONDISCOUNT_H

#include "chooseoptionwidget.h"
#include "Manager.h"

class ChangeOptionDiscount : public ChooseOptionWidget {
    Q_OBJECT

public:
    explicit ChangeOptionDiscount(QWidget *parent = nullptr);

private:
    Manager manager;

    QWidget *editWidget() override;
};

#endif // CHANGEOPTIONDISCOUNT_H
