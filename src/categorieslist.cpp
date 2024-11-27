#include "categorieslist.h"
#include "Database.h"
#include <QVBoxLayout>

CategoriesList::CategoriesList(QWidget *parent)
: QListWidget()
{
    populateCategories();

    setStyleSheet(R"(
                                QListWidget {
                                    border: 0px;
                                    background-color: white;
                                    padding: 5px;
                                }
                                QListWidget::item {
                                    border: 1px solid lightgray;
                                    padding: 10px;
                                    border-radius: 5px;
                                    color: black;
                                    margin: 5px;
                                }
                                QListWidget::item:selected {
                                    background-color: lightgray;
                                }
                                QListWidget::item:hover {
                                    background-color: #e0e0e0;
                                }
                                )");
}

void CategoriesList::populateCategories() {
    for (int categoryId : Database::getInstance()->getCategories()) {
        QString categoryName = QString::fromStdString(Database::getInstance()->getCategory(categoryId));

        QListWidgetItem *item = new QListWidgetItem(categoryName, this);

        item->setData(Qt::UserRole, categoryId);

        addItem(item);
    }
}
