#ifndef EDITCATEGORIES_H
#define EDITCATEGORIES_H

#include "chooseoptionwidget.h"
#include "Database.h"
#include <QPushButton>
#include <QLineEdit>
#include <QStackedWidget>
#include <QListWidget>

class EditCategories : public ChooseOptionWidget {
    Q_OBJECT

public:
    explicit EditCategories(QWidget *parent = nullptr);

private:
    QWidget *editWidget() override;
    void populateListItems();
    QWidget *addCategoryPage();
    void populateCategoryList();

private:
    QListWidget *categoryList;
};

#endif // EDITCATEGORIES_H
