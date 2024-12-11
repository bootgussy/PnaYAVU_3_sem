#include "chooseoptionwidget.h"

ChooseOptionWidget::ChooseOptionWidget(QWidget* parent)
    : QWidget(parent) {}

void ChooseOptionWidget::populateMenuItems(int categoryId) {
    QLayoutItem *child;
    while ((child = optionsLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    struct MenuItem {
        QString name;
        QString imagePath;
        double price;
    };

    int row = 0;
    int col = 0;
    for (const MenuOption &item : menu.displayOptions(categoryId)) {
        auto itemWidget = new QWidget(this);

        auto itemLayout = new QVBoxLayout(itemWidget);

        auto contentLayout = new ItemLayout(item);
        itemLayout->addLayout(contentLayout);
        changeButton = new AnimatedButton("Изменить", "#C28D4B", "#C28D4B", "color: white; padding: 3px 7px 3px 7px;", this);
        itemLayout->addWidget(changeButton, 0, Qt::AlignCenter);

        itemWidget->setStyleSheet(R"(
                                QWidget {
                                    border: 1px solid lightgray;
                                    border-radius: 5px;
                                    color: black;
                                    margin: 5px;
                                }
                                )");

        itemWidget->setMaximumHeight(250);
        itemWidget->setMaximumWidth(190);
        itemWidget->setMinimumWidth(180);

        optionsLayout->addWidget(itemWidget, row, col);

        if (++col == 2) {
            col = 0;
            row++;
        }

        connect(changeButton, &QPushButton::clicked, [this, item, &contentLayout]() {
            if (currentItemWidget) {
                changeLayout->removeWidget(currentItemWidget);
                currentItemWidget->deleteLater();  // Безопасное удаление
                currentItemWidget = nullptr;
            }

            currentItemWidget = new QWidget(this);
            auto itemLayout = new QVBoxLayout(currentItemWidget);

            contentLayout = new ItemLayout(item, this);
            currentOption = item;
            itemLayout->addLayout(contentLayout);

            currentItemWidget->setStyleSheet(R"(
                                QWidget {
                                    border: 1px solid lightgray;
                                    border-radius: 5px;
                                    color: black;
                                    margin: 5px;
                                }
                                )");

            currentItemWidget->setMaximumHeight(250);
            currentItemWidget->setMaximumWidth(190);
            currentItemWidget->setMinimumWidth(180);

            changeLayout->insertWidget(0, currentItemWidget);

            stackedWidget->setCurrentIndex(2);
        });
    }

    optionsWidget->update();
    optionsScrollArea->setWidgetResizable(true);
}

QWidget *ChooseOptionWidget::categoriesWidget() {
    auto categoriesLabelWidget = new QWidget(this);
    auto categoriesLabelLayout = new QHBoxLayout(categoriesLabelWidget);

    auto categoriesLabelButton = new AnimatedButton("     Категории     ", "white", "black", "color: black; padding: 12px;", this);
    categoriesLabelButton->setEnabled(false);
    categoriesLabelLayout->addWidget(categoriesLabelButton, 1, Qt::AlignCenter);
    categoriesLabelLayout->setSpacing(5);

    categoryList = new CategoriesList();
    categoryList->setFocusPolicy(Qt::NoFocus);

    auto mainWidget = new QWidget(this);
    auto categoryLayout = new QVBoxLayout(mainWidget);
    categoryLayout->addWidget(operationLabelButton, 0, Qt::AlignRight);
    categoryLayout->addWidget(categoriesLabelWidget);
    categoryLayout->addWidget(categoryList);

    categoriesLabelWidget->setStyleSheet("border: 0px;");

    connect(categoryList, &QListWidget::itemClicked, [this](QListWidgetItem *item) {
        int categoryId = item->data(Qt::UserRole).toInt();

        categoryLabelButton->setText("Категория: " + item->text());
        categoryLabelButton->update();
        populateMenuItems(categoryId);

        stackedWidget->setCurrentIndex(1);
    });

    return mainWidget;
}

QWidget* ChooseOptionWidget::optionSelection() {
    auto mainWidget = new QWidget(this);

    auto optionLayout = new QVBoxLayout(mainWidget);

    auto headerLayout = new QHBoxLayout();

    auto toCategoriesBackButton = new QPushButton(this);
    toCategoriesBackButton->setIcon(QIcon(":/pics/pics/back_arrow.png"));
    toCategoriesBackButton->setIconSize(QSize(24, 24));
    toCategoriesBackButton->setFlat(true);

    categoryLabelButton = new AnimatedButton("Категория: ", "white", "black", "color: black; padding: 12px;", this);
    categoryLabelButton->setEnabled(false);

    headerLayout->addWidget(toCategoriesBackButton, 0, Qt::AlignLeft);
    headerLayout->addWidget(categoryLabelButton, 0, Qt::AlignRight);

    optionsScrollArea = new QScrollArea(this);
    optionsWidget = new QWidget(this);
    optionsLayout = new QGridLayout(optionsWidget);

    optionsScrollArea->setWidget(optionsWidget);
    optionsScrollArea->setStyleSheet("background: white;");

    optionLayout->addLayout(headerLayout);
    optionLayout->addWidget(optionsScrollArea);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(toCategoriesBackButton, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentIndex(0);
    });

    return mainWidget;
}
