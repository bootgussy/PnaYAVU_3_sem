#ifndef CATEGORIESLIST_H
#define CATEGORIESLIST_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include "MarqueeLabel.h"
#include "MenuOption.h"

class CategoriesList : public QListWidget {
    Q_OBJECT

public:
    explicit CategoriesList(QWidget *parent = nullptr);

private:
    QListWidget *categoryList;

    void populateCategories();
};

#endif // CATEGORIESLIST_H
