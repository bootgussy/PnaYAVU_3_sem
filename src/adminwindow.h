#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include "leadershipwindow.h"
#include "changeoptionprice.h"
#include "changeoptiondiscount.h"

#include "editcategories.h"
#include "editoptions.h"

#include <QMetaType>

class AdminWindow : public LeadershipWindow<int> {
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);

protected:
    void handleSpecificOperation(int operationIndex) override;

signals:
    void logOutButtonClicked();
};
#endif // ADMINWINDOW_H
