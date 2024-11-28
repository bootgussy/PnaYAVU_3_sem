#ifndef MARQUEELABEL_H
#define MARQUEELABEL_H

#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QResizeEvent>

class MarqueeLabel : public QLabel {
    Q_OBJECT

public:
    explicit MarqueeLabel(QWidget* parent = nullptr)
        : QLabel(parent), offset(0) {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MarqueeLabel::updatePosition);
    }

    void setText(const QString& text) {
        QLabel::setText(text);
        offset = 0;
        checkTextOverflow();
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        QFontMetrics fm(font());

        // Если текст длиннее, чем ширина виджета, делаем бегущую строку
        if (fm.horizontalAdvance(text()) > width()) {
            QRect clippingRect = rect().adjusted(10, 0, -10, 0);
            painter.setClipRect(clippingRect);

            int textWidth = fm.horizontalAdvance(text() + "       ");
            int x = -offset % textWidth; // Вычисляем начальную позицию

            painter.drawText(x, 0, textWidth, height(), Qt::AlignVCenter, text() + "       ");
            painter.drawText(x + textWidth, 0, textWidth, height(), Qt::AlignVCenter, text() + "       ");
        } else {
            // Если текст помещается, отобразим его по центру
            painter.drawText(rect(), Qt::AlignCenter, text());
        }
    }

    void resizeEvent(QResizeEvent* event) override {
        QLabel::resizeEvent(event);
        checkTextOverflow();
    }

private slots:
    void updatePosition() {
        offset += 1;
        update();
    }

private:
    QTimer* timer;
    int offset;

    void checkTextOverflow() {
        QFontMetrics fm(font());
        if (fm.horizontalAdvance(text()) > width()) {
            // Запускаем таймер для создания бегущей строки
            timer->start(40); // Настройте скорость по необходимости
        } else {
            // Останавливаем таймер, если текст помещается
            timer->stop();
        }
    }
};

#endif // MARQUEELABEL_H
