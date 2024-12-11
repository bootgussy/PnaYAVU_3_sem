#include "editcategories.h"
#include "custommessagebox.h"

EditCategories::EditCategories(QWidget *parent)
    : ChooseOptionWidget(parent)
{
    auto mainLayout = new QVBoxLayout(this);

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(editWidget());
    stackedWidget->addWidget(addCategoryPage());

    mainLayout->addWidget(stackedWidget, 1);
}

QWidget *EditCategories::editWidget() {
    auto headerLayout = new QHBoxLayout();

    auto addCategoryButton = new AnimatedButton("Добавить категорию", "#C28D4B", "#C28D4B", "#C28D4B", "color: white; padding: 12px;", this);
    operationLabelButton = new AnimatedButton("Редактировать категории", "white", "black", "white", "color: black; padding: 12px;", this);
    headerLayout->addWidget(addCategoryButton, 0, Qt::AlignLeft);
    headerLayout->addWidget(operationLabelButton, 0, Qt::AlignRight);

    headerLayout->setContentsMargins(0, 0, 0, 0);

    auto categoriesLabelWidget = new QWidget(this);
    auto categoriesLabelLayout = new QHBoxLayout(categoriesLabelWidget);

    auto categoriesLabelButton = new AnimatedButton("     Категории     ", "white", "black", "white", "color: black; padding: 12px;", this);
    categoriesLabelLayout->addWidget(categoriesLabelButton, 1, Qt::AlignCenter);
    categoriesLabelLayout->setSpacing(5);

    categoryList = new QListWidget(this);
    populateListItems();

    auto mainWidget = new QWidget(this);
    auto categoryLayout = new QVBoxLayout(mainWidget);
    categoryLayout->addLayout(headerLayout);
    categoryLayout->addWidget(categoriesLabelWidget);
    categoryLayout->addWidget(categoryList);

    categoriesLabelWidget->setStyleSheet("border: 0px;");

    connect(addCategoryButton, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentIndex(1);
    });

    return mainWidget;
}

void EditCategories::populateListItems()
{
    if (!categoryList) {
        categoryList = new QListWidget(this);
        categoryList->setFocusPolicy(Qt::NoFocus);
    } else {
        categoryList->clear();
    }

    for (int categoryId : Database::getInstance()->getCategories()) {
        QString categoryName = QString::fromStdString(Database::getInstance()->getCategory(categoryId));

        auto rowWidget = new QWidget();
        auto rowLayout = new QHBoxLayout(rowWidget);

        auto categoryLabel = new QLabel(categoryName);
        categoryLabel->setStyleSheet("color: black;");
        rowLayout->addWidget(categoryLabel, 0, Qt::AlignLeft);

        auto deleteButton = new QPushButton();
        deleteButton->setIcon(QIcon(":/pics/pics/delete_icon.png"));
        deleteButton->setIconSize(QSize(20, 20));
        deleteButton->setFixedSize(20, 20);
        deleteButton->setStyleSheet("border: none;");

        rowLayout->addWidget(deleteButton, 0, Qt::AlignRight);

        rowLayout->setSpacing(0);
        rowLayout->setContentsMargins(0, 0, 0, 0);

        rowWidget->setMinimumHeight(20);

        auto item = new QListWidgetItem(categoryList);
        item->setData(Qt::UserRole, categoryId);

        categoryList->addItem(item);
        categoryList->setItemWidget(item, rowWidget);

        connect(deleteButton, &QPushButton::clicked, [this, item, categoryId, categoryName]() {
            CustomMessageBox confirmDialog;
            confirmDialog.setWindowTitle("Подтверждение");
            confirmDialog.setText("Вы уверены, что хотите удалить категорию " + categoryName + "?");
            confirmDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            confirmDialog.setDefaultButton(QMessageBox::No);

            if (confirmDialog.exec() == QMessageBox::Yes) {
                Database::getInstance()->deleteCategory(categoryId);

                populateListItems();
            }
        });
    }

    categoryList->setStyleSheet(R"(
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
                                )");
}

QWidget *EditCategories::addCategoryPage() {
    auto mainWidget = new QWidget(this);
    auto layout = new QVBoxLayout(mainWidget);

    auto newCategoryOperationButton = new AnimatedButton("Добавить новую категорию", "white", "black", "white", "color: black; padding: 12px; margin: 0px;", this);

    auto newCategoryLabelButton = new AnimatedButton("Введите название новой категории:", "lightgray", "white", "white", "color: black; padding: 7px; margin: 0px;", this);

    auto newCategoryInput = new QLineEdit(this);
    newCategoryInput->setPlaceholderText("Название категории");
    newCategoryInput->setMinimumWidth(270);

    auto addButton = new AnimatedButton("Добавить", "#C28D4B", "white", "#C28D4B", "color: white; padding: 7px;", this);

    addButton->setEnabled(false);

    connect(newCategoryInput, &QLineEdit::textChanged, addButton, [addButton](const QString &text) {
        addButton->setEnabled(!text.trimmed().isEmpty());
    });

    auto labelAndButtonWidget = new QWidget(this);
    auto labelAndButtonLayout = new QVBoxLayout(labelAndButtonWidget);

    labelAndButtonWidget->setObjectName("labelAndButtonWidget");
    labelAndButtonWidget->setStyleSheet(R"(
                                #labelAndButtonWidget {
                                    background-color: white;
                                    border: 2px solid black;
                                    border-radius: 10px;
                                    padding: 20px;
                                }
                                )");

    labelAndButtonLayout->addWidget(newCategoryLabelButton, 0, Qt::AlignCenter);
    labelAndButtonLayout->addWidget(newCategoryInput, 0, Qt::AlignCenter);
    labelAndButtonLayout->addWidget(addButton, 0, Qt::AlignCenter);
    labelAndButtonLayout->setSpacing(20);

    layout->addWidget(newCategoryOperationButton, 1, Qt::AlignTop);
    layout->addWidget(labelAndButtonWidget, 1, Qt::AlignCenter);
    layout->setSpacing(5);

    connect(addButton, &QPushButton::clicked, [this, newCategoryInput]() {
        QString newCategory = newCategoryInput->text().trimmed();

        if (newCategory.isEmpty()) {
            CustomMessageBox::warning(this, "Ошибка", "Название категории не может быть пустым.");
            return;
        }

        CustomMessageBox confirmDialog;
        confirmDialog.setWindowTitle("Подтверждение");
        confirmDialog.setText("Вы уверены, что хотите добавить категорию " + newCategory + "?");
        confirmDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        confirmDialog.setDefaultButton(QMessageBox::No);

        if (confirmDialog.exec() == QMessageBox::Yes) {
            if (Database::getInstance()->addCategory(newCategory.toStdString())) {
                CustomMessageBox::information(this, "Успешно", "Категория добавлена!");
                newCategoryInput->clear();

                populateListItems();
                stackedWidget->setCurrentIndex(0);
            }
            else {
                CustomMessageBox::warning(this, "Ошибка", "Такая категория уже существует.");
            }
        }
    });

    mainWidget->setMaximumHeight(300);
    return mainWidget;
}
