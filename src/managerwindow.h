#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include "leadershipwindow.h"
#include "changeoptionprice.h"
#include "changeoptiondiscount.h"

#include "editcategories.h"
#include "editoptions.h"
#include <QMetaType>

class ManagerWindow : public LeadershipWindow<int> {
    Q_OBJECT

public:
    explicit ManagerWindow(QWidget *parent = nullptr);

protected:
    void handleSpecificOperation(int operationIndex) override;

signals:
    void logOutButtonClicked();
};
#endif // MANAGERWINDOW_H
