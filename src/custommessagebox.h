#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H

#include <QMessageBox>

class CustomMessageBox : public QMessageBox {
public:
    CustomMessageBox(QWidget *parent = nullptr) : QMessageBox(parent) {
        // Устанавливаем стиль для всех окон
        setStyleSheet(
            "QMessageBox { "
            "    background-color: white; "
            "} "
            "QLabel { "
            "    color: black; "
            "} "
            "QPushButton { "
            "    background-color: #C28D4B; "
            "    color: white; "
            "    border: 2px solid white; "
            "    border-radius: 10px; "
            "    padding: 5px 10px; "
            "} "
            "QPushButton:hover { "
            "    background-color: #d4b16e; "
            "}"
            );
    }

    static void warning(QWidget *parent, const QString &title, const QString &text) {
        CustomMessageBox warningDialog(parent);
        warningDialog.setWindowTitle(title);
        warningDialog.setText(text);
        warningDialog.setIcon(QMessageBox::Warning);
        warningDialog.setStandardButtons(QMessageBox::Ok);
        warningDialog.exec();
    }

    static void information(QWidget *parent, const QString &title, const QString &text) {
        CustomMessageBox infoDialog(parent);
        infoDialog.setWindowTitle(title);
        infoDialog.setText(text);
        infoDialog.setIcon(QMessageBox::Information);
        infoDialog.setStandardButtons(QMessageBox::Ok);
        infoDialog.exec();
    }
};

#endif // CUSTOMMESSAGEBOX_H
