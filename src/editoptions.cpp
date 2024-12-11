#include "editoptions.h"
#include "custommessagebox.h"

EditOptions::EditOptions(QWidget *parent)
    : ChooseOptionWidget(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    operationLabelButton = new AnimatedButton("Редактировать опции", "white", "black", "white", "color: black; padding: 12px;", this);
    changeText = QString::fromUtf8("Удалить");

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(categoriesWidget());
    stackedWidget->addWidget(editWidget());
    stackedWidget->addWidget(addOptionPage());

    mainLayout->addWidget(stackedWidget, 1);
}

QWidget *EditOptions::categoriesWidget() {
    auto categoriesLabelWidget = new QWidget(this);
    auto categoriesLabelLayout = new QHBoxLayout(categoriesLabelWidget);

    auto categoriesLabelButton = new AnimatedButton("     Категории     ", "white", "black", "white", "color: black; padding: 12px;", this);
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
        populateMenuItems(categoryId);

        categoryName = item->text();

        stackedWidget->setCurrentIndex(1);
    });

    return mainWidget;
}

void EditOptions::populateMenuItems(int categoryId) {
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
        changeButton = new AnimatedButton(changeText, "#C28D4B", "#C28D4B", "#C28D4B", "color: white; padding: 3px 7px 3px 7px;", this);
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

        connect(changeButton, &QPushButton::clicked, [this, item, &contentLayout, categoryId]() {
            CustomMessageBox confirmDialog;
            confirmDialog.setWindowTitle("Подтверждение");
            confirmDialog.setText("Вы уверены, что хотите удалить опцию " + QString::fromStdString(item.getName()) + "?");
            confirmDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            confirmDialog.setDefaultButton(QMessageBox::No);

            if (confirmDialog.exec() == QMessageBox::Yes) {
                Database::getInstance()->deleteOption(item.getName());

                populateMenuItems(categoryId);
            }
        });
    }

    optionsWidget->update();
    optionsScrollArea->setWidgetResizable(true);
}

QWidget *EditOptions::editWidget() {
    auto mainWidget = new QWidget(this);

    optionLayout = new QVBoxLayout(mainWidget);

    headerLayout = new QHBoxLayout();

    auto toCategoriesBackButton = new QPushButton(this);
    toCategoriesBackButton->setIcon(QIcon(":/pics/pics/back_arrow.png"));
    toCategoriesBackButton->setIconSize(QSize(24, 24));
    toCategoriesBackButton->setFlat(true);

    auto addOptionButton = new AnimatedButton("Добавить опцию", "#C28D4B", "#C28D4B", "#C28D4B", "color: white; padding: 12px;", this);

    categoryLabelButton = new AnimatedButton("Категория: ", "white", "black", "white", "color: black; padding: 12px;", this);

    headerLayout->addWidget(toCategoriesBackButton, 0, Qt::AlignLeft);
    headerLayout->addWidget(addOptionButton, 0, Qt::AlignRight);
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

    connect(addOptionButton, &QPushButton::clicked, [this]() {
        stackedWidget->setCurrentIndex(2);
    });

    return mainWidget;
}

QWidget *EditOptions::addOptionPage() {
    auto mainWidget = new QWidget(this);
    auto layout = new QVBoxLayout(mainWidget);

    auto newOptionOperationButton = new AnimatedButton("Добавить новую опцию", "white", "black", "white", "color: black; padding: 12px; margin: 0px;", this);

    auto newOptionLabelButton = new AnimatedButton("Введите данные новой опции:", "lightgray", "white", "white", "color: black; padding: 7px; margin: 0px;", this);

    auto newOptionNameInput = new QLineEdit(this);
    newOptionNameInput->setPlaceholderText("Название опции");
    newOptionNameInput->setMinimumWidth(270);

    auto newOptionPriceInput = new QLineEdit(this);
    newOptionPriceInput->setPlaceholderText("Цена опции");
    newOptionPriceInput->setMinimumWidth(270);

    auto addButton = new AnimatedButton("Добавить", "#C28D4B", "white", "#C28D4B", "color: white; padding: 7px;", this);

    addButton->setEnabled(false);

    auto validateInputs = [addButton, newOptionNameInput, newOptionPriceInput]() {
        bool isNameFilled = !newOptionNameInput->text().trimmed().isEmpty();
        bool isPriceFilled = !newOptionPriceInput->text().trimmed().isEmpty();
        addButton->setEnabled(isNameFilled && isPriceFilled);
    };

    connect(newOptionNameInput, &QLineEdit::textChanged, validateInputs);
    connect(newOptionPriceInput, &QLineEdit::textChanged, validateInputs);

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

    labelAndButtonLayout->addWidget(newOptionLabelButton, 0, Qt::AlignCenter);
    labelAndButtonLayout->addWidget(newOptionNameInput, 0, Qt::AlignCenter);
    labelAndButtonLayout->addWidget(newOptionPriceInput, 0, Qt::AlignCenter);
    labelAndButtonLayout->addWidget(addButton, 0, Qt::AlignCenter);
    labelAndButtonLayout->setSpacing(20);

    layout->addWidget(newOptionOperationButton, 1, Qt::AlignTop);
    layout->addWidget(labelAndButtonWidget, 1, Qt::AlignCenter);
    layout->setSpacing(5);

    connect(addButton, &QPushButton::clicked, [this, newOptionNameInput, newOptionPriceInput]() {
        QString newOptionName = newOptionNameInput->text().trimmed();

        bool ok;
        double newOptionPrice = newOptionPriceInput->text().toDouble(&ok);

        if(!ok) {
            CustomMessageBox::warning(this, "Ошибка", "Цена должна быть числом!");
        }
        else if (newOptionPrice <= 0) {
            CustomMessageBox::warning(this, "Ошибка", "Введите корректную цену!");
        }
        else {
            CustomMessageBox confirmDialog;
            confirmDialog.setWindowTitle("Подтверждение");
            confirmDialog.setText("Вы уверены, что хотите добавить опцию " + newOptionName + "?");
            confirmDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            confirmDialog.setDefaultButton(QMessageBox::No);

            if (confirmDialog.exec() == QMessageBox::Yes) {
                if (Database::getInstance()->addOptionToCategory(categoryName.toStdString(), newOptionNameInput->text().toStdString(), newOptionPrice, 0)) {
                    CustomMessageBox::information(this, "Успешно", "Опция добавлена!");
                    newOptionNameInput->clear();
                    newOptionPriceInput->clear();

                    stackedWidget->setCurrentIndex(0);
                }
                else {
                    CustomMessageBox::warning(this, "Ошибка", "Такая опция уже существует.");
                }
            }
        }
    });

    mainWidget->setMaximumHeight(300);
    return mainWidget;
}
