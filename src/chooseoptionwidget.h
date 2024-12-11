#ifndef CHOOSEOPTIONWIDGET_H
#define CHOOSEOPTIONWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QMessageBox>
#include <QScrollArea>
#include "MenuOption.h"
#include "itemlayout.h"
#include "categorieslist.h"
#include "AnimatedButton.h"
#include "Menu.h"
#include "custommessagebox.h"


class ChooseOptionWidget : public QWidget {
    Q_OBJECT

public:
    explicit ChooseOptionWidget(QWidget* parent = nullptr);

protected:
    QScrollArea *optionsScrollArea;
    QWidget *optionsWidget;
    QGridLayout *optionsLayout;
    QListWidget *categoryList;
    AnimatedButton *operationLabelButton;
    AnimatedButton *changeButton;
    AnimatedButton *categoryLabelButton;
    AnimatedButton *categoryLabel;
    QWidget *currentItemWidget;
    QVBoxLayout *currentItemLayout;
    QHBoxLayout *changeLayout;
    ItemLayout *contentLayout;
    QStackedWidget *stackedWidget;
    QHBoxLayout *headerLayout;
    QVBoxLayout *optionLayout;
    QString changeText;

    MenuOption currentOption;
    Menu menu;

    void populateMenuItems(int categoryId);
    virtual QWidget *categoriesWidget();
    QWidget *optionSelection();
    virtual QWidget *editWidget() = 0;

    template <typename T>
    bool processConfirm(QWidget *parent, const QString &attributeNameClarify,  const QString &attributeNameSucessfull, T value, QLineEdit *input,
                                                 const std::function<void(T)> &updateCallback) const {
        CustomMessageBox confirmDialog;
        confirmDialog.setWindowTitle("Подтверждение");
        confirmDialog.setText("Вы уверены, что хотите изменить " + attributeNameClarify + "?");
        confirmDialog.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        confirmDialog.setDefaultButton(QMessageBox::No);

        if (confirmDialog.exec() == QMessageBox::Yes) {
            updateCallback(value);
            CustomMessageBox::information(parent, "Успешно", attributeNameSucessfull + " успешно изменена!");
            input->clear();

            stackedWidget->setCurrentIndex(0);
            return true;
        }
        return false;
    }
};

#endif // CHOOSEOPTIONWIDGET_H
