#ifndef EDITOPTIONS_H
#define EDITOPTIONS_H

#include "chooseoptionwidget.h"
#include "Database.h"
#include <QPushButton>
#include <QLineEdit>
#include <QStackedWidget>
#include <QListWidget>
#include <QString>

class EditOptions : public ChooseOptionWidget {
    Q_OBJECT

public:
    explicit EditOptions(QWidget *parent = nullptr);

private:
    QWidget *categoriesWidget() override;
    void populateMenuItems(int categoryId);
    QWidget *editWidget() override;
    QWidget *addOptionPage();
    void populateCategoryList();
    QString categoryName;

private:
    QListWidget *categoryList;
};

#endif // EDITOPTIONS_H
