#ifndef LEADERSHIPWINDOW_H
#define LEADERSHIPWINDOW_H

#include "AnimatedButton.h"
#include "ChangeOptionPrice.h"
#include "ChangeOptionDiscount.h"
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QLabel>
#include <QString>
#include <vector>

template <typename OperationType>
class LeadershipWindow : public QWidget
{
public:
    explicit LeadershipWindow(const QString &statusText, const std::vector<std::pair<QString, OperationType>> &operations, QWidget *parent = nullptr)
        : QWidget(parent)
    {
        QString cellStyle = "padding: 12px;";

        auto headerLayout = new QHBoxLayout();

        auto statusWidget = new QWidget(this);
        auto statusLayout = new QHBoxLayout(statusWidget);
        auto statusLabel = new AnimatedButton(statusText, "white", "black", "color: black;", this);
        statusLayout->addWidget(statusLabel, 1, Qt::AlignLeft);
        statusWidget->setStyleSheet(cellStyle);

        auto logOutWidget = new QWidget(this);
        auto logOutLayout = new QHBoxLayout(logOutWidget);
        logOutButton = new AnimatedButton("Выход", "#EDC676", "#EDC676", "padding: 12px;", this);
        logOutLayout->addWidget(logOutButton, 1, Qt::AlignCenter);

        headerLayout->addWidget(statusWidget, 0, Qt::AlignLeft);
        headerLayout->addWidget(logOutWidget, 0, Qt::AlignRight);

        auto headerWidget = new QWidget(this);
        headerWidget->setLayout(headerLayout);

        auto *horizontalLine = new QFrame(this);
        horizontalLine->setFrameShape(QFrame::HLine);
        horizontalLine->setFrameShadow(QFrame::Sunken);

        auto operationsWidget = new QWidget(this);

        auto operationsLabelWidget = new QWidget(this);
        auto operationsLabelLayout = new QHBoxLayout(operationsLabelWidget);
        auto operationsLabelButton = new AnimatedButton("Операции", "white", "black", "color: black;", this);
        operationsLabelButton->setEnabled(false);
        operationsLabelLayout->addWidget(operationsLabelButton, 1, Qt::AlignCenter);
        operationsLabelWidget->setStyleSheet(cellStyle);

        operationsList = new QListWidget(this);
        operationsList->setFocusPolicy(Qt::NoFocus);

        for (const auto &operation : operations) {
            auto item = new QListWidgetItem(operation.first, operationsList);
            item->setData(Qt::UserRole, operation.second);
            operationsList->addItem(item);
        }

        auto operationsLayout = new QVBoxLayout();
        operationsLayout->addWidget(operationsLabelWidget);
        operationsLayout->addWidget(operationsList);

        operationsWidget->setLayout(operationsLayout);
        operationsWidget->setStyleSheet(R"(
                                QWidget {
                                    background-color: white;
                                    border: 2px solid black;
                                    border-radius: 5px;
                                    padding: 5px;
                                }
                                )");
        operationsLabelWidget->setStyleSheet("border: 0px;");
        operationsList->setStyleSheet(R"(
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

        operationsWidget->setMaximumWidth(230);

        operationWidget = new QWidget(this);
        operationLayout = new QVBoxLayout(operationWidget);
        operationLayout->setContentsMargins(0, 0, 0, 0);
        operationWidget->setObjectName("operationWidget");
        operationWidget->setStyleSheet(R"(
                                #operationWidget {
                                    background-color: white;
                                    border: 2px solid black;
                                    border-radius: 5px;
                                    padding: 5px;
                                }
                                )");

        auto mainWidget = new QWidget(this);
        auto mainLayout = new QHBoxLayout(mainWidget);
        mainLayout->addWidget(operationsWidget);
        mainLayout->addWidget(operationWidget);

        auto layout = new QVBoxLayout;
        layout->addWidget(headerWidget, 0, Qt::AlignTop);
        layout->addWidget(horizontalLine);
        layout->addWidget(mainWidget);

        setLayout(layout);

        connect(operationsList, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
            if (currentOperationWidget) {
                operationLayout->removeWidget(currentOperationWidget);
                currentOperationWidget->deleteLater();
                currentOperationWidget = nullptr;
            }

            OperationType operationValue = item->data(Qt::UserRole).value<OperationType>();
            handleSpecificOperation(operationValue);

            if (currentOperationWidget) {
                operationLayout->addWidget(currentOperationWidget);
            }
        });
    }

protected:

    QListWidget *operationsList;
    QVBoxLayout *operationLayout;
    QWidget *operationWidget;
    QWidget *currentOperationWidget = nullptr;
    AnimatedButton *logOutButton;

    void addItemToList(const QString &itemName, OperationType operationValue)
    {
        auto item = new QListWidgetItem(itemName, operationsList);
        item->setData(Qt::UserRole, QVariant::fromValue(operationValue));
        operationsList->addItem(item);
    }

    virtual void handleSpecificOperation(OperationType operationValue) = 0;
};

#endif // LEADERSHIPWINDOW_H
